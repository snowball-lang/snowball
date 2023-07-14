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
        stringValue =
                getSourceInfo()->getPath() + ":" + std::to_string(p_node->getDBGInfo()->pos.first);
    } else if (pseudo == "COLUMN") {
        stringValue = std::to_string(p_node->getDBGInfo()->pos.second);
    } else if (pseudo == "SN_VERSION") {
        stringValue = _SNOWBALL_VERSION;
    } else if (pseudo == "SN_FOLDER") {
        stringValue = fs::path(get_exe_folder()).remove_filename();
    } else {
        E<PSEUDO_ERROR>(p_node,
                        FMT("Pseudo variable with name '%s' hasn't been found!", pseudo.c_str()));
    }

    // We add " to both sides because the generator removes them and we
    // prevent the values
    //  from being lost.
    auto val = new Syntax::Expression::ConstantValue(
            Expression::ConstantValue::ConstantType::String, "\"" + stringValue + "\"");
    trans(val);
}

} // namespace Syntax
} // namespace snowball