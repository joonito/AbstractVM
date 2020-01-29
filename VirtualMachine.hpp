#ifndef VIRTUALMACHINE_HPP
#define VIRTUALMACHINE_HPP

#include "IOperand.hpp"
#include "Lexer.hpp"
#include "Token.hpp"
#include <deque>
#undef assert

#define INT8 "int8"
#define INT16 "int16"
#define INT32 "int32"
#define FLOAT "float"
#define DOUBLE "double"

class VirtualMachine {
    private:
        std::deque<IOperand const *> stack;
        bool vmErr;
        bool lexErr;
        bool parseErr;
        bool stdInput;

        void setError(void);
        bool checkStdInput(void) const;

        void pop(void);
        void dump(void);
        void add(void);
        void sub(void);
        void mul(void);
        void div(void);
        void mod(void);
        void print(void);

        void push(Token const * token);
        void assert(Token const * token);

        Token const * getNextToken(std::deque<Token const * > & tokens);
        std::deque<Token const *> getNextInst(std::deque<std::deque<Token const *> > & instructions);
        IOperand const * dataToOperand(std::string const &data);
    public:
        VirtualMachine();
        VirtualMachine(bool stdInput, bool lexErr, bool parseErr);
        VirtualMachine(const VirtualMachine & other);
        ~VirtualMachine();
        VirtualMachine & operator = (const VirtualMachine &rhs);

        void runInstruction(std::deque<std::deque<Token const * > > & instructions);
        bool hasError(void) const;
        void setLexParseErr(bool lexErr, bool parseErr);
};


#endif