#include "Lexer.hpp"
#include "Exceptions.hpp"

Lexer::Lexer() {
    lexErr = false;
    stdInput = false;
    lineErr = false;
}

Lexer::Lexer(bool stdIn) {
    this->lexErr = false;
    this->stdInput = stdIn;
    this->lineErr = false;
}

Lexer::Lexer(const Lexer &other) {
    this->lexErr = other.lexErr;
    this->stdInput = other.stdInput;
    this->lineErr = other.lineErr;
}

Lexer::~Lexer() {
}

Lexer & Lexer::operator=(const Lexer &rhs) {
    if (this != &rhs) {
        this->lexErr = rhs.lexErr;
        this->stdInput = rhs.stdInput;
        this->lineErr = rhs.lineErr;
    }
    return *this;
}

Token const * Lexer::createToken(std::string const &word, bool comment) {
    if (comment == true) {
        return new Token(tokenType::comment, word);
    }
    std::regex i8Pattern(INT8PATTERN);
    std::regex i16Pattern(INT16PATTERN);
    std::regex i32Pattern(INT32PATTERN);
    std::regex fltPattern(FLOATPATTERN);
    std::regex dblPattern(DOUBLEPATTERN);
    if (word == PUSH) {
        return new Token(tokenType::unaryInstruction, PUSH);
    } else if (word == POP) {
        return new Token(tokenType::instruction, POP); 
    } else if (word == DUMP) {
        return new Token(tokenType::instruction, DUMP);
    } else if (word == ASSERT) {
        return new Token(tokenType::unaryInstruction, ASSERT);
    } else if (word == ADD) {
        return new Token(tokenType::instruction, ADD);
    } else if (word == SUB) {
        return new Token(tokenType::instruction, SUB);
    } else if (word == MUL) {
        return new Token(tokenType::instruction, MUL);
    } else if (word == DIV) {
        return new Token(tokenType::instruction, DIV);
    } else if (word == MOD) {
        return new Token(tokenType::instruction, MOD);
    } else if (word == PRINT) {
        return new Token(tokenType::instruction, PRINT);
    } else if (word == EXIT) {
        return new Token(tokenType::instruction, EXIT);
    } else if (regex_match(word, i8Pattern)) {
        return new Token(tokenType::operand, word);
    } else if (regex_match(word, i16Pattern)) {
        return new Token(tokenType::operand, word);
    } else if (regex_match(word, i32Pattern)) {
        return new Token(tokenType::operand, word);
    } else if (regex_match(word, fltPattern)) {
        return new Token(tokenType::operand, word);
    } else if (regex_match(word, dblPattern)) {
        return new Token(tokenType::operand, word);
    }
    return new Token(tokenType::unknown, word);
}

std::deque<Token const *> Lexer::tokenizer(std::string const &line) {
    lineErr = false;
    std::deque<Token const *> tokens;
    Token const * token;
    std::size_t cPos = line.find(";");
    std::string comment = "";
    std::deque<std::string> words;
    if (cPos != std::string::npos) {
        std::string lineWithoutComent = line.substr(0, cPos);
        words = splitter(lineWithoutComent, ' ');
        
        comment = line.substr(cPos + 1);
    } else {
        words = splitter(line, ' ');
    }
    for (std::size_t i = 0; i < words.size(); i++) {
        try {
            // std::cout << words[i] << std::endl;
            token = createToken(words[i], false);
            if (token->getType() == tokenType::unknown)
                throw LexicalErrorException();
        } catch (LexicalErrorException& e) {
            lineErr = true;
            std::cout << e.what() << std::endl;
            setError();
            if (checkStdInput() == true)
                exit( EXIT_FAILURE );
        }
        tokens.push_back(token);
    }
    if (comment != "") {
        token = createToken(comment, true);
        tokens.push_back(token);
    }
    removeUseless(tokens);
    if (lineErr == true)
        tokens.clear();
    return tokens;
}

void Lexer::removeUseless(std::deque<Token const *> & tokens) {
    for (int i = tokens.size() - 1; i >= 0; i--) {
        if (tokens[i]->getType() == tokenType::comment || tokens[i]->getType() == tokenType::unknown)
            tokens.erase(tokens.begin() + i);
    }
}        


std::deque<std::string> Lexer::splitter(std::string const &line, char delim) const {
    std::deque<std::string> tokens;
    std::stringstream ss(line);
    std::string token;
    while (getline(ss, token, delim)) {
        tokens.push_back(token);
    }
    for (int i = tokens.size() - 1; i >= 0; i--) {
        if (tokens[i].length() == 0)
            tokens.erase(tokens.begin() + i);
    }
    return tokens;
}

bool Lexer::hasError(void) const {
    return this->lexErr;
}

void Lexer::setError(void) {
    if (this->lexErr == false)
        this->lexErr = true;
}

bool Lexer::checkStdInput(void) const {
    return this->stdInput;
}