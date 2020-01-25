#include "IOperand.hpp"
#include "Exceptions.hpp"

Int8Operand::Int8Operand() {
    this->value = 0;
}

Int8Operand::Int8Operand(std::string const & value) {
    try {
        if (value.length() > 4)
            throw OverflowException();
        else {
            this->value = std::stoll(value, nullptr);
            if (!IS_INT8_RANGE(this->value))
                throw OverflowException();
        }
    } catch (OverflowException& e) {
        std::cout << e.what() << std::endl;
        std::exit( EXIT_FAILURE );
    }
}

Int8Operand::Int8Operand(const Int8Operand &other) {
    this->value = other.value;
}

Int8Operand::~Int8Operand() {
    // std::cout << "Int8Operand: Destructor called" << std::endl;
}

Int8Operand & Int8Operand::operator = (const Int8Operand &rhs) {
    if (this != &rhs)
        this->value = rhs.value;
    return *this;
}

int     Int8Operand::getPrecision(void) const {
    return 0;
}

eOperandType Int8Operand::getType(void) const {
    return Int8;
}

IOperand const * Int8Operand::operator+( IOperand const & rhs ) const {

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
            if (!IS_INT8_RANGE(l + r))
                throw OverflowException();
            else {
                std::string value = std::to_string(l + r);
                delete ret;
                ret = co.createOperand(lshType, value);
            }
        } catch (OverflowException& e) {
            std::cout << e.what() << std::endl;
            std::exit( EXIT_FAILURE );
        }
        return ret;
    }
    const IOperand *newLhs = co.createOperand(rhsType, this->toString());
    const IOperand *ret = *newLhs + rhs;
    delete newLhs;
    return ret;
}

IOperand const * Int8Operand::operator-( IOperand const & rhs ) const {

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
            if (!IS_INT8_RANGE(l - r))
                throw OverflowException();
            else {
                std::string value = std::to_string(l - r);
                delete ret;
                ret = co.createOperand(lshType, value);
            }
        } catch (OverflowException& e) {
            std::cout << e.what() << std::endl;
            std::exit( EXIT_FAILURE );
        }
        return ret;
    }
    const IOperand *newLhs = co.createOperand(rhsType, this->toString());
    const IOperand *ret = *newLhs - rhs;
    delete newLhs;
    return ret;
}

IOperand const * Int8Operand::operator*( IOperand const & rhs ) const {

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
            if (!IS_INT8_RANGE(l * r))
                throw OverflowException();
            else {
                std::string value = std::to_string(l * r);
                delete ret;
                ret = co.createOperand(lshType, value);
            }
        } catch (OverflowException& e) {
            std::cout << e.what() << std::endl;
            std::exit( EXIT_FAILURE );
        }
        return ret;
    }
    const IOperand *newLhs = co.createOperand(rhsType, this->toString());
    const IOperand *ret = *newLhs * rhs;
    delete newLhs;
    return (ret);
}

IOperand const * Int8Operand::operator/( IOperand const & rhs ) const {

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
            if (!IS_INT8_RANGE(l / r))
                throw OverflowException();
            else {
                std::string value = std::to_string(l / r);
                delete ret;
                ret = co.createOperand(lshType, value);
            }
        } catch (OverflowException& e) {
            std::cout << e.what() << std::endl;
            std::exit( EXIT_FAILURE );
        } catch (DivisionByZeroException& e) {
            std::cout << e.what() << std::endl;
            std::exit( EXIT_FAILURE );
        }
        return ret;
    }
    const IOperand *newLhs = co.createOperand(rhsType, this->toString());
    const IOperand *ret = *newLhs / rhs;
    delete newLhs;
    return (ret);
}

IOperand const * Int8Operand::operator%( IOperand const & rhs ) const {

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
            if (!IS_INT8_RANGE(l % r))
                throw OverflowException();
            else {
                std::string value = std::to_string(l % r);
                delete ret;
                ret = co.createOperand(lshType, value);
            }
        } catch (OverflowException& e) {
            std::cout << e.what() << std::endl;
            std::exit( EXIT_FAILURE );
        } catch (ModuloByZeroException& e) {
            std::cout << e.what() << std::endl;
            std::exit( EXIT_FAILURE );
        }
        return ret;
    }
    const IOperand *newLhs = co.createOperand(rhsType, this->toString());
    const IOperand *ret = *newLhs % rhs;
    delete newLhs;
    return (ret);
}

std::string const & Int8Operand::toString( void ) const {
    std::string const *tmp = new std::string(std::to_string(this->value));
    std::string const &ret = *tmp;
    return ret;
}