#include "Exceptions.hpp"

const char *LexicalErrorException::what() const throw() {
    return "LexicalErrorException: Lexical error has occurred";
}

const char * SyntacticErrorException::what() const throw() {
    return "SyntaticErrorException: Wrong syntax";
}

const char * OverflowException::what() const throw() {
    return "OverflowException: Value overflow";
}

const char * UnderflowException::what() const throw() {
    return "UnderflowException: Value underflow";
}

const char * EmptyStackException::what() const throw() {
    return "EmptyStackException: Stack is empty";
}

const char * DivisionByZeroException::what() const throw() {
    return "DivisionByZeroException: Division by 0";
}

const char * ModuloByZeroException::what() const throw() {
    return "ModuloByZeroException: Modulo by 0";
}

const char * NoExitInstructionException::what() const throw() {
    return "NoExitInstructionException: No exit instruction is given";
}

const char * AssertionFailureException::what() const throw() {
    return "AssertionFailureException: Assertion failed";
}

const char * NotEnoughValuesException::what() const throw() {
    return "NotEnoughValuesException: Stack has not enough vales to be calculated";
}