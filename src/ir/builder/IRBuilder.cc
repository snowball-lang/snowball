
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
(DBGSourceInfo* dbgInfo, std::string name, Func::FunctionArgs args, bool isExtern, bool isVarArg) {
    return module->N<Func>(dbgInfo, name, args, isExtern, isVarArg);
}
SharedValue<Func> IRBuilder::createFunction(DBGSourceInfo* dbgInfo, std::string name, SharedValue<Block> block, Func::FunctionArgs args, 
                                bool isExtern, bool isVarArg) {
    return module->N<Func>(dbgInfo, name, block, args, isExtern, isVarArg);
}
SharedValue<Func> IRBuilder::createFunction(DBGSourceInfo* dbgInfo, std::string name, SharedValue<Block> block, 
                                bool isExtern, bool isVarArg) {
    return createFunction(dbgInfo, name, block, {}, isExtern, isVarArg);
}
SharedValue<Cast> IRBuilder::createCast(DBGSourceInfo* dbgInfo, SharedValue<> value, Type<> type) {
    auto cast = module->N<Cast>(dbgInfo, value, type);
    cast->setType(type);
    return cast;
}
SharedValue<IndexExtract> IRBuilder::createIndexExtract(DBGSourceInfo* dbgInfo, SharedValue<> value, types::DefinedType::ClassField* field,
                                           unsigned int index) {
    auto indexExtract = module->N<IndexExtract>(dbgInfo, value, field, index);
    indexExtract->setType(field->type);
    return indexExtract;
}
SharedValue<Argument> IRBuilder::createArgument(DBGSourceInfo* dbgInfo, const std::string& name, int index,
                                       Syntax::Expression::Base* defaultValue) {
    return module->N<Argument>(dbgInfo, name, index, defaultValue);
}
SharedValue<Argument> IRBuilder::createArgument(DBGSourceInfo* dbgInfo, const std::string& name, int index,
                                    Type<> type,
                                   Syntax::Expression::Base* defaultValue) {
    auto arg = createArgument(dbgInfo, name, index, defaultValue);
    arg->setType(type);
    return arg;
}
SharedValue<Variable> IRBuilder::createVariable(DBGSourceInfo* dbgInfo, const std::string& identifier,
                                       bool isArgument, bool isMutable) {
    return module->N<Variable>(dbgInfo, identifier, isArgument, isMutable);
}
SharedValue<Variable> IRBuilder::createVariable(DBGSourceInfo* dbgInfo, const std::string& identifier, Type<> type,
                                bool isArgument, bool isMutable) {
    auto var = createVariable(dbgInfo, identifier, isArgument, isMutable);
    var->setType(type);
    return var;
}
SharedValue<Block> IRBuilder::createBlock(DBGSourceInfo* dbgInfo) {
    return createBlock(dbgInfo, {});
}
SharedValue<Block> IRBuilder::createBlock(DBGSourceInfo* dbgInfo, std::vector<SharedValue<>> values) {
    return module->N<Block>(dbgInfo, values);
}
SharedValue<ReferenceTo> IRBuilder::createReferenceTo(DBGSourceInfo* dbgInfo, SharedValue<> value) {
    auto ref = module->N<ReferenceTo>(dbgInfo, value);
    ref->setType(value->getType()->getPointerTo());
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
SharedValue<Return> IRBuilder::createReturn(DBGSourceInfo* dbgInfo, SharedValue<> value) {
    auto ret = module->N<Return>(dbgInfo, value);
    if (value) ret->setType(value->getType());
    return ret;
}
SharedValue<Return> IRBuilder::createVoidReturn(DBGSourceInfo* dbgInfo) {
    return module->N<Return>(dbgInfo, nullptr);
}
SharedValue<Call> IRBuilder::createCall(DBGSourceInfo* dbgInfo, SharedValue<> callee, ValueVec<> args) {
    return module->N<Call>(dbgInfo, callee, args);
}
SharedValue<VariableDeclaration> IRBuilder::createVariableDeclaration(DBGSourceInfo* dbgInfo,
                                                        const std::string identifier,
                                                        SharedValue<> value, bool isMutable) {
    auto decl = module->N<VariableDeclaration>(dbgInfo, identifier, value, isMutable);
    decl->setType(value->getType());
    return decl;
}
SharedValue<ValueExtract> IRBuilder::createValueExtract(DBGSourceInfo* dbgInfo, SharedValue<> value) {
    auto extract = module->N<ValueExtract>(dbgInfo, value);
    extract->setType(value->getType());
    return extract;
}
SharedValue<ObjectInitialization> IRBuilder::createObjectInitialization(DBGSourceInfo* dbgInfo, SharedValue<> value,
                                                        ValueVec<> args, bool atHeap) {
    auto init = module->N<ObjectInitialization>(dbgInfo, value, args);
    init->initializeAtHeap = atHeap;
}
SharedValue<ObjectInitialization> IRBuilder::createObjectInitialization(DBGSourceInfo* dbgInfo, SharedValue<> value,
                                                        ValueVec<> args, SharedValue<> createdObject, bool atHeap) {
    auto init = createObjectInitialization(dbgInfo, value, args, atHeap);
    init->createdObject = createdObject;
    return init;
}
SharedValue<Conditional> IRBuilder::createConditional(DBGSourceInfo* dbgInfo, SharedValue<> condition,
                                        SharedValue<Block> thenBlock, SharedValue<Block> elseBlock) {
    return module->N<Conditional>(dbgInfo, condition, thenBlock, elseBlock);
}
SharedValue<WhileLoop> IRBuilder::createWhileLoop(DBGSourceInfo* dbgInfo, SharedValue<> condition, SharedValue<Block> body) {
    return module->N<WhileLoop>(dbgInfo, condition, body);
}

} // namespace ir
} // namespace snowball