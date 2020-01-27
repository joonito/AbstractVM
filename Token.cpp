#include "Token.hpp"

Token::Token() : type(tokenType::unknown), value("unknown"){
}

Token::Token(tokenType type, std::string const & value) : type(type), value(value){    
}

Token::~Token() {
}

Token::Token(const Token & other) : type(other.type), value(other.value){
}

Token &Token::operator = (const Token &rhs) {
    if (this != &rhs) {
        this->type = rhs.type;
        this->value = rhs.value;
    }
    return *this;
}

tokenType Token::getType(void) const {
    return this->type;
}

std::string Token::getValue(void) const {
    return this->value;
}
