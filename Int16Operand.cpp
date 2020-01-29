#include "IOperand.hpp"
#include "Exceptions.hpp"

Int16Operand::Int16Operand() {
    this->value = 0;   
}

Int16Operand::Int16Operand(std::string const & value) {
    try {
    if (value.length() > 6)
        throw OverflowException();
    else {
        this->value = std::stoll(value, nullptr);
        if (!IS_INT16_RANGE(this->value))
            throw OverflowException();
    }} catch (const OverflowException & e) {
        std::cerr << e.what() << std::endl;
        if (g_stdIn == true)
            exit( EXIT_FAILURE );
    }
}

Int16Operand::Int16Operand(const Int16Operand &other) {
    this->value = other.value;
}

Int16Operand::~Int16Operand() {
}

Int16Operand & Int16Operand::operator = (const Int16Operand &rhs) {
    if (this != &rhs)
        this->value = rhs.value;
    return *this;
}

int     Int16Operand::getPrecision(void) const {
    return 0;
}

eOperandType Int16Operand::getType(void) const {
    return Int16;
}

IOperand const * Int16Operand::operator+( IOperand const & rhs ) const {

    CreateOperand co;
    eOperandType lshType = this->getType();
    eOperandType rhsType = rhs.getType();
    if (lshType >= rhsType) {
        const IOperand *newRhs = co.createOperand(lshType, rhs.toString());
        long long int l = std::stoll(this->toString(), nullptr);
        long long int r = std::stoll(newRhs->toString(), nullptr);
        delete newRhs;
        const IOperand *ret = co.createOperand(lshType, "0");
        try {
        if (!IS_INT16_RANGE(l + r))
            throw OverflowException();
        else {
            std::string value = std::to_string(l + r);
            delete ret;
            ret = co.createOperand(lshType, value);
        }} catch (const OverflowException & e) {
            std::cerr << e.what() << std::endl;
            if (g_stdIn == true)
                exit( EXIT_FAILURE );
        }
        return ret;
    }
    const IOperand *newLhs = co.createOperand(rhsType, this->toString());
    const IOperand *ret = *newLhs + rhs;
    delete newLhs;
    return ret;
}

IOperand const * Int16Operand::operator-( IOperand const & rhs ) const {

    CreateOperand co;
    eOperandType lshType = this->getType();
    eOperandType rhsType = rhs.getType();
    if (lshType >= rhsType) {
        const IOperand *newRhs = co.createOperand(lshType, rhs.toString());
        long long int l = std::stoll(this->toString(), nullptr);
        long long int r = std::stoll(newRhs->toString(), nullptr);
        delete newRhs;
        const IOperand *ret = co.createOperand(lshType, "0");
        try {
        if (!IS_INT16_RANGE(l - r))
            throw OverflowException();
        else {
            std::string value = std::to_string(l - r);
            delete ret;
            ret = co.createOperand(lshType, value);
        }} catch (const OverflowException & e) {
            std::cerr << e.what() << std::endl;
            if (g_stdIn == true)
                exit( EXIT_FAILURE );
        }
        return ret;
    }
    const IOperand *newLhs = co.createOperand(rhsType, this->toString());
    const IOperand *ret = *newLhs - rhs;
    delete newLhs;
    return ret;
}

IOperand const * Int16Operand::operator*( IOperand const & rhs ) const {

    CreateOperand co;
    eOperandType lshType = this->getType();
    eOperandType rhsType = rhs.getType();
    if (lshType >= rhsType) {
        const IOperand *newRhs = co.createOperand(lshType, rhs.toString());
        long long int l = std::stoll(this->toString(), nullptr);
        long long int r = std::stoll(newRhs->toString(), nullptr);
        delete newRhs;
        const IOperand *ret = co.createOperand(lshType, "0");
        try {
        if (!IS_INT16_RANGE(l * r))
            throw OverflowException();
        else {
            std::string value = std::to_string(l * r);
            delete ret;
            ret = co.createOperand(lshType, value);
        }} catch (const OverflowException & e) {
            std::cerr << e.what() << std::endl;
            if (g_stdIn == true)
                exit( EXIT_FAILURE );
        }
        return ret;
    }
    const IOperand *newLhs = co.createOperand(rhsType, this->toString());
    const IOperand *ret = *newLhs * rhs;
    delete newLhs;
    return (ret);
}

IOperand const * Int16Operand::operator/( IOperand const & rhs ) const {

    CreateOperand co;
    eOperandType lshType = this->getType();
    eOperandType rhsType = rhs.getType();
    if (lshType >= rhsType) {
        const IOperand *newRhs = co.createOperand(lshType, rhs.toString());
        long long int l = std::stoll(this->toString(), nullptr);
        long long int r = std::stoll(newRhs->toString(), nullptr);
        delete newRhs;
        const IOperand *ret = co.createOperand(lshType, "0");
        try {
        if (IS_ZERO(r))
            throw DivisionByZeroException();
        if (!IS_INT16_RANGE(l / r))
            throw OverflowException();
        else {
            std::string value = std::to_string(l / r);
            delete ret;
            ret = co.createOperand(lshType, value);
        }} catch (const DivisionByZeroException & e) {
            std::cerr << e.what() << std::endl;
            if (g_stdIn == true)
                exit( EXIT_FAILURE );
        } catch (const OverflowException & e) {
            std::cerr << e.what() << std::endl;
            if (g_stdIn == true)
                exit( EXIT_FAILURE );
        }
        return ret;
    }
    const IOperand *newLhs = co.createOperand(rhsType, this->toString());
    const IOperand *ret = *newLhs / rhs;
    delete newLhs;
    return (ret);
}

IOperand const * Int16Operand::operator%( IOperand const & rhs ) const {

    CreateOperand co;
    eOperandType lshType = this->getType();
    eOperandType rhsType = rhs.getType();
    if (lshType >= rhsType) {
        const IOperand *newRhs = co.createOperand(lshType, rhs.toString());
        long long int l = std::stoll(this->toString(), nullptr);
        long long int r = std::stoll(newRhs->toString(), nullptr);
        delete newRhs;
        const IOperand *ret = co.createOperand(lshType, "0");
        try {
        if (IS_ZERO(r))
            throw ModuloByZeroException();
        if (!IS_INT16_RANGE(l % r))
            throw OverflowException();
        else {
            std::string value = std::to_string(l % r);
            delete ret;
            ret = co.createOperand(lshType, value);
        }} catch (const ModuloByZeroException & e) {
            std::cerr << e.what() << std::endl;
            if (g_stdIn == true)
                exit( EXIT_FAILURE );
        } catch (const OverflowException & e) {
            std::cerr << e.what() << std::endl;
            if (g_stdIn == true)
                exit( EXIT_FAILURE );
        }
        return ret;
    }
    const IOperand *newLhs = co.createOperand(rhsType, this->toString());
    const IOperand *ret = *newLhs % rhs;
    delete newLhs;
    return (ret);
}

std::string const & Int16Operand::toString( void ) const {
    std::string const *tmp = new std::string(std::to_string(this->value));
    std::string const &ret = *tmp;
    return ret;
}