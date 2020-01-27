#include "IOperand.hpp"
#include "Lexer.hpp"
#include "Parser.hpp"
#include "VirtualMachine.hpp"
#include <stack>
#include <fstream>
#include <regex>

int     main(int ac, char **av) {
    if (ac == 2) {
        std::string line;
        std::ifstream myfile (av[1]);
        Lexer lexer(false);
        Parser parser(false);
        std::deque<Token const *> tokens;
        std::deque<std::deque<Token const *>> instructions;
        if (myfile.is_open()) {
            while ( getline (myfile,line) )
            {
                // std::cout << line << std::endl;
                tokens = lexer.tokenizer(line);
                parser.tokenEvaluator(tokens);
                if (!tokens.empty())
                    instructions.push_back(tokens);
            }
            myfile.close();
            VirtualMachine vm(false, lexer.hasError(), parser.hasError());
            vm.runInstruction(instructions);
        }
        else std::cout << "Unable to open file" << std::endl;
    } else if (ac == 1) {
        std::string line;
        Lexer lexer(true);
        Parser parser(true);
        std::deque<Token const *> tokens;
        std::deque<std::deque<Token const *>> instructions;
        while (1) {
            getline(std::cin, line);
            if (line == ";;") {
                break;   
            }
            tokens = lexer.tokenizer(line);
            parser.tokenEvaluator(tokens);
            instructions.push_back(tokens);
        }
        VirtualMachine vm(true, lexer.hasError(), parser.hasError());
        vm.runInstruction(instructions);
    } else
    {
        std::cout << "Too many arguments" << std::endl;
    }
    
}
