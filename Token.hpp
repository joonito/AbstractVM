#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <string>

enum class tokenType {
    comment,
    instruction,
    unaryInstruction,
    operand,
    unknown,
};

class Token {
    public:
        Token();
        Token(tokenType type, std::string const & value);
        Token(const Token & other);
        ~Token();
        Token &operator = (const Token &rhs);

        tokenType getType(void) const;
        std::string getValue(void) const;
        
    private:
        tokenType type;
        std::string value;
};

#endif