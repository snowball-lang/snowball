#include "../../../lexer.h"
#include "../../../parser/Parser.h"
#include "../../TransformState.h"
#include "../../Transformer.h"
#include "../../TypeChecker.h"

#include <fstream>
#include <tuple>

using namespace snowball::utils;
using namespace snowball::Syntax::transform;

namespace snowball {
namespace Syntax {

SN_TRANSFORMER_VISIT(Statement::ImportStmt) {
    auto package = p_node->getPackage();
    auto path    = p_node->getPath();
    // TODO: extension
    auto [filePath, error] = ctx->imports->getImportPath(package, path);
    if (!error.empty()) {
        E<IO_ERROR>(p_node, error);
    }

    auto uuid = ctx->imports->getModuleUUID(filePath);
    auto exportName =
        ctx->imports->getExportName(filePath, p_node->getExportSymbol());
    auto mod = std::make_shared<ir::Module>(exportName, uuid);
    auto st  = std::make_shared<ContextState::StackType>();
    auto state =
        std::shared_ptr<ContextState>(new ContextState(st, mod, nullptr));

    ctx->withState(state, [filePath = filePath, this]() mutable {
        std::ifstream ifs(filePath.string());
        assert(!ifs.fail());

        std::string content((std::istreambuf_iterator<char>(ifs)),
                            (std::istreambuf_iterator<char>()));

        auto srcInfo = new SourceInfo(content, filePath);
        auto lexer   = new Lexer(srcInfo);
        lexer->tokenize();

        if (lexer->tokens.size() != 0) {
            auto parser = new parser::Parser(lexer->tokens, srcInfo);
            auto ast    = parser->parse();
            ctx->module->setSourceInfo(srcInfo);

            visit(ast);

            auto typeChecker = new codegen::TypeChecker(ctx->module);
            typeChecker->codegen();

            // TODO: set a new module to the import cache
            addModule(ctx->module);
        }
    });

    auto item = std::make_shared<Item>(mod);
    ctx->addItem(exportName, item);
}

} // namespace Syntax
} // namespace snowball