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
<br>

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
