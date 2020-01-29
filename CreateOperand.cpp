#include "IOperand.hpp"

CreateOperand::CreateOperand() {
    arrFp = new coMemFn[5];
    arrFp[Int8] = &CreateOperand::createInt8;
    arrFp[Int16] = &CreateOperand::createInt16;
    arrFp[Int32] = &CreateOperand::createInt32;
    arrFp[Float] = &CreateOperand::createFloat;
    arrFp[Double] = &CreateOperand::createDouble;
}

CreateOperand::CreateOperand(const CreateOperand & other) {
    this->arrFp = other.arrFp;
}

CreateOperand::~CreateOperand() {
}

CreateOperand & CreateOperand::operator = (const CreateOperand & rhs) {
    if (this != &rhs)
        this->arrFp = rhs.arrFp;
    return *this;
}

IOperand const * CreateOperand::createOperand(eOperandType type, std::string const & value) const {
    return ((this->*(arrFp[type]))(value));
}

IOperand const * CreateOperand::createInt8( std::string const & value ) const {
    try {
    IOperand const * tmp = nullptr;
    tmp = new Int8Operand(value);
    return tmp;
    } catch (const std::bad_alloc & e) {
        std::cerr << e.what() << std::endl;
    }
    return nullptr;
} 

IOperand const * CreateOperand::createInt16( std::string const & value ) const {
    IOperand const * tmp = nullptr;
    tmp = new Int16Operand(value);
    if (tmp != nullptr)
        return tmp;
    return nullptr;
} 

IOperand const * CreateOperand::createInt32( std::string const & value ) const {
    IOperand const * tmp = nullptr;
    tmp = new Int32Operand(value);
    if (tmp != nullptr)
        return tmp;
    return nullptr;
}

IOperand const * CreateOperand::createFloat( std::string const & value ) const {
    try {
    IOperand const * tmp = nullptr;
    tmp = new FloatOperand(value);
        return tmp;
    } catch (const std::bad_alloc & e) {
        std::cerr << e.what() << std::endl;
    }
    return nullptr;
} 

IOperand const * CreateOperand::createDouble( std::string const & value ) const {
    IOperand const * tmp = nullptr;
    tmp = new DoubleOperand(value);
    if (tmp != nullptr)
        return tmp;
    return nullptr;
}
