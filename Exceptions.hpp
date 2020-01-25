#include <iostream>

class LexicalErrorException : public std::exception {
    public:
        const char * what() const throw();
};

class SyntaticErrorException : public std::exception {
    public:
        const char * what() const throw();
};

class UnknownInstructionException : public std::exception {
    public:
        const char * what() const throw();
};

class OverflowException : public std::exception {
    public:
        const char * what() const throw();
};

class UnderflowException : public std::exception {
    public:
        const char * what() const throw();
};

class EmptyStackException : public std::exception {
    public:
        const char * what() const throw();
};

class DivisionByZeroException : public std::exception {
    public:
        const char * what() const throw();
};

class ModuloByZeroException : public std::exception {
    public:
        const char * what() const throw();
};

class NoExitInstructionException : public std::exception {
    public:
        const char * what() const throw();
};

class AssertionFailureException : public std::exception {
    public:
        const char * what() const throw();
};

class NotEnoughValuesException : public std::exception {
    public:
        const char * what() const throw();
};