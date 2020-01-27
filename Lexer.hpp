#ifndef LEXER_HPP
#define LEXER_HPP

#include "IOperand.hpp"
#include "Token.hpp"
#include <regex>

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
#define TERMINATE ";;"

#define INT8PATTERN "int8\\({1}-?\\d+\\){1}"
#define INT16PATTERN "int16\\({1}-?\\d+\\){1}"
#define INT32PATTERN "int32\\({1}-?\\d+\\){1}"
#define FLOATPATTERN "float\\({1}-?\\d+\\.{1}\\d+\\){1}"
#define DOUBLEPATTERN "double\\({1}-?\\d+\\.{1}\\d+\\){1}"


class Lexer {
    public:
        Lexer();
        Lexer(const Lexer & other);
        Lexer(bool stdIn);
        ~Lexer();
        Lexer & operator = (const Lexer &rhs);

        std::deque<Token const *> tokenizer(std::string const & line);
        bool hasError(void) const;

    private:

        bool lexErr;
        bool stdInput;
        bool lineErr;

        Token const * createToken(std::string const &word, bool comment = false);
        std::deque<std::string> splitter(std::string const &line, char delim) const;
        void removeUseless(std::deque<Token const *> & tokens);        
        void setError(void);
        bool checkStdInput(void) const;
};

#endif