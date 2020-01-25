#ifndef PARSER_HPP
#define PARSER_HPP

#include "IOperand.hpp"

class Parser {
    public:
        std::vector<std::string> parseLine(std::string const &line) const;
    private:
};

#endif