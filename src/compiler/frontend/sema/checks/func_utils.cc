
#include "compiler/frontend/ast/nodes.h"
#include "compiler/frontend/sema/check.h"

namespace snowball {
namespace frontend {
namespace sema {

using namespace utils;

ast::FnDecl* TypeChecker::get_best_match(const std::vector<ast::FnDecl*>& decls, const std::vector<ast::types::Type*>& args, 
    const SourceLocation& loc, bool identified) {
  std::vector<ast::FnDecl*> matches;
  if (decls.size() > 1 && identified) {
    err(loc, "Expected arguments provided to function call!", Error::Info {
      .highlight = "Multiple functions overload found for call.",
      .help = "Try calling the function with the correct number of arguments and types",
      .note = "This is because the function call is ambiguous and the compiler cannot determine which function to call"
    });
  } else if (decls.size() == 1 && identified) {
    return decls.at(0);
  }
  for (auto& decl : decls) {
    if (decl->get_params().size() != args.size()) {
      continue;
    }
    bool match = true;
    for (size_t i = 0; i < args.size(); ++i) {
      if (!type_match(decl->get_params().at(i)->get_type(), args.at(i))) {
        match = false;
        break;
      }
    }
    if (match) {
      matches.push_back(decl);
    }
  }
  switch (matches.size()) {
    case 0:
      err(loc, fmt::format("No matching function found for call. Expected a function with the signature: {}",
        fmt::format("({})", join(map<std::string, ast::types::Type*>(args, [](auto x) { return x->get_printable_name(); }), ", "))), Error::Info {
          .highlight = fmt::format("No matching function found for call."),
          .help = "Try calling the function with the correct number of arguments and types",
          .note = fmt::format("Function '{}' does not exist or the function signature does not match the call", 
            decls.at(0)->get_name()),
          .see = "https://snowball-lang.gitbook.io/docs/language-reference/functions"
        });
      return nullptr;
    case 1:
      return matches.at(0);
    default:
      err(loc, fmt::format("Ambiguous call to function '{}'. Multiple functions match the call", decls.at(0)->get_name()), 
        Error::Info {
          .highlight = fmt::format("Ambiguous call to function '{}'. Multiple functions match the call", decls.at(0)->get_name()),
          .help = fmt::format("Try calling the function with the correct number of arguments and types"),
          .note = fmt::format("Multiple functions match the call to '{}'", decls.at(0)->get_name())
        });
      return nullptr;
  }
}
}
}
}
