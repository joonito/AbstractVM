#include "IOperand.hpp"
#include "Exceptions.hpp"

FloatOperand::FloatOperand() {
    this->value = 0;
}

FloatOperand::FloatOperand(std::string const &value) {
    try{
    std::size_t dPoint = value.find(".");
    if (dPoint != std::string::npos) {
        std::size_t length = value.length();
        std::size_t fpLength = length - dPoint - 1;
        std::size_t wnLength = length - fpLength - 1;
        if (wnLength > DOUBLE_LEN_LIM) {
            throw OverflowException();
        }
        if (fpLength > DOUBLE_LEN_LIM) {
            throw UnderflowException();
        }
        std::string fpart = value.substr(dPoint + 1);
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
    }} catch (const OverflowException & e) {
        std::cerr << e.what() << std::endl;
        if (g_stdIn == true)
            exit( EXIT_FAILURE );
    } catch (const UnderflowException & e) {
        std::cerr << e.what() << std::endl;
        if (g_stdIn == true)
            exit( EXIT_FAILURE );
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

    try{
    CreateOperand co;
    eOperandType lshType = this->getType();
    eOperandType rhsType = rhs.getType();
    if (lshType >= rhsType) {
        const IOperand *newRhs = co.createOperand(lshType, rhs.toString());
        long double l = std::stold(this->toString(), nullptr);
        long double r = std::stold(newRhs->toString(), nullptr);
        delete newRhs;
        const IOperand *ret = co.createOperand(lshType, "0");
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
        return ret;
    }
    const IOperand *newLhs = co.createOperand(rhsType, this->toString());
    const IOperand *ret = *newLhs + rhs;
    delete newLhs;
    return ret;
    } catch (const OverflowException & e) {
            std::cerr << e.what() << std::endl;
            if (g_stdIn == true)
                exit( EXIT_FAILURE );
        } catch (const UnderflowException & e) {
            std::cerr << e.what() << std::endl;
            if (g_stdIn == true)
                exit( EXIT_FAILURE );
        }
    return nullptr;
}

IOperand const * FloatOperand::operator-( IOperand const & rhs ) const {

    try {
    CreateOperand co;
    eOperandType lshType = this->getType();
    eOperandType rhsType = rhs.getType();
    if (lshType >= rhsType) {
        const IOperand *newRhs = co.createOperand(lshType, rhs.toString());
        long double l = std::stold(this->toString(), nullptr);
        long double r = std::stold(newRhs->toString(), nullptr);
        delete newRhs;
        const IOperand *ret = co.createOperand(lshType, "0");
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
        return ret;
    }
    const IOperand *newLhs = co.createOperand(rhsType, this->toString());
    const IOperand *ret = *newLhs - rhs;
    delete newLhs;
    return ret;
    } catch (const OverflowException & e) {
            std::cerr << e.what() << std::endl;
            if (g_stdIn == true)
                exit( EXIT_FAILURE );
        } catch (const UnderflowException & e) {
            std::cerr << e.what() << std::endl;
            if (g_stdIn == true)
                exit( EXIT_FAILURE );
        }
    return nullptr;
}

IOperand const * FloatOperand::operator*( IOperand const & rhs ) const {

    try {
    CreateOperand co;
    eOperandType lshType = this->getType();
    eOperandType rhsType = rhs.getType();
    if (lshType >= rhsType) {
        const IOperand *newRhs = co.createOperand(lshType, rhs.toString());
        long double l = std::stold(this->toString(), nullptr);
        long double r = std::stold(newRhs->toString(), nullptr);
        delete newRhs;
        const IOperand *ret = co.createOperand(lshType, "0");
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
        return ret;
    }
    const IOperand *newLhs = co.createOperand(rhsType, this->toString());
    const IOperand *ret = *newLhs * rhs;
    delete newLhs;
    return (ret);
    } catch (const OverflowException & e) {
            std::cerr << e.what() << std::endl;
            if (g_stdIn == true)
                exit( EXIT_FAILURE );
        } catch (const UnderflowException & e) {
            std::cerr << e.what() << std::endl;
            if (g_stdIn == true)
                exit( EXIT_FAILURE );
        }
    return nullptr;
}

IOperand const * FloatOperand::operator/( IOperand const & rhs ) const {
    try {
    CreateOperand co;
    eOperandType lshType = this->getType();
    eOperandType rhsType = rhs.getType();
    if (lshType >= rhsType) {
        const IOperand *newRhs = co.createOperand(lshType, rhs.toString());
        long double l = std::stold(this->toString(), nullptr);
        long double r = std::stold(newRhs->toString(), nullptr);
        delete newRhs;
        const IOperand *ret = co.createOperand(lshType, "0");
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
        return ret;
    }
    const IOperand *newLhs = co.createOperand(rhsType, this->toString());
    const IOperand *ret = *newLhs / rhs;
    delete newLhs;
    return (ret);
    } catch (const DivisionByZeroException & e) {
            std::cerr << e.what() << std::endl;
            if (g_stdIn == true)
                exit( EXIT_FAILURE );
        } catch (const OverflowException & e) {
            std::cerr << e.what() << std::endl;
            if (g_stdIn == true)
                exit( EXIT_FAILURE );
        } catch (const UnderflowException & e) {
            std::cerr << e.what() << std::endl;
            if (g_stdIn == true)
                exit( EXIT_FAILURE );
        }
    return nullptr;
}

IOperand const * FloatOperand::operator%( IOperand const & rhs ) const {

    try {
    CreateOperand co;
    eOperandType lshType = this->getType();
    eOperandType rhsType = rhs.getType();
    if (lshType >= rhsType) {
        const IOperand *newRhs = co.createOperand(lshType, rhs.toString());
        long double l = std::stold(this->toString(), nullptr);
        long double r = std::stold(newRhs->toString(), nullptr);
        delete newRhs;
        const IOperand *ret = co.createOperand(lshType, "0");
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
        return ret;
    }
    const IOperand *newLhs = co.createOperand(rhsType, this->toString());
    const IOperand *ret = *newLhs % rhs;
    delete newLhs;
    return (ret);
    } catch (const ModuloByZeroException &e) {
            std::cerr << e.what() << std::endl;
            if (g_stdIn == true)
                exit( EXIT_FAILURE );
        } catch (const OverflowException &e) {
            std::cerr << e.what() << std::endl;
            if (g_stdIn == true)
                exit( EXIT_FAILURE );
        } catch (const UnderflowException & e) {
            std::cerr << e.what() << std::endl;
            if (g_stdIn == true)
                exit( EXIT_FAILURE );
    }
    return nullptr;
}

std::string const & FloatOperand::toString(void) const {
    std::ostringstream strs;
    strs << std::fixed;
    strs << std::setprecision(getPrecision()) << this->value;
    std::string tmp = std::string(strs.str());
    int i;
    for (i = tmp.length() - 1; tmp[i] == '0'; i--)
        ;
    std::string const *trimmed = new std::string(tmp.substr(0, i + 1));
    std::string const &ret = *trimmed;
    return ret;
}