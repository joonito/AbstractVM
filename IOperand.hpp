#ifndef IOPERAND_HPP
#define IOPERAND_HPP

#include <iostream>
#include <string>
#include <limits.h>
#include <float.h>
#include <cfloat>
#include <vector>
#include <algorithm>
#include <math.h>
#include <sstream>
#include <iomanip>
#include <ctype.h>

#define IS_INT8_RANGE(x) (-128 <= x && x < 128)
#define IS_INT16_RANGE(x) (-32768 <= x && x < 32768)
#define IS_INT32_RANGE(x) (-2147483648 <= x && x < 2147483648)
#define IS_FLOAT_OVERFLOW(x) (x > FLT_MAX || x < -FLT_MAX)
#define IS_FLOAT_UNDERFLOW(x) ((0 < x && x < FLT_MIN) || (-FLT_MIN < x && x < 0))
#define IS_DOUBLE_OVERFLOW(x) (x > DBL_MAX || x < -DBL_MAX)
#define IS_DOUBLE_UNDERFLOW(x) ((0< x && x < DBL_MIN) || (-DBL_MIN < x && x < 0))
#define DOUBLE_LEN_LIM 400
#define FLOAT_PRECISION 7
#define DOUBLE_PRECISION 15
#define IS_ZERO(x) (x == 0)

enum eOperandType {
    Int8,
    Int16,
    Int32,
    Float,
    Double,
    UnknownOperand
};

class IOperand {
public:
  virtual int getPrecision( void ) const = 0;       // Precision of the type of the instance
  virtual eOperandType getType( void ) const = 0;   // Type of the instance
  
  virtual IOperand const * operator+( IOperand const & rhs ) const = 0; // Sum
  virtual IOperand const * operator-( IOperand const & rhs ) const = 0; // Difference
  virtual IOperand const * operator*( IOperand const & rhs ) const = 0; // Product rhs
  virtual IOperand const * operator/( IOperand const & rhs ) const = 0; // Quotient
  virtual IOperand const * operator%( IOperand const & rhs ) const = 0; // Modulo
  
  virtual std::string const & toString( void ) const = 0; // String representation of the instance
  virtual ~IOperand( void ) {} 
};

class Int8Operand : public IOperand {
    public:
        Int8Operand();
        Int8Operand(std::string const & value);
        Int8Operand(const Int8Operand &other);
        ~Int8Operand();
        Int8Operand & operator = (const Int8Operand &rhs); 

        int getPrecision( void ) const;
        eOperandType getType(void) const;

        IOperand const * operator+( IOperand const & rhs ) const;
        IOperand const * operator-( IOperand const & rhs ) const;
        IOperand const * operator*( IOperand const & rhs ) const;
        IOperand const * operator/( IOperand const & rhs ) const;
        IOperand const * operator%( IOperand const & rhs ) const;
        std::string const & toString( void ) const;

    private:
        long long int value;
};

class Int16Operand : public IOperand {
    public:
        Int16Operand();
        Int16Operand(std::string const & value);
        Int16Operand(const Int16Operand &other);
        ~Int16Operand();
        Int16Operand & operator = (const Int16Operand &rhs);

        int getPrecision( void ) const;
        eOperandType getType(void) const;

        IOperand const * operator+( IOperand const & rhs ) const;
        IOperand const * operator-( IOperand const & rhs ) const;
        IOperand const * operator*( IOperand const & rhs ) const;
        IOperand const * operator/( IOperand const & rhs ) const;
        IOperand const * operator%( IOperand const & rhs ) const;
        std::string const & toString( void ) const;

    private:
        long long int value;
};

class Int32Operand : public IOperand {
    public:
        Int32Operand();
        Int32Operand(std::string const & value);
        Int32Operand(const Int32Operand &other);
        ~Int32Operand();
        Int32Operand & operator = (const Int32Operand &rhs);

        int getPrecision( void ) const;
        eOperandType getType(void) const;

        IOperand const * operator+( IOperand const & rhs ) const;
        IOperand const * operator-( IOperand const & rhs ) const;
        IOperand const * operator*( IOperand const & rhs ) const;
        IOperand const * operator/( IOperand const & rhs ) const;
        IOperand const * operator%( IOperand const & rhs ) const;
        std::string const & toString( void ) const;

    private:
        long long int value;
};

class FloatOperand : public IOperand {
    public:
        FloatOperand();
        FloatOperand(std::string const & value);
        FloatOperand(const FloatOperand & other);
        ~FloatOperand();
        FloatOperand & operator = (const FloatOperand &rhs);

        int getPrecision( void ) const;
        eOperandType getType(void) const;

        IOperand const * operator+( IOperand const & rhs ) const;
        IOperand const * operator-( IOperand const & rhs ) const;
        IOperand const * operator*( IOperand const & rhs ) const;
        IOperand const * operator/( IOperand const & rhs ) const;
        IOperand const * operator%( IOperand const & rhs ) const;
        std::string const & toString( void ) const;
    
    private:
        long double value;
};

class DoubleOperand : public IOperand {
    public:
        DoubleOperand();
        DoubleOperand(std::string const & value);
        DoubleOperand(const DoubleOperand & other);
        ~DoubleOperand();
        DoubleOperand & operator = (const DoubleOperand &rhs);

        int getPrecision( void ) const;
        eOperandType getType(void) const;

        IOperand const * operator+( IOperand const & rhs ) const;
        IOperand const * operator-( IOperand const & rhs ) const;
        IOperand const * operator*( IOperand const & rhs ) const;
        IOperand const * operator/( IOperand const & rhs ) const;
        IOperand const * operator%( IOperand const & rhs ) const;
        std::string const & toString( void ) const;
    
    private:
        long double value;
};

class CreateOperand {
    public:
        IOperand const * createOperand( eOperandType type, std::string const & value ) const;
    private:
        IOperand const * createInt8( std::string const & value ) const; 
        IOperand const * createInt16( std::string const & value ) const; 
        IOperand const * createInt32( std::string const & value ) const; 
        IOperand const * createFloat( std::string const & value ) const; 
        IOperand const * createDouble( std::string const & value ) const;
};

#endif