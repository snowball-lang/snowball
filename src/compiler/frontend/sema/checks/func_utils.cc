
#include "compiler/frontend/ast/nodes.h"
#include "compiler/frontend/sema/check.h"

namespace snowball {
namespace frontend {
namespace sema {

using namespace utils;

ast::FnDecl* TypeChecker::get_best_match(const std::vector<ast::FnDecl*>& decls, const std::vector<ast::types::Type*>& args, 
    const SourceLocation& loc, const std::vector<ast::TypeRef>& generics, bool identified) {
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
      if (decl->get_params().at(i)->get_type()->is_deep_generic()) continue;
      if (can_cast(args.at(i), decl->get_params().at(i)->get_type()) == CastType::Invalid) {
        // TODO: different casts can have different costs
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
    case 1: {
      auto match = matches.at(0);
      return deduce_func(match, args, loc, generics);
    }
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

ast::FnDecl* TypeChecker::deduce_func(ast::FnDecl* node, const std::vector<ast::types::Type*>& args, 
                                    const SourceLocation& loc, const std::vector<ast::TypeRef>& generics) {
  if (node->get_generics().size() == 0) {
    return node;
  }
  std::map<std::string, ast::types::Type*> deduced;
  for (size_t i = 0; i < generics.size(); ++i) {
    auto gen = node->get_generics().at(i);
    auto arg = get_type(generics.at(i));
    deduced[gen.get_name()] = arg;
  }
  std::function<void(const ast::VarDecl*, ast::types::Type*, ast::types::Type*, bool)> check_generic = [&](auto param, auto pgen, auto arg, auto already_checked) {
    if (auto cls = pgen->as_class(); cls && !already_checked) {
      check_generic(param, cls, arg, true);
      if (auto cls_arg = arg->as_class()) {
        if (cls->get_generics().size() != cls_arg->get_generics().size()) {
          return;
        }
        for (size_t i = 0; i < cls->get_generics().size(); ++i) {
          check_generic(param, cls->get_generics().at(i), cls_arg->get_generics().at(i), false);
        }
      }
      return;
    }
    if (!pgen->is_generic()) return;
    auto gen = pgen->as_generic();
    if (deduced.find(gen->get_name()) != deduced.end()) {
      if (!type_match(deduced[gen->get_name()], arg)) {
        err(loc, fmt::format("Type mismatch for generic parameter '{}'. Expected type '{}' but got type '{}'", 
          gen->get_name(), deduced[gen->get_name()]->get_printable_name(), arg->get_printable_name()), Error::Info {
            .highlight = fmt::format("Type mismatch for generic parameter '{}'. Expected type '{}' but got type '{}'", 
              gen->get_name(), deduced[gen->get_name()]->get_printable_name(), arg->get_printable_name()),
            .help = fmt::format("Try calling the function with the correct number of arguments and types")
          });
      }
      return;
    }
    deduced[gen->get_name()] = arg;
  };
  for (size_t i = 0; i < args.size(); ++i) {
    auto param = node->get_params().at(i);
    auto arg = args.at(i);
    check_generic(param, param->get_type(), arg, false);
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
    auto monorphs = generic_registry[node->get_id()];
    // used for caching generic functions and prevent rechecking every time
    for (auto& monorph : monorphs) {
      assert(deduced.size() == monorph.generics.size());
      size_t i = 0;
      if (std::find_if(monorph.generics.begin(), monorph.generics.end(), [&](auto& gen) {
        i++;
        return type_match(gen.second, deduced.at(gen.first));
      }) != monorph.generics.end()) {
        return monorph.decl;
      }
    }
  }
  auto decl = (ast::FnDecl*)node->clone();
  return monorphosize(decl, deduced, loc);
}

void TypeChecker::add_self_param(ast::FnDecl*& node) {
  auto current_class = ctx.current_class;
  if (node->get_static() || !current_class) return;
  auto& params = node->get_params();
  if (params.size() > 0 && params[0]->get_name() == "self") return; // already has a self param
  auto self = ast::VarDecl::create(node->get_location(), "self", std::nullopt, std::nullopt);
  self->set_used();
  unify(self->get_type(), current_class->get_type()->get_reference_to(), node->get_location());
  params.insert(params.begin(), self);
  node->get_type()->as_func()->get_param_types().insert(node->get_type()->as_func()->get_param_types().begin(), self->get_type());
}

}
}
}
