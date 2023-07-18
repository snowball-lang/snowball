#include "../../../../lexer/lexer.h"
#include "../../../../parser/Parser.h"
#include "../../../Analyzer.h"
#include "../../../TransformState.h"
#include "../../../Transformer.h"
#include "../../../TypeChecker.h"
#include "../../../analyzers/DefinitveAssigment.h"

#include <fstream>
#include <tuple>

using namespace snowball::utils;
using namespace snowball::Syntax::transform;

namespace snowball {
namespace Syntax {

SN_TRANSFORMER_VISIT(Statement::ImportStmt) {
    if (ctx->generateFunction) return;
    auto bkIsMainModule = ctx->isMainModule;
    auto package = p_node->getPackage();
    auto path = p_node->getPath();
    // TODO: extension
    auto [filePath, error] = ctx->imports->getImportPath(package, path);
    if (!error.empty()) { E<IO_ERROR>(p_node, error); }
    auto uuid = package == "Core" ? ctx->imports->CORE_UUID + path[0] : ctx->imports->getModuleUUID(filePath);
    auto exportName = ctx->imports->getExportName(filePath, p_node->getExportSymbol());
    auto isExternalModule = ctx->imports->isExternalModule(package);
    ctx->isMainModule = !isExternalModule;
    std::shared_ptr<ir::Module> importedModule = nullptr;
    if (ctx->getItem(exportName).second)
        Syntax::E<IMPORT_ERROR>(p_node, FMT("Import with name '%s' is already defined!", exportName.c_str()),
         {
            .info = "This is the import that was used",
            .note = "It may be possible that you have imported the same module twice\n"
                    "or that this symbol is already defined in the same stack.",
            .help = "If you want to import the same module twice, you can use the 'as'\n"
                    "keyword to give it a different name."
         });
    if (auto m = ctx->imports->cache->getModule(filePath)) {
        auto item = std::make_shared<Item>(m.value());
        ctx->addItem(exportName, item);
        importedModule = m.value();
    } else {
        auto niceFullName = package + "::" + utils::join(path.begin(), path.end(), "::");
        auto mod = std::make_shared<ir::Module>(niceFullName, uuid);
        std::vector<std::string> uuidStack = ctx->uuidStack.size() == 0
                ? std::vector<std::string>{}
                : std::vector<std::string>{ctx->uuidStack.front()};
        auto state = std::make_shared<ContextState>(ContextState::StackType{}, mod, uuidStack, nullptr);
        // clang-format off
        ctx->withState(state,
            [filePath = filePath, mod, this]() mutable {
                std::ifstream ifs(filePath.string());
                assert(!ifs.fail());
                std::string content((std::istreambuf_iterator<char>(ifs)),
                                    (std::istreambuf_iterator<char>()));
                auto srcInfo = new SourceInfo(content, filePath);
                auto lexer = new Lexer(srcInfo);
#if _SNOWBALL_TIMERS_DEBUG
                DEBUG_TIMER("Lexer: %fs (%s)", utils::_timer([&] {
                    lexer->tokenize();
                }), filePath.c_str());
#else
                lexer->tokenize();
#endif
                auto tokens = lexer->tokens;
                if (tokens.size() != 0) {
                    auto backupModule = ctx->module;
                    ctx->module = mod;
                    auto parser = new parser::Parser(tokens, srcInfo);
#if _SNOWBALL_TIMERS_DEBUG
                    parser::Parser::NodeVec ast;
                    DEBUG_TIMER("Parser: %fs (%s)", utils::_timer([&] { ast = parser->parse(); }), filePath.c_str());
#else
                    auto ast = parser->parse();
#endif
                    ctx->module->setSourceInfo(srcInfo);
                    visitGlobal(ast);
                    // TODO: make this a separate function to avoid any sort of "conflict" with the compiler's version of this algorithm
                    std::vector<Syntax::Analyzer *> passes = {
                        new Syntax::DefiniteAssigment(srcInfo)};
                    for (auto pass : passes)
                        pass->run(ast);
                    // TODO: set a new module to the import cache
                    ctx->module = backupModule;
                    addModule(ctx->module);
                    ctx->imports->cache->addModule(filePath, ctx->module);
                }
        });
        // clang-format on
        auto item = std::make_shared<Item>(mod);
        ctx->addItem(exportName, item);
        importedModule = mod;
    }

    if (p_node->hasAttribute(Attributes::MACROS)) {
        auto args = p_node->getAttributeArgs(Attributes::MACROS);
        auto macros = importedModule->getExportedMacros();
        for (auto [name, _v] : args) {
            if (!_v.empty()) {
                E<ATTRIBUTE_ERROR>(p_node, FMT("Attribute 'macros(%s)' does not take any arguments!", name.c_str()));
            }
            auto macro = macros.find(name);
            if (macro == macros.end()) {
                E<ATTRIBUTE_ERROR>(p_node, FMT("Macro '%s' does not exist!", name.c_str()),
                    {
                        .info = "This is the macro that was used",
                        .note = "It may be possible that you forgot to use the 'export' keyword\n"
                                "or that this macro does not exist in the imported module.",
                        .help = "If you want to import the macro from the module, you need to use\n"
                                "the 'export' keyword in front of the macro."
                    });
            }

            auto item = std::make_shared<Item>(macro->second);
            if (ctx->getInCurrentScope(name).second)
                Syntax::E<IMPORT_ERROR>(p_node, FMT("Import with name '%s' is already defined!", name.c_str()),
                 {
                    .info = "This is the import that was used",
                    .note = "It may be possible that you have imported the same module twice\n"
                            "or that this symbol is already defined in the same stack.",
                    .help = "If you want to import the same module twice, you can use the 'as'\n"
                            "keyword to give it a different name."
                 });
            ctx->addItem(name, item);
        }
    }

    ctx->isMainModule = bkIsMainModule;
}

} // namespace Syntax
} // namespace snowball