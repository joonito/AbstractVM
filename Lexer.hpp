#ifndef LEXER_HPP
#define LEXER_HPP

#include "IOperand.hpp"

#define PUSH "push"
#define POP "pop"
#define DUMP "dump"
#define ASSERT "assert"
#define ADD "add"
#define SUB "sub"
#define MUL "mul"
#define DIV "div"
#define MOD "mod"
#define PRINT "print"
#define EXIT "exit"

#define INT8 "int8"
#define INT16 "int16"
#define INT32 "int32"
#define FLOAT "float"
#define DOUBLE "double"

enum InstructionType {
    push,
    pop,
    dump,
    assert,
    add,
    sub,
    mul,
    _div,
    mod,
    print,
    _exit,
    unknownInstr
};

class Lexer {
    public:
        Lexer();
        Lexer(const Lexer & other);
        ~Lexer();
        Lexer & operator = (const Lexer &rhs);

        InstructionType instrIdentifier(std::string const &token);
        eOperandType operandIdentifier(std::string const &token, std::string &value);
        bool hasError(void) const;
    
    private:
        std::vector<std::string> tokenizer(std::string const &line, char delim) const;
        bool isNumeric(std::string const &str) const;
        bool lexErr;
        void setError(void);
};

#endif