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
\* **mnemonic** : A device such as a pattern of letters, ideas, or associations that assists
<br>
\* **Opcode** : Abbreviation of operation code, also known as instruction syllable, instruction parcel or opstring. Portion of a machine language instruction that specifies the operation to be performed. 

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
