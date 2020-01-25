#include "Lexer.hpp"
#include "Exceptions.hpp"

Lexer::Lexer() {
    lexErr = false;
}

Lexer::Lexer(const Lexer &other) {
    this->lexErr = other.lexErr;
}

Lexer::~Lexer() {
}

Lexer & Lexer::operator=(const Lexer &rhs) {
    if (this != &rhs)
        this->lexErr = rhs.lexErr;
    return *this;
}

InstructionType Lexer::instrIdentifier(std::string const &token) {
    try {
        if (token == PUSH) {
            return push;
        } else if (token == POP) {
            return pop;
        } else if (token == DUMP) {
            return dump;
        } else if (token == ASSERT) {
            return assert;
        } else if (token == ADD) {
            return add;
        } else if (token == SUB) {
            return sub;
        } else if (token == MUL) {
            return mul;
        } else if (token == DIV) {
            return _div;
        } else if (token == MOD) {
            return mod;
        } else if (token == PRINT) {
            return print;
        } else if (token == EXIT) {
            return _exit;
        } else {
            throw UnknownInstructionException(); 
        }
    } catch (UnknownInstructionException& e) {
        std::cout << e.what() << std::endl;
        setError();
    }
    return unknownInstr;
}

eOperandType Lexer::operandIdentifier(std::string const &token, std::string &value) {
    try {
        int lParen = 0;
        int rParen = 0;
        for (std::string::size_type i = 0; i < token.size(); i++) {
            if (token[i] == '(') {
                lParen++;
            } else if (token[i] == ')') {
                rParen++;
            }
            if (rParen > lParen)
                throw LexicalErrorException();
        }
        if (!(lParen == 1 && rParen == 1))
            throw LexicalErrorException();
        std::vector<std::string> tokens = tokenizer(token, '(');
        std::string oType = tokens[0];
        tokens = tokenizer(tokens[1], ')');
        if (tokens.size() != 1)
            throw LexicalErrorException();
        value = tokens[0];
        if (!isNumeric(value))
            throw LexicalErrorException();
        if (oType == INT8) {
            return Int8;
        } else if (oType == INT16) {
            return Int16;
        } else if (oType == INT32) {
            return Int32;
        } else if (oType == FLOAT) {
            return Float;
        } else if (oType == DOUBLE) {
            return Double;
        } else {
            throw LexicalErrorException();
        }
    } catch (LexicalErrorException &e) {
        std::cout << e.what() << std::endl;
        setError();
    }
    return UnknownOperand; 
}

std::vector<std::string> Lexer::tokenizer(std::string const &line, char delim) const {
    std::vector<std::string> tokens;
    std::stringstream ss(line);
    std::string token;
    while (getline(ss, token, delim)) {
        tokens.push_back(token);
    }
    return tokens;
}

bool Lexer::isNumeric(std::string const &str) const {
    int dotCount = 0;
    for (std::string::size_type i = 0; i < str.size(); i++) {
        if (str[i] == '.')
            dotCount++;
    }
    if (dotCount > 1)
        return false;
    for (std::string::size_type i = 0; i < str.size(); i++) {
        if (!isdigit(str[i]) && str[i] != '.') {
            return false;
        }
    }
    return true;
}

bool Lexer::hasError(void) const {
    return lexErr;
}

void Lexer::setError(void) {
    this->lexErr = true;
}