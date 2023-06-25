
#include "../../ast/syntax/nodes.h"
#include "../../ast/types/DefinedType.h"
#include "../../ast/types/FunctionType.h"
#include "../../ast/visitor/Visitor.h"
#include "../../ir/module/Module.h"
#include "../../ir/values/Argument.h"
#include "../../ir/values/Call.h"
#include "../../ir/values/Constants.h"
#include "../../ir/values/Func.h"
#include "../../ir/values/Return.h"
#include "../../ir/values/ValueExtract.h"
#include "../../utils/utils.h"
#include "../Analyzer.h"

#include <assert.h>
#include <map>
#include <memory>
#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

#ifndef __SNOWBALL_DEFINITE_ASSIGMENT_ANALYZER_H_
#define __SNOWBALL_DEFINITE_ASSIGMENT_ANALYZER_H_

#define ACCEPT(Node)                      virtual void visit(Node* p_node) override;
#define SN_DEFINITE_ASSIGMENT_VISIT(Node) void DefiniteAssigment::visit(Node* p_node)

namespace snowball {
namespace Syntax {

/**
 * A class that extends the AcceptorExtend class and implements the
 * Analyzer interface to perform definite assignment analysis on a given
 * program. Definite assignment analysis determines whether a variable
 * has been definitely assigned a value before it is used in the
 * program. This class provides an implementation for the analysis
 * algorithm.
 *
 * Inherits from:
 *   - AcceptorExtend: A template class that provides an implementation
 * for the Visitor design pattern.
 *   - Analyzer: An interface that defines the methods required for
 * performing program analysis.
 */
class DefiniteAssigment : public Analyzer {
    /**
     * @brief A context utility to make sure that the current node being
     *  visited is inside a class.
     */
    std::optional<Statement::ClassDef*> insideClass = std::nullopt;
    /**
     * An enumeration that defines the possible reference status values
     * for a variable in the analyzed program. The reference status
     * indicates whether the variable has been initialized before it is
     * used in the program.
     *
     * The enum defines two possible values:
     *   - NotInitialized: Indicates that the variable has not been
     * initialized before it is used in the program.
     *   - Initialized: Indicates that the variable has been initialized
     * before it is used in the program.
     *
     * This enum is used in the implementation of the DefiniteAssigment
     * class, which performs definite assignment analysis on a given
     * program.
     */
    enum ReferenceStatus
    {
        NotInitialized = 0x00,
        Initialized = 0x01
    };
    /**
     * A map that associates each variable declared in the analyzed
     * program with its reference status. The reference status indicates
     * whether the variable has been initialized before it is used in
     * the program.
     *
     * The map is implemented using the std::map container, where the
     * keys are of type Statement::VariableDecl, representing the
     * variable declarations in the program, and the values are of type
     * ReferenceStatus, indicating the reference status of each
     * variable.
     *
     * The ReferenceStatus enum defines two possible values for the
     * reference status: NotInitialized and Initialized. The default
     * value for each variable in the map is NotInitialized.
     *
     * This member variable is part of the DefiniteAssigment class and
     * is used in the implementation of the definite assignment analysis
     * algorithm.
     */
    using Scope = std::unordered_map<std::string, ReferenceStatus>;
    /**
     * A list that represents the stack of variable scopes in the
     * analyzed program.
     *
     * Each element in the list is a Scope object, which is a map that
     * associates each variable declared in the current scope with its
     * reference status. The reference status indicates whether the
     * variable has been initialized before it is used in the program.
     *
     * The Scope object is implemented using the std::map container,
     * where the keys are of type Statement::VariableDecl, representing
     * the variable declarations in the current scope, and the values
     * are of type ReferenceStatus, indicating the reference status of
     * each variable.
     *
     * The ReferenceStatus enum defines two possible values for the
     * reference status: NotInitialized and Initialized. The default
     * value for each variable in the Scope object is NotInitialized.
     *
     * This member variable is part of the DefiniteAssigment class and
     * is used in the implementation of the definite assignment analysis
     * algorithm to keep track of the current variable scopes in the
     * program.
     */
    std::list<Scope> scopes = {/* global = */ {}};
    /**
     * A struct that represents the state of the current scope in the
     * program.
     *
     * The struct contains a std::vector of std::string objects called
     * inited, which represents the variables that have been initialized
     * in the current scope.
     *
     * This struct is used in the implementation of the withScope and
     * withState functions to keep track of the current variable scope
     * and state, respectively.
     */
    struct {
        std::vector<std::string> inited;
    } state;
    /**
     * A function that executes the given callback function within a new
     * variable scope.
     *
     * The withScope function creates a new scope by pushing a new empty
     * vector of initialized variables onto the scopes vector. The
     * callback function is then executed, and when it returns, the
     * first element of the scopes vector is popped, effectively
     * removing the variables that were initialized in the new scope
     * from the state.
     *
     * @param cb The callback function to be executed within the new
     * scope.
     */
    void withScope(std::function<void()> cb);
    /**
     * A function that executes the given callback function with a copy
     * of the current state.
     *
     * The withState function creates a copy of the current state struct
     * and passes it to the callback function. After the callback
     * function returns, the original state struct is restored.
     *
     * @param cb The callback function to be executed with a copy of the
     * current state.
     */
    void withState(std::function<void()> cb);
    /**
     * A function that executes the given callback function as a new
     * block in the program.
     *
     * The @fn asBlock function executes the callback function within a
     * new variable scope by calling the withScope and the withState
     * function with the callback function as its argument.
     *
     * @param cb The callback function to be executed within a new
     * scope.
     */
    void asBlock(std::function<void()> cb);
    /**
     * A function that returns the declaration statement and reference
     * status of a variable with the given identifier from the class
     * instance.
     *
     * @param x The identifier of the variable to look for.
     * @return An optional object that contains a pair of the
     * declaration statement of the variable and its reference status,
     * if found. Otherwise, an empty optional is returned.
     */
    std::optional<std::pair<std::string, DefiniteAssigment::ReferenceStatus>>
    getIdentifier(std::string x);

#include "../../defs/accepts.def"
  public:
    using Analyzer::Analyzer;
    DefiniteAssigment(SourceInfo* srci) : Analyzer(srci){};

    // Default destructor
    ~DefiniteAssigment() noexcept = default;
};

} // namespace Syntax
} // namespace snowball

#undef ACCEPT
#endif // __SNOWBALL_DEFINITE_ASSIGMENT_ANALYZER_H_
