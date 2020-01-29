CXX=g++

CXXFLAGS= -std=c++11 -Wall -Wextra -Werror

DEPS = Exceptions.hpp IOperand.hpp Lexer.hpp Parser.hpp Token.hpp VirtualMachine.hpp

OBJ = CreateOperand.o DoubleOperand.o Exceptions.o FloatOperand.o Int16Operand.o Int32Operand.o Int8Operand.o Lexer.o Parser.o Token.o VirtualMachine.o main.o

%.o: %.c $(DEPS)
	$(CXX) -c -o $@ $< $(CXXFLAGS)

avm: $(OBJ) $(DEPS)
	$(CXX) -o $@ $(OBJ) $(CXXFLAGS)

clean:
	rm -f *.o

.PHONY: clean

fclean: clean
	rm -f avm

re: fclean avm