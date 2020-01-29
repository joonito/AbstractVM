#include "VirtualMachine.hpp"
#include "Exceptions.hpp"

VirtualMachine::VirtualMachine() {
    this->vmErr = false;
    this->stdInput = false;
    this->lexErr = false;
    this->parseErr = false;
}

VirtualMachine::VirtualMachine(bool stdInput, bool lErr, bool pErr) {
    this->vmErr = false;
    this->stdInput = stdInput;
    this->lexErr = lErr;
    this->parseErr = pErr;
}

VirtualMachine::VirtualMachine(const VirtualMachine & other) {
    this->stack = other.stack;
    this->vmErr = other.vmErr;
    this->stdInput = other.stdInput;
    this->lexErr = other.lexErr;
    this->parseErr = other.parseErr;
}

VirtualMachine::~VirtualMachine() {

}

VirtualMachine & VirtualMachine::operator = (const VirtualMachine &rhs) {
    if (this != &rhs) {
        this->stack = rhs.stack;
        this->vmErr = rhs.vmErr;
        this->stdInput = rhs.stdInput;
        this->lexErr = rhs.lexErr;
        this->parseErr = rhs.parseErr;
    }
    return *this;
}

void VirtualMachine::runInstruction(std::deque<std::deque<Token const * > > & instructions) {
    
    std::deque<Token const *> instruction;
    Token const *inst = nullptr;
    while (!instructions.empty()) {
        instruction = getNextInst(instructions);
        inst = nullptr;
        if (!instruction.empty()) {
            inst = getNextToken(instruction);
            if (inst->getType() == tokenType::instruction) {
                if (inst->getValue() == POP) {
                    pop();
                } else if (inst->getValue() == DUMP) {
                    dump();
                } else if (inst->getValue() == ADD) {
                    add();
                } else if (inst->getValue() == SUB) {
                    sub();
                } else if (inst->getValue() == MUL) {
                    mul();
                } else if (inst->getValue() == DIV) {
                    div();
                } else if (inst->getValue() == MOD) {
                    mod();
                } else if (inst->getValue() == PRINT) {
                    print();
                } else if (inst->getValue() == EXIT) {
                    if (lexErr == false && parseErr == false && vmErr == false)
                        exit( EXIT_SUCCESS );
                    else {
                        exit( EXIT_FAILURE );       
                    }
                }
            } else if (inst->getType() == tokenType::unaryInstruction) {
                Token const *operand = getNextToken(instruction);
                if (inst->getValue() == PUSH) {
                    push(operand);
                } else if (inst->getValue() == ASSERT) {
                    assert(operand);
                }
            }
        }
    }
    try {
        throw NoExitInstructionException();
    } catch (const NoExitInstructionException & e) {
        std::cerr << e.what() << std::endl;
        exit (EXIT_FAILURE);
    }
}

void VirtualMachine::pop(void) {
    try {
    if (!stack.empty())
        stack.pop_back();
    else {
        throw EmptyStackException();
        setError();
    }} catch (const EmptyStackException &e) {
        std::cerr << e.what() << std::endl;
        setError();
        if (stdInput == true)
            exit( EXIT_FAILURE );
    }
}

void VirtualMachine::dump(void) {
    try{
    if (!stack.empty()) {
        if (lexErr == false && parseErr == false && vmErr == false) {
            for (int i = stack.size() - 1; i >= 0; i--) {
                std::cout << stack[i]->toString() << std::endl;
            }
        }
    } else {
        throw EmptyStackException();
        setError();
    }} catch (const EmptyStackException &e) {
        std::cerr << e.what() << std::endl;
        setError();
        if (stdInput == true)
            exit( EXIT_FAILURE );
    }
}

void VirtualMachine::add(void) {
    try {
        if (!stack.empty()) {
            IOperand const * v1 = stack.back();
            stack.pop_back();
            if (!stack.empty()) {
                IOperand const * v2 = stack.back();
                stack.pop_back();
                IOperand const * res = *v1 + *v2;
                if (res != nullptr)
                    stack.push_back(res);
            } else {
                throw NotEnoughValuesException();
            }
        } else {
            throw NotEnoughValuesException();
        }
    } catch (const NotEnoughValuesException &e) {
        std::cerr << e.what() << std::endl;
        setError();
        if (stdInput == true)
            exit( EXIT_FAILURE );
    }
}

void VirtualMachine::sub(void) {
    try {
        if (!stack.empty()) {
            IOperand const * v1 = stack.back();
            stack.pop_back();
            if (!stack.empty()) {
                IOperand const * v2 = stack.back();
                stack.pop_back();
                IOperand const * res = *v2 - *v1;
                if (res != nullptr)
                    stack.push_back(res);
            } else {
                throw NotEnoughValuesException();
            }
        } else {
            throw NotEnoughValuesException();
        }
    } catch (const NotEnoughValuesException & e) {
        std::cerr << e.what() << std::endl;
        setError();
        if (stdInput == true)
            exit( EXIT_FAILURE );
    }
}

void VirtualMachine::mul(void) {
    try {
        if (!stack.empty()) {
            IOperand const * v1 = stack.back();
            stack.pop_back();
            if (!stack.empty()) {
                IOperand const * v2 = stack.back();
                stack.pop_back();
                IOperand const * res = *v1 * *v2;
                if (res != nullptr)
                    stack.push_back(res);
            } else {
                throw NotEnoughValuesException();
            }
        } else {
            throw NotEnoughValuesException();
        }
    } catch (const NotEnoughValuesException & e) {
        std::cerr << e.what() << std::endl;
        setError();
        if (stdInput == true)
            exit( EXIT_FAILURE );
    }
}

void VirtualMachine::div(void) {
    try {
    if (!stack.empty()) {
        IOperand const * v1 = stack.back();
        stack.pop_back();
        if (!stack.empty()) {
            IOperand const * v2 = stack.back();
            stack.pop_back();
            IOperand const * res = *v2 / *v1;
            if (res != nullptr)
                stack.push_back(res);
        } else {
            throw NotEnoughValuesException();
            setError();
        }
    } else {
        throw NotEnoughValuesException();
        setError();
    }} catch (const NotEnoughValuesException & e) {
        std::cerr << e.what() << std::endl;
        setError();
        if (stdInput == true)
            exit( EXIT_FAILURE );
    }
}

void VirtualMachine::mod(void) {
    try {
    if (!stack.empty()) {
        IOperand const * v1 = stack.back();
        stack.pop_back();
        if (!stack.empty()) {
            IOperand const * v2 = stack.back();
            stack.pop_back();
            IOperand const * res = *v2 % *v1;
            if (res != nullptr)
                stack.push_back(res);
        } else {
            throw NotEnoughValuesException();
            setError();
        }
    } else {
        throw NotEnoughValuesException();
        setError();
    }} catch (const NotEnoughValuesException & e) {
        std::cerr << e.what() << std::endl;
        setError();
        if (stdInput == true)
            exit( EXIT_FAILURE );
    }
}

void VirtualMachine::print(void) {
    try{
    if (stack.empty())
        throw EmptyStackException();
    IOperand const *operand = stack.back();
    if (operand->getType() == Int8) {
        char c = std::stoi(operand->toString());
        if (lexErr == false && parseErr == false && vmErr == false)
            std::cout << c << std::endl;
    } else {
        throw AssertionFailureException();
        setError();
    }} catch (const EmptyStackException & e) {
        std::cerr << e.what() << std::endl;
        setError();
        if (stdInput == true)
            exit( EXIT_FAILURE );
    } catch (const AssertionFailureException & e) {
        std::cerr << e.what() << std::endl;
        setError();
        if (stdInput == true)
            exit( EXIT_FAILURE );
    }
}

void VirtualMachine::push(Token const * token) {
    std::string rawData = token->getValue();
    IOperand const *operand = dataToOperand(rawData);
    if (operand != nullptr) {
        stack.push_back(operand);
    }
}

void VirtualMachine::assert(Token const * token) {
    try {
    IOperand const *v1 = dataToOperand(token->getValue());
    if (v1 == nullptr)
        return;
    if (stack.empty()) {
        throw EmptyStackException();
        setError();
    }
    IOperand const *v2 = stack.back();
    if (!(v1->getType() == v2->getType() && v1->toString() == v2->toString())) {
        throw AssertionFailureException();
        setError();
    }} catch (const EmptyStackException & e) {
        std::cerr << e.what() << std::endl;
        setError();
        if (stdInput == true)
            exit( EXIT_FAILURE );
    } catch (const AssertionFailureException & e) {
        std::cerr << e.what() << std::endl;
        setError();
        if (stdInput == true)
            exit( EXIT_FAILURE );
    }
}

IOperand const * VirtualMachine::dataToOperand(std::string const &data) {
    std::size_t lpoint = data.find("(");
    std::size_t tLen = lpoint;
    std::size_t vLen = data.length() - lpoint - 2;

    std::string type = data.substr(0, tLen);
    std::string value = data.substr(lpoint + 1, vLen);
    CreateOperand co;
    if (type == INT8) {
        return co.createOperand(Int8, value);
    } else if (type == INT16) {
        return co.createOperand(Int16, value);
    } else if (type == INT32) {
        return co.createOperand(Int32, value);
    } else if (type == FLOAT) {
        return co.createOperand(Float, value);
    } else if (type == DOUBLE) {
        return co.createOperand(Double, value);
    }
    return nullptr;
}


Token const * VirtualMachine::getNextToken(std::deque<Token const * > & tokens) {

    Token const * token = nullptr;
    if (!tokens.empty()) {
        token = tokens.front();
        tokens.pop_front();
    }
    return token;
}

std::deque<Token const *> VirtualMachine::getNextInst(std::deque<std::deque<Token const * > > & instructions) {
    std::deque<Token const *> instruction;
    if (!instructions.empty()) {
        instruction = instructions.front();
        instructions.pop_front();
    }
    return instruction;
}

bool VirtualMachine::hasError(void) const{
    return this->vmErr;
}

void VirtualMachine::setError(void) {
    if (this->vmErr == false)
        this->vmErr = true;
}

bool VirtualMachine::checkStdInput(void) const {
    return this->stdInput;
}