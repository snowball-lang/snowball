
#include "../../ast/types/DefinedType.h"
#include "../../ast/types/FunctionType.h"
#include "../../ast/types/PrimitiveTypes.h"
#include "../../ast/types/TypeAlias.h"
#include "../../common.h"
#include "../../srci/DBGSourceInfo.h"

#include "../ModuleHolder.h"
#include "../values/Argument.h"
#include "../values/Call.h"
#include "../values/Cast.h"
#include "../values/Conditional.h"
#include "../values/Constants.h"
#include "../values/Dereference.h"
#include "../values/Func.h"
#include "../values/IndexExtract.h"
#include "../values/ReferenceTo.h"
#include "../values/Return.h"
#include "../values/Throw.h"
#include "../values/Value.h"
#include "../values/ValueExtract.h"
#include "../values/WhileLoop.h"

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
    SharedValue<Func> createFunction(DBGSourceInfo* dbgInfo, std::string name,
                                     bool isExtern = false, bool isVarArg = false);
    SharedValue<Func> createFunction(DBGSourceInfo* dbgInfo, std::string name,
                                     Func::FunctionArgs args, bool isExtern = false,
                                     bool isVarArg = false);
    SharedValue<Func> createFunction(DBGSourceInfo* dbgInfo, std::string name,
                                     SharedValue<Block> block, Func::FunctionArgs args,
                                     bool isExtern = false, bool isVarArg = false);
    SharedValue<Func> createFunction(DBGSourceInfo* dbgInfo, std::string name,
                                     SharedValue<Block> block, bool isExtern = false,
                                     bool isVarArg = false);
    /// @brief Create a new cast
    SharedValue<Cast> createCast(DBGSourceInfo* dbgInfo, SharedValue<> value, Type<> type);
    /// @brief Create a new index extract
    SharedValue<IndexExtract> createIndexExtract(DBGSourceInfo* dbgInfo, SharedValue<> value,
                                                 types::DefinedType::ClassField* field,
                                                 unsigned int index);
    /// @brief Create a new argument value with the default parameters
    SharedValue<Argument> createArgument(DBGSourceInfo* dbgInfo, const std::string& name,
                                         Type<> type = nullptr);
    /// @brief Create a new argument value
    SharedValue<Argument> createArgument(DBGSourceInfo* dbgInfo, const std::string& name, int index,
                                         AST(Expression::Base) defaultValue = nullptr);
    /// @brief Create a new argument value and set a type to it
    SharedValue<Argument> createArgument(DBGSourceInfo* dbgInfo, const std::string& name, int index,
                                         Type<> type, AST(Expression::Base) defaultValue = nullptr);
    /// @brief Create a new variable
    SharedValue<Variable> createVariable(DBGSourceInfo* dbgInfo, const std::string& identifier,
                                         bool isArgument = false, bool isMutable = false);
    /// @brief Create a new variable and set a type to it
    SharedValue<Variable> createVariable(DBGSourceInfo* dbgInfo, const std::string& identifier,
                                         Type<> type, bool isArgument = false,
                                         bool isMutable = false);
    /// @brief Create a new block
    SharedValue<Block> createBlock(DBGSourceInfo* dbgInfo, std::vector<SharedValue<>> values);
    /// @brief Create a new empty block
    SharedValue<Block> createBlock(DBGSourceInfo* dbgInfo);
    /// @brief Create a new throw instruction
    SharedValue<Throw> createThrow(DBGSourceInfo* dbgInfo, SharedValue<> value);
    /// @brief Create a new reference to a value (pointer)
    SharedValue<ReferenceTo> createReferenceTo(DBGSourceInfo* dbgInfo, SharedValue<> value);
    /// @brief Create a new dereference to a value (pointer)
    SharedValue<DereferenceTo> createDereferenceTo(DBGSourceInfo* dbgInfo, SharedValue<> value,
                                                   Type<> type);
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
                                                               SharedValue<>
                                                                       value,
                                                               bool isMutable = false);
    /// @brief Create a extraction node from a value
    SharedValue<ValueExtract> createValueExtract(DBGSourceInfo* dbgInfo, SharedValue<> value);
    /// @brief Create a object initialization node
    SharedValue<ObjectInitialization> createObjectInitialization(
            DBGSourceInfo* dbgInfo, SharedValue<> value, ValueVec<> args, bool atHeap = false);
    /// @brief Create a object initialization node with an already created object
    SharedValue<ObjectInitialization>
    createObjectInitialization(DBGSourceInfo* dbgInfo, SharedValue<> value, ValueVec<> args,
                               SharedValue<> createdObject, bool atHeap = false);
    /// @brief Create a new conditional instruction (if/else)
    SharedValue<Conditional> createConditional(DBGSourceInfo* dbgInfo, SharedValue<> condition,
                                               SharedValue<Block> thenBlock,
                                               SharedValue<Block> elseBlock);
    /// @brief Create a new while loop
    SharedValue<WhileLoop> createWhileLoop(DBGSourceInfo* dbgInfo, SharedValue<> condition,
                                           SharedValue<Block> body, bool isDoWhile = false);
    /// @brief Create a new binary operation
    /// @todo add more overloads for the binary operation
    SharedValue<BinaryOp> createBinaryOp(SharedValue<Call> call);
    /// @brief Create a new function type
    Type<types::FunctionType> createFunctionType(std::vector<Type<>> args, Type<> retType,
                                                 bool isVarArg = false, bool isMutable = false);
    /// @brief Create a new type alias
    Type<types::TypeAlias> createTypeAlias(DBGSourceInfo* dbg, std::string name, Type<> base);

    /// @brief Utility function to create a new instruction
    template <typename DesiredType, typename... Args>
    std::shared_ptr<DesiredType> N(DBGSourceInfo* dbg, Args&&... args) {
        return module->N<DesiredType>(dbg, std::forward<Args>(args)...);
    }
};
} // namespace ir
} // namespace snowball

#undef TYPE
#undef AST
#endif // __SNOWBALL_IR_BUILDER_H_
