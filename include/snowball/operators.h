
#ifndef __SNOWBALL_OPERATORS_H_
#define __SNOWBALL_OPERATORS_H_

namespace snowball {
    enum class OperatorType {
        EQ,
        EQEQ,
        PLUS,
        PLUSEQ,
        MINUS,
        MINUSEQ,
        MUL,
        MULEQ,
        DIV,
        DIVEQ,
        MOD,
        MOD_EQ,
        LT,
        LTEQ,
        GT,
        GTEQ,
        AND,
        OR,
        NOT,
        NOTEQ,
        BIT_NOT,
        BIT_LSHIFT,
        BIT_LSHIFT_EQ,
        BIT_RSHIFT,
        BIT_RSHIFT_EQ,
        BIT_OR,
        BIT_OR_EQ,
        BIT_AND,
        BIT_AND_EQ,
        BIT_XOR,
        BIT_XOR_EQ,

        // other operators
        CONSTRUCTOR,
        DESTRUCTOR, // TODO
        CALL,

        // operator types
        STRING,
        BOOL
    };
}

#endif // __SNOWBALL_OPERATORS_H_