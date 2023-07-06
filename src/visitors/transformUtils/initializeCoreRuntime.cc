#include "../../ast/syntax/nodes.h"
#include "../Transformer.h"

#include <fstream>
#include "../../lexer.h"
#include "../../parser/Parser.h"
#include "../../utils/utils.h"
#include "../../visitors/Analyzer.h"
#include "../../visitors/Transformer.h"
#include "../../visitors/TypeChecker.h"
#include "../../visitors/analyzers/DefinitveAssigment.h"

using namespace snowball::utils;
using namespace snowball::Syntax::transform;

namespace snowball {
namespace Syntax {

void Transformer::initializeCoreRuntime() {
    auto [filePath, error] = ctx->imports->getImportPath("Core", {"_$core"});
    if (!error.empty()) { E<IO_ERROR>(error); }
    // clang-format off
    std::ifstream ifs(filePath.string());
    assert(!ifs.fail());
    std::string content((std::istreambuf_iterator<char>(ifs)),
                        (std::istreambuf_iterator<char>()));
    auto srcInfo = new SourceInfo(content, filePath);
    auto lexer = new Lexer(srcInfo);
    lexer->tokenize();
    auto tokens = lexer->tokens;
    if (tokens.size() != 0) {
        auto parser = new parser::Parser(tokens, srcInfo);
        auto ast = parser->parse();
        ctx->module->setSourceInfo(srcInfo);
        visitGlobal(ast);
        // TODO: make this a separate function to avoid any sort of "conflict" with the compiler's version of this algorithm
        std::vector<Syntax::Analyzer *> passes = {
            new Syntax::DefiniteAssigment(srcInfo)};
        for (auto pass : passes)
            pass->run(ast);
        auto typeChecker = new codegen::TypeChecker(ctx->module);
        typeChecker->codegen();
    }
}

} // namespace Syntax
} // namespace snowball