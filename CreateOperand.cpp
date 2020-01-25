#include "IOperand.hpp"

IOperand const * CreateOperand::createOperand(eOperandType type, std::string const & value) const {

    switch (type) {
        case Int8:
            return createInt8(value);
            break;
        case Int16:
            return createInt16(value);
            break;
        case Int32:
            return createInt32(value);
            break;
        case Float:
            return createFloat(value);
            break;
        case Double:
            return createDouble(value);
            break;
    }
}

IOperand const * CreateOperand::createInt8( std::string const & value ) const {
    return new Int8Operand(value);
} 

IOperand const * CreateOperand::createInt16( std::string const & value ) const {
    return new Int16Operand(value);
} 

IOperand const * CreateOperand::createInt32( std::string const & value ) const {
    return new Int32Operand(value);
}

IOperand const * CreateOperand::createFloat( std::string const & value ) const {
    return new FloatOperand(value);
} 

IOperand const * CreateOperand::createDouble( std::string const & value ) const {
    return new DoubleOperand(value);
}
