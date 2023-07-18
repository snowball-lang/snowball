#include "../../../../ir/values/Cast.h"
#include "../../../Transformer.h"

#include <filesystem>

using namespace snowball::utils;
using namespace snowball::Syntax::transform;
namespace fs = std::filesystem;

namespace snowball {
namespace Syntax {

SN_TRANSFORMER_VISIT(Expression::PseudoVariable) {
    std::string stringValue;
    std::string pseudo = p_node->getIdentifier();

    if (pseudo == "FN") {
        if (auto x = ctx->getCurrentFunction()) {
            stringValue = x->getNiceName();
        } else {
            E<PSEUDO_ERROR>(p_node, "Can't use @FN pseudo variable outside a function!");
        }
    } else if (pseudo == "MANGLED_FN") {
        if (auto x = ctx->getCurrentFunction()) {
            stringValue = x->getMangle();
        } else {
            E<PSEUDO_ERROR>(p_node,
                            "Can't use @MANGLED_FN pseudo variable outside "
                            "a function!");
        }
    } else if (pseudo == "MOD") {
        stringValue = ctx->module->getName();
    } else if (pseudo == "CLASS") {
        if (auto x = ctx->getCurrentClass()) {
            stringValue = x->getPrettyName();
        } else {
            E<PSEUDO_ERROR>(p_node, "Can't use @CLASS pseudo variable outside a class!");
        }
    } else if (pseudo == "FILE") {
        stringValue = getSourceInfo()->getPath();
    } else if (pseudo == "LINE") {
        stringValue = std::to_string(p_node->getDBGInfo()->pos.first - 1);
    } else if (pseudo == "FILE_LINE") {
        stringValue = getSourceInfo()->getPath() + ":" + std::to_string(p_node->getDBGInfo()->pos.first);
    } else if (pseudo == "COLUMN") {
        stringValue = std::to_string(p_node->getDBGInfo()->pos.second);
    } else if (pseudo == "SN_VERSION") {
        stringValue = _SNOWBALL_VERSION;
    } else if (pseudo == "SN_FOLDER") {
        stringValue = fs::path(get_exe_folder()).remove_filename();
    } else if (auto [item, found] = ctx->getItem(pseudo); found) {
        auto macro = item->getMacro();
        if (!p_node->asStatement && macro->isMacroStatement()) {
            E<PSEUDO_ERROR>(p_node, FMT("Macro '%s' is not an expression!", pseudo.c_str()),
             {
                .info = "Trying to use a statement macro as an expression macro.",
                .note = "You can't use a statement macro as an expression macro.\n"
                        "You can use the macro as a statement instead.",
                .help = "Try using the macro as a statement instead or declare the\n"
                        "macro as an expression macro.",
                .tail = EI<>(macro->getDBGInfo(), "", {
                    .info = "Macro declaration here.",
                })
             });
        } 
        transformMacro(p_node, macro);
        return;
    } else {
        if (auto parent = ctx->currentMacroInstance) {
            auto arg = parent->stack.find(pseudo);
            if (arg != parent->stack.end()) {
                trans((*arg).second);
                return;
            }
        }

        E<PSEUDO_ERROR>(p_node, FMT("Pseudo variable with name '%s' hasn't been found!", pseudo.c_str()));
    }

    // We add " to both sides because the generator removes them and we
    // prevent the values
    //  from being lost.
    auto val = new Syntax::Expression::ConstantValue(Expression::ConstantValue::ConstantType::String,
                                                     "\"" + stringValue + "\"");
    trans(val);
}

} // namespace Syntax
} // namespace snowball