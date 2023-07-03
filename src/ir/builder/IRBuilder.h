
#include "../../DBGSourceInfo.h"
#include "../../ast/types/PrimitiveTypes.h"
#include "../../ast/types/DefinedType.h"
#include "../../common.h"

#include "../ModuleHolder.h"
#include "../values/Value.h"
#include "../values/Call.h"
#include "../../ir/values/Argument.h"
#include "../../ir/values/Constants.h"
#include "../../ir/values/Func.h"
#include "../../ir/values/Return.h"
#include "../../ir/values/ValueExtract.h"

#include <list>
#include <unordered_map>

#ifndef __SNOWBALL_IR_BUILDER_H_
#define __SNOWBALL_IR_BUILDER_H_
#define AST(x) Syntax::x*

namespace snowball {
namespace ir {

template <typename ValueType = Value>
using SharedValue = std::shared_ptr<ValueType>;

template <class TypeName = types::Type>
using Type = std::shared_ptr<TypeName>;

template <typename ValueType = Value>
using ValueVec = std::vector<SharedValue<ValueType>>;

/// @brief IRBuilder is a utility class to create new instructions
class IRBuilder : public AcceptorExtend<IRBuilder, ModuleHolder> {
    friend ModuleHolder;
  public:
    IRBuilder() = default;
    IRBuilder(std::shared_ptr<ir::Module> module);

    /// @brief Create a new function
    SharedValue<Func> createFunction(DBGSourceInfo* dbgInfo, std::string name, ValueVec<Argument> args, 
                                    bool isExtern = false, bool isVarArg = false);
    SharedValue<Func> createFunction(DBGSourceInfo* dbgInfo, std::string name, SharedValue<Block> block, ValueVec<Argument> args, 
                                    bool isExtern = false, bool isVarArg = false);
    SharedValue<Func> createFunction(DBGSourceInfo* dbgInfo, std::string name, SharedValue<Block> block, 
                                    bool isExtern = false, bool isVarArg = false);
    /// @brief Create a new cast               
    SharedValue<Func> createCast(DBGSourceInfo* dbgInfo, SharedValue<> value, Type<> type);
    /// @brief Create a new index extract
    SharedValue<IndexExtract> createIndexExtract(DBGSourceInfo* dbgInfo, types::DefinedType::ClassField* value,
                                           unsigned int index);
    /// @brief Create a new argument value
    SharedValue<Argument> createArgument(DBGSourceInfo* dbgInfo, std::string name, Type<> type,
                                   AST(Expression::Base) defaultValue = nullptr);
    /// @brief Create a new variable
    SharedValue<Variable> createVariable(DBGSourceInfo* dbgInfo, const std::string& identifier,
                                   bool isArgument = false, bool isMutable = false);
    /// @brief Create a new block
    SharedValue<Block> createBlock(DBGSourceInfo* dbgInfo, std::vector<SharedValue<>> values);
    /// @brief Create a new empty block
    SharedValue<Block> createBlock(DBGSourceInfo* dbgInfo);
    /// @brief Create a new reference to a value (pointer)
    SharedValue<ReferenceTo> createReferenceTo(DBGSourceInfo* dbgInfo, SharedValue<> value);
    /// @brief Create a new binary operation
    SharedValue<BinaryOp> createBinaryOp(DBGSourceInfo* dbgInfo, SharedValue<> left, SharedValue<> right,
                                   AST(Expression::BinaryOp::OpType) opType, bool isUnary = false);
    /// @brief Create a new string value
    SharedValue<StringValue> createStringValue(DBGSourceInfo* dbgInfo, const std::string value);
    /// @brief Create a new number value
    SharedValue<NumberValue> createNumberValue(DBGSourceInfo* dbgInfo, snowball_int_t value);
    /// @brief Create a new float value
    SharedValue<FloatValue> createFloatValue(DBGSourceInfo* dbgInfo, double value);
    /// @brief Create a new boolean value
    SharedValue<BooleanValue> createBooleanValue(DBGSourceInfo* dbgInfo, bool value);
    /// @brief Create a new char value
    SharedValue<CharValue> createCharValue(DBGSourceInfo* dbgInfo, char value);
    /// @brief Create a new return instruction
    SharedValue<Return> createReturn(DBGSourceInfo* dbgInfo, SharedValue<> value);
    /// @brief Create a new void return instruction
    SharedValue<Return> createVoidReturn(DBGSourceInfo* dbgInfo);
    /// @brief Create a new call instruction
    SharedValue<Call> createCall(DBGSourceInfo* dbgInfo, SharedValue<> callee, ValueVec<> args);
    /// @brief Create a new type
    SharedValue<VariableDeclaration> createVariableDeclaration(DBGSourceInfo* dbgInfo,
                                                         const std::string identifier,
                                                         SharedValue<> value, bool isMutable = false);
    /// @brief Create a extraction node from a value
    SharedValue<ValueExtract> createValueExtract(DBGSourceInfo* dbgInfo, SharedValue<> value);
    /// @brief Create a object initialization node
    SharedValue<ObjectInitialization> createObjectInitialization(DBGSourceInfo* dbgInfo, SharedValue<> value,
                                                           ValueVec<> args, bool atHeap = false);
    /// @brief Create a object initialization node with an already created object
    SharedValue<ObjectInitialization> createObjectInitialization(DBGSourceInfo* dbgInfo, SharedValue<> value,
                                                          ValueVec<> args, SharedValue<> createdObject, bool atHeap = false);
    /// @brief Create a new conditional instruction (if/else) 
    SharedValue<Conditional> createConditional(DBGSourceInfo* dbgInfo, SharedValue<> condition,
                                         SharedValue<Block> thenBlock, SharedValue<Block> elseBlock);
    /// @brief Create a new while loop
    SharedValue<WhileLoop> createWhileLoop(DBGSourceInfo* dbgInfo, SharedValue<> condition, SharedValue<Block> body);

    /// @brief Utility function to create a new instruction
    template <typename DesiredType, typename... Args>
    std::shared_ptr<DesiredType> N(DBGSourceInfo* dbg, Args&&... args) {
        return module->N(dbg, std::forward<Args>(args)...);
    }
};
} // namespace ir
} // namespace snowball

#undef TYPE
#undef AST
#endif // __SNOWBALL_IR_BUILDER_H_
