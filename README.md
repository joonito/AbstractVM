# AbstractVM

Let's create simple virtual machine!  

### Articles before start
1. https://en.wikipedia.org/wiki/Central_processing_unit
2. https://en.wikipedia.org/wiki/Chipset
3. https://en.wikipedia.org/wiki/Computer_data_storage
4. https://en.wikipedia.org/wiki/Input/output

### Central Processing unit

### Chipset

### Computer data storage

### Input/output

## What is AbstractVM?
AbstractVM is a machine that uses  a stack to compute simple arithmetic expressions.  
These arithmetic expressions are provided to the machine as basic assembly programs.  

### Wait.. what is assembly!?

Assembly code is converted into machine code by **assembler**
Every assembler has its own assembly language which is designed for exactly one specific computer architecture.
Assembly language usually has one statement per machine instruction(1:1).
Assembly langauge uses a mnemonic to represent each low-level machine instruction or opcode. 
Assembly language instructions usually consist of an opcode mnemonic followed by a list of data, arguments or parameters. These are translated by an assembler into machine language instructions that can be loaded into memory and executed.

<br>
**mnemonic** : A device such as a pattern of letters, ideas, or associations that assists
<br>
**Opcode** : Abbreviation of operation code, also known as instruction syllable, instruction parcel or opstring. Portion of a machine language instruction that specifies the operation to be performed. 

[Check Wikipedia for more information](https://en.wikipedia.org/wiki/Assembly_language)

### AbstractVM's assembly language

As for any assembly language, the language of AbstractVM is composed of a series of instructions, with one instruction per line.  

* Comments: Starts with a ';' and finish with a newline. A comment can be either at the start of a line, or after an instruction.  
* **push v**: Pushes the value v at the top of the stack. The value v must have one of the following form:  
  - int8(n)
  - int16(n)
  - int32(n)
  - float(z)
  - double(z)
* **pop**: Unstacks the value from the top of the stack. If the stack is empty, the program execution must stop with an error.  
* **dump**: Displays each value of the stack, from the most recent one to the oldest one WITHOUT CHANGING the stack. Each value is separated from the next one by a newline.  
* **assert v**: Asserts that the value at the top of the stack is equal to the one passed as parameter for this instruction. If it is not the case, the program execution must stop with an error. The value v has the same form that those passed as parameters to the instruction **push**.<br>
* **add**: Ustacks the first two values on the stack, adds them together and stacks the result. If the number of values on the stack is strictly inferior to 2, the program execution must stop with an error.
* **sub**: Unstacks the first two values on the stack, subtracts them, then stacks the result. If the number of values on the stack is strictly inferior to 2, the program execution must stop with an error.
* **mul**: Unstacks the first two values on the stack, multiplies them, then stacks the result. If the number of values on the stack is strictly inferior to 2, the program execution must stop with an error.
* **div**: Unstacks the first two values on the stack, divides them, then stacks the result. If the number of values on the stack is strictly inferior to 2, the program execution must stop with an error. Moreover, if the divisor is equal to 0, the program execution must stop with an error too. Chatting about floating point values is relevant a this point. If you don’t understand why, some will understand. The linked question is an open one, there’s no definitive answer.
* **mod**: Unstacks the first two values on the stack, calculates the modulus, then stacks the result. If the number of values on the stack is strictly inferior to 2, the program execution must stop with an error. Moreover, if the divisor is equal to 0, the program execution must stop with an error too. Same note as above about fp values.
* **print**: Asserts that the value at the top of the stack is an 8-bit integer. (If not, see the instruction assert), then interprets it as an ASCII value and displays the corresponding character on the standard output.
* **exit**: Terminate the execution of the current program. If this instruction does not appears while all others instruction has been processed, the execution must stop with an error.
<br>
When a computation involves two operands of different types, the value returned has the type of the more precise operand.<br>

### Errors
When one of the following cases is encountered, AbstractVM must raise an exception and stop the execution of the program cleanly. It is forbidden to raise scalar exceptions. Moreover your exception classes must inherit from std::exception. (We need to create our own exception classes!)

* The assembly program includes one or several lexical errors or syntactic errors.
* An instruction is unknown
* Overflow on a value
* Underflow on a value
* Instruction pop on an empty stack
* Division/modulo by 0
* The program doesn’t have an exit instruction
* An assert instruction is not true
* The stack is composed of strictly less that two values when an arithmetic instruction is executed.

Perhaps there are more errors cases. However, you machine must never crash (segfault, bus error, infinite loop, unhandled exception, ...).
<br>
### Execution
Your machine must be able to run programs from a file passed as a parameter and from the standard input. When reading from the standard input, the end of the program is indicated by the special symbol ";;" otherwise absent.

### Generic instructions
* You are free to use any C++ version you like.
* You are free to use any library you like.
* Any class that declares at least one attribute must be written in canonical form. In- heriting from a class that declares attributes does not count as declaring attributes.
* It’s forbidden to implement any function in a header file, except for templates and the virtual destructor of a base class.
* The “keyword” "using namespace" is forbidden.

### The IOperand interface
AbstractVM uses 5 operand classes that you must declare and define:
* Int8
* Int16
* Int 32
* Float
* Double
```
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
```

### Creation of a new operand
New operands MUST be created via a "factory method". Search Google if you don’t know what it is. This member function must have the following prototype:
```
 IOperand const * createOperand( eOperandType type, std::string const & value ) const;
```
The eOperandType type is an enum defining the following values: Int8, Int16, Int32, Float and Double.
Depending on the enum value passed as a parameter, the member function createOperand creates a new IOperand by calling one of the following private member functions:
```
IOperand const * createInt8( std::string const & value ) const; 
IOperand const * createInt16( std::string const & value ) const; 
IOperand const * createInt32( std::string const & value ) const; 
IOperand const * createFloat( std::string const & value ) const; 
IOperand const * createDouble( std::string const & value ) const;
```
In order to choose the right member function for the creation of the new IOperand, you MUST create and use an array (here, a vector shows little interest) of pointers on member functions with enum values as index.

### The precision
When an operation happens between two operands of the same type, there is no problem. However, what about when the types are different ? The usual method is to order types using their precision. For this machine you should use the following order: Int8 < Int16 < Int32 < Float < Double. This order may be represented as an enum, as enum values evaluate to integers.

The pure method getPrecision from the interface IOperand allows to get the preci- sion of an operand. When an operation uses two operands from two different types, the comparison of theirs precisions allows to figure out the result type of the operation.

### The Stack
AbstractVM is a stack based virtual machine. Whereas the stack is an actual stack or another container that behaves like a stack is up to you. Whatever the container, it MUST only contain pointers to the abstract type IOperand.
