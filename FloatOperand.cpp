#include "IOperand.hpp"
#include "Exceptions.hpp"

FloatOperand::FloatOperand() {
    this->value = 0;
}

FloatOperand::FloatOperand(std::string const &value) {
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
            if (IS_FLOAT_UNDERFLOW(this->value))
                throw UnderflowException();
            if (IS_FLOAT_OVERFLOW(this->value))
                throw OverflowException();
        } else {
            if (value.length() > DOUBLE_LEN_LIM)
                throw OverflowException();
            this->value = std::stold(value);
            if (IS_FLOAT_OVERFLOW(this->value))
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

FloatOperand::FloatOperand(const FloatOperand &other) {
    this->value = other.value;
}

FloatOperand::~FloatOperand() {
}

FloatOperand & FloatOperand::operator = (const FloatOperand &rhs) {
    if (this != &rhs)
        this->value = rhs.value;
    return *this;
}

int     FloatOperand::getPrecision(void) const {
    return FLOAT_PRECISION;
}

eOperandType FloatOperand::getType(void) const {
    return Float;
}

IOperand const * FloatOperand::operator+( IOperand const & rhs ) const {

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
            if (IS_FLOAT_OVERFLOW(l + r))
                throw OverflowException();
            if (IS_FLOAT_UNDERFLOW(l + r))
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

IOperand const * FloatOperand::operator-( IOperand const & rhs ) const {

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
            if (IS_FLOAT_OVERFLOW(l - r))
                throw OverflowException();
            if (IS_FLOAT_UNDERFLOW(l - r))
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

IOperand const * FloatOperand::operator*( IOperand const & rhs ) const {

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
            if (IS_FLOAT_OVERFLOW(l * r))
                throw OverflowException();
            if (IS_FLOAT_UNDERFLOW(l * r))
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

IOperand const * FloatOperand::operator/( IOperand const & rhs ) const {

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
            if (IS_FLOAT_OVERFLOW(l / r))
                throw OverflowException();
            if (IS_FLOAT_UNDERFLOW(l / r))
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

IOperand const * FloatOperand::operator%( IOperand const & rhs ) const {

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
            if (IS_FLOAT_OVERFLOW(fmod(l, r)))
                throw OverflowException();
            if (IS_FLOAT_UNDERFLOW(fmod(l, r)))
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

std::string const & FloatOperand::toString(void) const {
    std::ostringstream strs;
    strs << std::fixed;
    strs << std::setprecision(getPrecision()) << this->value;
    std::string const *tmp = new std::string(strs.str());
    std::string const &ret = *tmp;
    return ret;
}