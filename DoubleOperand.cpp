#include "IOperand.hpp"
#include "Exceptions.hpp"

DoubleOperand::DoubleOperand() {
    this->value = 0;
}

DoubleOperand::DoubleOperand(std::string const &value) {
    try {
        std::size_t dpoint = value.find(".");
        if (dpoint != std::string::npos) {
            std::size_t length = value.length();
            std::size_t fpLength = length - dpoint;
            std::size_t wnLength = length - fpLength - 1;
            if (wnLength > DOUBLE_LEN_LIM) {
                throw OverflowException();
            }
            std::string fpart = value.substr(dpoint + 1);
            int zeroCount = 0;
            while (fpart[zeroCount] == '0')
                zeroCount++;
            if (zeroCount > DOUBLE_LEN_LIM)
                throw UnderflowException();
            this->value = std::stold(value);
            if (IS_DOUBLE_UNDERFLOW(this->value))
                throw UnderflowException();
            if (IS_DOUBLE_OVERFLOW(this->value))
                throw OverflowException();
        } else {
            if (value.length() > DOUBLE_LEN_LIM)
                throw OverflowException();
            this->value = std::stold(value);
            if (IS_DOUBLE_OVERFLOW(this->value))
                throw OverflowException();
        }
    } catch (OverflowException& e){
        std::cout << e.what() << std::endl;
        std::exit( EXIT_FAILURE );
    } catch (UnderflowException& e) {
        std::cout << e.what() << std::endl;
        std::exit( EXIT_FAILURE );
    }
}

DoubleOperand::DoubleOperand(const DoubleOperand &other) {
    this->value = other.value;
}

DoubleOperand::~DoubleOperand() {
}

DoubleOperand & DoubleOperand::operator = (const DoubleOperand &rhs) {
    if (this != &rhs)
        this->value = rhs.value;
    return *this;
}

int     DoubleOperand::getPrecision(void) const {
    return DOUBLE_PRECISION;
}

eOperandType DoubleOperand::getType(void) const {
    return Double;
}

IOperand const * DoubleOperand::operator+( IOperand const & rhs ) const {

    CreateOperand co;
    eOperandType lshType = this->getType();
    eOperandType rhsType = rhs.getType();
    if (lshType >= rhsType) {
        const IOperand *newRhs = co.createOperand(lshType, rhs.toString());
        long double l = std::stold(this->toString(), nullptr);
        long double r = std::stold(newRhs->toString(), nullptr);
        delete newRhs;
        const IOperand *ret = co.createOperand(lshType, "0");
        try {
            if (IS_DOUBLE_OVERFLOW(l + r))
                throw OverflowException();
            if (IS_DOUBLE_UNDERFLOW(l + r))
                throw UnderflowException();
            long double res = l + r;
            std::ostringstream strs;
            strs << std::fixed;
            strs << std::setprecision(getPrecision()) << res;
            std::string value = strs.str();
            delete ret;
            ret = co.createOperand(lshType, value);
        } catch (OverflowException& e) {
            std::cout << e.what() << std::endl;
            std::exit( EXIT_FAILURE );
        } catch (UnderflowException& e) {
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

IOperand const * DoubleOperand::operator-( IOperand const & rhs ) const {

    CreateOperand co;
    eOperandType lshType = this->getType();
    eOperandType rhsType = rhs.getType();
    if (lshType >= rhsType) {
        const IOperand *newRhs = co.createOperand(lshType, rhs.toString());
        long double l = std::stold(this->toString(), nullptr);
        long double r = std::stold(newRhs->toString(), nullptr);
        delete newRhs;
        const IOperand *ret = co.createOperand(lshType, "0");
        try {
            if (IS_DOUBLE_OVERFLOW(l - r))
                throw OverflowException();
            if (IS_DOUBLE_UNDERFLOW(l - r))
                throw UnderflowException();
            long double res = l - r;
            std::ostringstream strs;
            strs << std::fixed;
            strs << std::setprecision(getPrecision()) << res;
            std::string value = strs.str();
            delete ret;
            ret = co.createOperand(lshType, value);
        } catch (OverflowException& e) {
            std::cout << e.what() << std::endl;
            std::exit( EXIT_FAILURE );
        } catch (UnderflowException& e) {
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

IOperand const * DoubleOperand::operator*( IOperand const & rhs ) const {

    CreateOperand co;
    eOperandType lshType = this->getType();
    eOperandType rhsType = rhs.getType();
    if (lshType >= rhsType) {
        const IOperand *newRhs = co.createOperand(lshType, rhs.toString());
        long double l = std::stold(this->toString(), nullptr);
        long double r = std::stold(newRhs->toString(), nullptr);
        delete newRhs;
        const IOperand *ret = co.createOperand(lshType, "0");
        try {
            if (IS_DOUBLE_OVERFLOW(l * r))
                throw OverflowException();
            if (IS_DOUBLE_UNDERFLOW(l * r))
                throw UnderflowException();
            long double res = l * r;
            std::ostringstream strs;
            strs << std::fixed;
            strs << std::setprecision(getPrecision()) << res;
            std::string value = strs.str();
            delete ret;
            ret = co.createOperand(lshType, value);
        } catch (OverflowException& e) {
            std::cout << e.what() << std::endl;
            std::exit( EXIT_FAILURE );
        } catch (UnderflowException& e) {
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

IOperand const * DoubleOperand::operator/( IOperand const & rhs ) const {

    CreateOperand co;
    eOperandType lshType = this->getType();
    eOperandType rhsType = rhs.getType();
    if (lshType >= rhsType) {
        const IOperand *newRhs = co.createOperand(lshType, rhs.toString());
        long double l = std::stold(this->toString(), nullptr);
        long double r = std::stold(newRhs->toString(), nullptr);
        delete newRhs;
        const IOperand *ret = co.createOperand(lshType, "0");
        try {
            if (IS_ZERO(r))
                throw DivisionByZeroException();
            if (IS_DOUBLE_OVERFLOW(l / r))
                throw OverflowException();
            if (IS_DOUBLE_UNDERFLOW(l / r))
                throw UnderflowException();
            long double res = l / r;
            std::ostringstream strs;
            strs << std::fixed;
            strs << std::setprecision(getPrecision()) << res;
            std::string value = strs.str();
            delete ret;
            ret = co.createOperand(lshType, value);
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

IOperand const * DoubleOperand::operator%( IOperand const & rhs ) const {

    CreateOperand co;
    eOperandType lshType = this->getType();
    eOperandType rhsType = rhs.getType();
    if (lshType >= rhsType) {
        const IOperand *newRhs = co.createOperand(lshType, rhs.toString());
        long double l = std::stold(this->toString(), nullptr);
        long double r = std::stold(newRhs->toString(), nullptr);
        delete newRhs;
        const IOperand *ret = co.createOperand(lshType, "0");
        try {
            if (IS_ZERO(r))
                throw ModuloByZeroException();
            if (IS_DOUBLE_OVERFLOW(fmod(l, r)))
                throw OverflowException();
            if (IS_DOUBLE_UNDERFLOW(fmod(l, r)))
                throw UnderflowException();
            long double res = fmod(l, r);
            std::ostringstream strs;
            strs << std::fixed;
            strs << std::setprecision(getPrecision()) << res;
            std::string value = strs.str();
            delete ret;
            ret = co.createOperand(lshType, value);
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

std::string const & DoubleOperand::toString(void) const {
    std::ostringstream strs;
    strs << std::fixed;
    strs << std::setprecision(getPrecision()) << this->value;
    std::string const *tmp = new std::string(strs.str());
    std::string const &ret = *tmp;
    return ret;
}