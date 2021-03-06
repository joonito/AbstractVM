#include "Parser.hpp"
#include "Exceptions.hpp"

Parser::Parser() {
    this->parseErr = false;
    this->stdInput = false;
}

Parser::Parser(bool stdIn) {
    this->parseErr = false;
    this->stdInput = stdIn;
}

Parser::Parser(const Parser & other) {
    this->parseErr = other.parseErr;
    this->stdInput = other.stdInput;
}

Parser::~Parser() {

}

Parser & Parser::operator = (const Parser &rhs) {
    if (this != &rhs) {
        this->parseErr = rhs.parseErr;
        this->stdInput = rhs.stdInput;
    }
    return *this;
}

void Parser::tokenEvaluator(std::deque<Token const *> & tokens) {
    if (tokens.empty())
        return ;
    try {
    int instruction = 0;
    int unaryInstruction = 0;
    int operand = 0;
    for (std::size_t i = 0; i < tokens.size(); i++) {
        switch (tokens[i]->getType()) {
            case tokenType::instruction:
                instruction++;
                break;
            case tokenType::unaryInstruction:
                unaryInstruction++;
                break;
            case tokenType::operand:
                operand++;
                break;
            case tokenType::comment:
                break;
                case tokenType::unknown:
                    break;
        }
        if (operand > unaryInstruction) {
            throw SyntacticErrorException();
            setError();
            tokens.clear();
        }
    }
    if (!(instruction == 1 && !unaryInstruction && !operand)
    && !(unaryInstruction == 1 && operand == 1 && !instruction)
    && !(instruction == 0 && unaryInstruction == 0 && operand == 0)) {
        throw SyntacticErrorException();
        setError();
        tokens.clear();
    }} catch (const SyntacticErrorException & e) {
        std::cerr << e.what() << std::endl;
        setError();
        if (stdInput == true)
        exit( EXIT_FAILURE );
    }
}

bool Parser::hasError(void) const{
    return this->parseErr;
}

void Parser::setError(void) {
    if (this->parseErr == false)
        this->parseErr = true;
}

bool Parser::checkStdInput(void) const {
    return this->stdInput;
}