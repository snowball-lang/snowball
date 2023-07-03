
#include "../../DBGSourceInfo.h"
#include "../../common.h"
#include "../../ast/syntax/nodes.h"
#include "IRBuilder.h"

namespace snowball {
namespace ir {

IRBuilder::IRBuilder(std::shared_ptr<ir::Module> module) {
    setModule(module);
}
SharedValue<Func> IRBuilder::createFunction
(DBGSourceInfo* dbgInfo, std::string name, ValueVec<Argument> args, bool isExtern, bool isVarArg) {
    return module->N<Func>(dbgInfo, name, args, isExtern, isVarArg);
}
SharedValue<Func> IRBuilder::createFunction(DBGSourceInfo* dbgInfo, std::string name, SharedValue<Block> block, ValueVec<Argument> args, 
                                bool isExtern, bool isVarArg) {
    return module->N<Func>(dbgInfo, name, block, args, isExtern, isVarArg);
}
SharedValue<Func> IRBuilder::createFunction(DBGSourceInfo* dbgInfo, std::string name, SharedValue<Block> block, 
                                bool isExtern = false, bool isVarArg = false) {
    return createFunction(dbgInfo, name, block, {}, isExtern, isVarArg);
}
SharedValue<Func> IRBuilder::createCast(DBGSourceInfo* dbgInfo, SharedValue<> value, Type<> type) {
    return module->N<Cast>(dbgInfo, value, type);
}
SharedValue<IndexExtract> createIndexExtract(DBGSourceInfo* dbgInfo, types::DefinedType::ClassField* value,
                                           unsigned int index) {
    return module->N<IndexExtract>(dbgInfo, value, index);
}
SharedValue<Argument> IRBuilder::createArgument(DBGSourceInfo* dbgInfo, std::string name, Type<> type,
                                       Syntax::Expression::Base* defaultValue) {
    return module->N<Argument>(dbgInfo, name, type, defaultValue);
}
SharedValue<Variable> IRBuilder::createVariable(DBGSourceInfo* dbgInfo, const std::string& identifier,
                                       bool isArgument, bool isMutable) {
    return module->N<Variable>(dbgInfo, identifier, isArgument, isMutable);
}
SharedValue<Block> IRBuilder::createBlock(DBGSourceInfo* dbgInfo) {
    return createBlock(dbgInfo, {});
}
SharedValue<Block> IRBuilder::createBlock(DBGSourceInfo* dbgInfo, std::vector<SharedValue<>> values) {
    return module->N<Block>(dbgInfo, values);
}
SharedValue<ReferenceTo> IRBuilder::createReferenceTo(DBGSourceInfo* dbgInfo, SharedValue<> value) {
    return module->N<ReferenceTo>(dbgInfo, value);
}
SharedValue<BinaryOp> createBinaryOp(DBGSourceInfo* dbgInfo, SharedValue<> left, SharedValue<> right,
                                   Syntax::Expression::BinaryOp::OpType* opType, bool isUnary ) {
    return module->N<BinaryOp>(dbgInfo, left, right, opType, isUnary);
}
SharedValue<StringValue> IRBuilder::createStringValue(DBGSourceInfo* dbgInfo, const std::string value) {
    return module->N<StringValue>(dbgInfo, value);
}
SharedValue<NumberValue> IRBuilder::createNumberValue(DBGSourceInfo* dbgInfo, snowball_int_t value) {
    return module->N<NumberValue>(dbgInfo, value);
}
SharedValue<FloatValue> IRBuilder::createFloatValue(DBGSourceInfo* dbgInfo, double value) {
    return module->N<FloatValue>(dbgInfo, value);
}  
SharedValue<BooleanValue> IRBuilder::createBooleanValue(DBGSourceInfo* dbgInfo, bool value) {
    return module->N<BooleanValue>(dbgInfo, value);
}
SharedValue<CharValue> IRBuilder::createCharValue(DBGSourceInfo* dbgInfo, char value) {
    return module->N<CharValue>(dbgInfo, value);
}
SharedValue<Return> createReturn(DBGSourceInfo* dbgInfo, SharedValue<> value);
/// @brief Create a new void return instruction
SharedValue<Return> createVoidReturn(DBGSourceInfo* dbgInfo);
/// @brief Create a new call instruction
SharedValue<Call> createCall(DBGSourceInfo* dbgInfo, SharedValue<> callee, ValueVec<> args);


} // namespace ir
} // namespace snowball