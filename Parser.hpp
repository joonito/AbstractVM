#ifndef PARSER_HPP
#define PARSER_HPP

#include <deque>
#include "IOperand.hpp"
#include "Token.hpp"

class Parser {
    public:
        Parser();
        Parser(bool stdIn);
        Parser(const Parser & other);
        ~Parser();
        Parser &operator = (const Parser &rhs);

        void tokenEvaluator(std::deque<Token const *> & tokens);
        bool hasError(void) const;

    private:
        bool parseErr;
        bool stdInput;
        void setError(void);
        bool checkStdInput(void) const;

};

#endif