
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
    matches.push_back(decls.at(0));
  }
  for (auto& decl : decls) {
    if (decl->get_params().size() != args.size() || identified) 
      continue;
    bool match = true;
    for (size_t i = 0; i < args.size(); ++i) {
      if (decl->get_params().at(i)->get_type()->is_generic()) continue;
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
          .note = fmt::format("Function '{}' DOES exist but the arguements provided does not match any signature.", 
            decls.at(0)->get_name()),
          .see = "https://snowball-lang.gitbook.io/docs/language-reference/functions"
        });
      return nullptr;
    case 1:
      return deduce_func(matches.at(0), args, loc);
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

ast::FnDecl* TypeChecker::deduce_func(ast::FnDecl* node, const std::vector<ast::types::Type*>& args, const SourceLocation& loc) {
  if (node->get_generics().size() == 0) {
    return node;
  }
  std::map<std::string, ast::types::Type*> deduced;
  for (size_t i = 0; i < args.size(); ++i) {
    auto param = node->get_params().at(i);
    auto arg = args.at(i);
    if (param->get_type()->is_generic()) {
      auto gen = param->get_type()->as_generic();
      if (deduced.find(gen->get_name()) != deduced.end()) {
        if (!type_match(deduced[gen->get_name()], arg)) {
          err(loc, fmt::format("Type mismatch for generic parameter '{}'. Expected type '{}' but got type '{}'", 
            gen->get_name(), deduced[gen->get_name()]->get_printable_name(), arg->get_printable_name()), Error::Info {
              .highlight = fmt::format("Type mismatch for generic parameter '{}'. Expected type '{}' but got type '{}'", 
                gen->get_name(), deduced[gen->get_name()]->get_printable_name(), arg->get_printable_name()),
              .help = fmt::format("Try calling the function with the correct number of arguments and types")
            });
        }
        continue;
      }
      deduced[gen->get_name()] = arg;
    }
  }
  for (auto& gen : node->get_generics()) {
    // TODO: Default generic types implementation here!
    if (deduced.find(gen.get_name()) == deduced.end()) {
      err(loc, fmt::format("Generic parameter '{}' has not been deduced", gen.get_name()), Error::Info {
        .highlight = fmt::format("Coudnt deduce '{}' from call signature", gen.get_name()),
        .help = fmt::format("Try explicitly specifying all generic type parameters"),
        .related = {{ node->get_location(), Error::Info {
          .highlight = fmt::format("Generic parameter '{}' declared here", gen.get_name())
        }}}
      });
    }
  }
  return propagate_generic(node, deduced, loc);
}

ast::FnDecl* TypeChecker::propagate_generic(ast::FnDecl* node, const std::map<std::string, ast::types::Type*>& deduced, const SourceLocation& loc) {
  if (generic_registry.find(node->get_id()) != generic_registry.end()) {
    auto monorph = generic_registry[node->get_id()];
    assert(deduced.size() == monorph.generics.size());
    size_t i = 0;
    if (std::find_if(monorph.generics.begin(), monorph.generics.end(), [&](auto& gen) {
      i++;
      return type_match(gen.second, deduced.at(gen.first));
    }) != monorph.generics.end()) {
      err(loc, "Generic parameters not fully deduced", Error::Info {
        .highlight = "Generic parameters not fully deduced",
        .help = "Try explicitly specifying all generic type parameters",
        .related = {{ node->get_location(), Error::Info {
          .highlight = "Generic parameters declared here"
        }}}
      });
    }
  }
  auto decl = node->clone();
  decl->get_type() = nullptr;
  decl->increment_id();
  decl->clear_generics();
  generic_registry[node->get_id()] = MonorphosizedFn {
    .decl = node,
    .generics = deduced
  };
  sn_assert(false, "not implemented (generic propagation)");
  return decl;
}

}
}
}
