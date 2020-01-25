#include "IOperand.hpp"
#include "Lexer.hpp"
#include <stack>
#include <fstream>

int     main(int ac, char **av) {
    if (ac == 2) {
        std::string line;
        std::ifstream myfile ("example.txt");
        Lexer lex;
        if (myfile.is_open()) {
            while ( getline (myfile,line) )
            {
                
                // std::cout << line << '\n';
            }
            myfile.close();
        }
        else std::cout << "Unable to open file";
    } else {
        std::vector<std::string> tokens;
        std::string line = "lsdkfj   sdfsd  sdf    ";
        std::stringstream ss(line);
        std::string token;
        while (getline(ss, token, ' ')) {
            tokens.push_back(token);
        }
        std::vector<std::string>::iterator it = tokens.begin();
        for (int i = tokens.size() - 1; i >= 0; i--) {
            if (tokens[i].length() == 0)
                tokens.erase(it + i);
        }
        for (int i = 0; i < tokens.size(); i++) {
            std::cout << tokens[i] << std::endl;
        }
    }

    // CreateOperand co;
    // const IOperand * i80 = co.createOperand(Int8, "0");
    // const IOperand * i160 = co.createOperand(Int16, "300");
    // std::cout << i80->toString() << std::endl;
    // std::cout << i160->toString() << std::endl;

    // const IOperand * i161 = *i160 / *i80;
    // std::cout << i161->toString() << std::endl;

    //std::cout << std::numeric_limits<double>::min() << std::endl;
    // std::cout << FLT_TRUE_MIN << std::endl;
    // double d = std::stold("0.0000000000000000000000000000000000000002");
    // std::cout << d << std::endl;
    // float f = std::stof("100000000000000000000000000000000000000");
    // std::cout << f << std::endl;

    // double f = 	1.401298464e-45f;
    // std::cout << f << std::endl;

    // std::string z = "000000.0000000000050000000005";
    // std::size_t found = z.find(".");
    // std::string::iterator nth = z.begin() + found;
    // std::string fpart = z.substr(found+1);
    // int i;
    // for (i = 0; fpart[i] == '0'; i++)
    //     ;
    // std::cout << i << std::endl;
    // std::cout << std::count(z.begin(), z.end(), '0') << std::endl;
    // std::cout << std::count(nth, z.end(), '0') << std::endl;
    
    // long long int d = 100000046500000044;
    // std::cout << std::to_string(d) << std::endl;

    // CreateOperand co;
    // const IOperand *f0 = co.createOperand(Float, "54.235342352");
    // const IOperand *f1 = co.createOperand(Float, "23.34621");
    // const IOperand *d0 = co.createOperand(Double, "23.2350983450982123123234");
    // const IOperand *f2 = *f0 + *d0;
    // std::cout << f0->toString() << std::endl;
    // std::cout << f1->toString() << std::endl;
    // std::cout << f2->toString() << std::endl;
    
    // double dbl = 340958.349587439583;
    // std::ostringstream strs;
    // strs << std::setprecision(20) << dbl;
    // std::string str = strs.str();
    
    // std::cout << str <<std::endl;

    // CreateOperand co;
    // std::stack<IOperand const *> s;
    // s.push(co.createOperand(Float, "123.4656"));
    // s.push(co.createOperand(Int32, "2323411"));
    // std::cout << s.top()->toString() << std::endl;
    // s.pop();
    // std::cout << s.top()->toString() << std::endl;
}
