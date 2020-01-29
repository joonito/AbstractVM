#include "IOperand.hpp"
#include "Lexer.hpp"
#include "Parser.hpp"
#include "VirtualMachine.hpp"
#include "Exceptions.hpp"
#include <stack>
#include <fstream>
#include <regex>

void    print_mode(void) {
std::cout << R"foo(
===================================================================
                  *      (    (   (            *       ) (          
   (            (  `     )\ ) )\ ))\ )       (  `   ( /( )\ )       
   )\    (   (  )\))(   (()/((()/(()/( (     )\))(  )\()|()/(  (    
((((_)(  )\  )\((_)()\   /(_))/(_))(_)))\   ((_)()\((_)\ /(_)) )\   
 )\ _ )\((_)((_|_()((_) (_))_(_))(_)) ((_)  (_()((_) ((_|_))_ ((_)  
 (_)_\(_) \ / /|  \/  | | |_ |_ _| |  | __| |  \/  |/ _ \|   \| __| 
  / _ \  \ V / | |\/| | | __| | || |__| _|  | |\/| | (_) | |) | _|  
 /_/ \_\  \_/  |_|  |_| |_|  |___|____|___| |_|  |_|\___/|___/|___| 
                                                                    
===================================================================

)foo";
}

void    print_manual(void) {
std::cout << R"foo(

=======================================================
  ___  _         _                  _     _   ____  ___
 / _ \| |       | |                | |   | | | |  \/  |
/ /_\ | |__  ___| |_ _ __ __ _  ___| |_  | | | | .  . |
|  _  | '_ \/ __| __| '__/ _` |/ __| __| | | | | |\/| |
| | | | |_) \__ | |_| | | (_| | (__| |_  \ \_/ | |  | |
\_| |_|_.__/|___/\__|_|  \__,_|\___|\__|  \___/\_|  |_/
                                                       
=======================================================

<How to use>

S := INSTR [SEP INSTR]* #

INSTR :=
     push VALUE
    | pop | dump
    | assert VALUE
    | add
    | sub
    | mul
    | div
    | mod
    | print
    | exit

VALUE :=
    int8(N)
    | int16(N)
    | int32(N)
    | float(Z)
    | double(Z)

N := [-]?[0..9]+

Z := [-]?[0..9]+.[0..9]+

SEP := '\n'+

=======================================================

)foo";
}

bool g_stdIn;

int     main(int ac, char **av) {
    try {
    if (ac == 2) {
        print_mode();
        g_stdIn = false;
        std::string line;
        std::ifstream myfile (av[1]);
        Lexer lexer(false);
        Parser parser(false);
        std::deque<Token const *> tokens;
        std::deque<std::deque<Token const *>> instructions;
        if (myfile.is_open()) {
            while ( getline (myfile,line) )
            {
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
        g_stdIn = true;
        print_manual();
        std::string line;
        Lexer lexer(true);
        Parser parser(true);
        std::deque<Token const *> tokens;
        std::deque<std::deque<Token const *>> instructions;
        while (1) {
            std::cout << "avm :";
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
    } else {
        std::cout << "Too many arguments" << std::endl;
    }} catch (const std::exception & e) {
        std::cerr << e.what() << std::endl;
    }
}
