
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <sstream>
#include <cctype>

#include "Calculator.hpp"


/* --- Declarations --- */
bool isNumber(std::string const& s);
std::string getArgument(std::vector<std::string>& vec);


/* --- Implementations --- */
Calculator::~Calculator() {
    // Delete all tokens
    for (auto&& t : tokens) {
        std::cout << "Calc del " << t->getName() << std::endl;
        delete t;
    }
}

void Calculator::print(std::ostream& os, std::string const& target) {
    auto it = std::find_if(tokens.begin(), tokens.end(),
        [&target](auto& it) { return it->getName() == target; });
    if (it != std::end(tokens))
        os << (*it)->evaluate() << std::endl;
    else
        os << "Evaluation of expression " << target
        << " failed, register not found." << std::endl;
}

void Calculator::readInput() {
    std::string input;
    while (std::getline(std::cin, input)) {
        if (input == "quit" || input == "QUIT")
            break;
        parseInput(input);
    }
}

void Calculator::parseInput(std::string const& input) {
    // Split input into separate strings (copy stream into vector)
    std::vector<std::string> inputVec;
    std::istringstream stream(input);
    std::copy(std::istream_iterator<std::string>(stream),
        std::istream_iterator<std::string>(),
        std::back_inserter(inputVec));

    //std::cout << "inputVec.size() " << inputVec.size() << std::endl;

    // 3 arguments are given 
    if (inputVec.size() == 3) {
        std::string arg3 = getArgument(inputVec);
        std::string arg2 = getArgument(inputVec);
        std::string arg1 = getArgument(inputVec);

        // Create expression from argument 3
        Expression* exp3;
        if (isNumber(arg3))
            exp3 = new Expression(stoi(arg3));
        else
            exp3 = findToken(arg3);

        // Create operation from argument 2 and 3
        Operation* OP;
        if (arg2 == "ADD")
            OP = new Addition(exp3);
        else if (arg2 == "SUBTRACT")
            OP = new Subtraction(exp3);
        else if (arg2 == "MULTIPLY")
            OP = new Multiplication(exp3);
        else
            std::cout << "Invalid operation from user (input: " << input << ")" << std::endl;

        // Create expression from argument 1 with the above operation
        Expression* exp1 = findToken(arg1);
        exp1->addOP(OP);
        return;
    }
    // 2 arguments are given
    else if (inputVec.size() == 2) {
        std::string arg2 = getArgument(inputVec);
        std::string arg1 = getArgument(inputVec);

        if (arg1 == "PRINT") {
            print(std::cout, arg2);
            return;
        }
    }
    // All other input
    std::cout << "Invalid input from user (" << input << ")" << std::endl;
    /*std::cout << "3 arguments required: [register] [operation] [value]" << std::endl;
    std::cout << "or print [register]" << std::endl;*/
}

// Try to find token with name and add it if not found
Expression* Calculator::findToken(std::string const& name) {
    auto it = std::find_if(tokens.begin(), tokens.end(),
        [&name](auto& it) { return it->getName() == name; });

    if (it != std::end(tokens))
        return (*it);

    // If token not found, create a new token and add it
    Expression* exp = new Expression(name);
    tokens.push_back(exp);
    return exp;
}


bool isNumber(std::string const& s) {
    return std::all_of(s.begin(), s.end(), ::isdigit);
}

// Get argument as an upper case string from a vector 
std::string getArgument(std::vector<std::string>& vec) {
    if (!vec.empty()) {
        std::string arg = vec.back();
        // Convert string to upper case (toupper ignores numbers)
        std::transform(arg.begin(), arg.end(), arg.begin(), ::toupper);
        vec.pop_back();
        return arg;
    }
    return "NULL";
}

void Calculator::read(std::string filename) {
    //ifstream f(filename + ".txt");
    // Read from text file
    /*
    std::ifstream f(filename, std::ifstream::in);

    std::string input;
    while (getline(f, input)) {
        std::cout << input;
    }

    // Close the text file
    f.close();
    */
}


/*

    //tmp
    Expression* val = new Expression(2);
    Operation* OP = new Addition(val);
    Expression* A = new Expression(OP, "A");
    tokens.push_back(A);

    Expression* val2 = new Expression(3);
    Operation* OP2 = new Addition(val2);
    Expression* B = new Expression(OP2, "B");
    tokens.push_back(B);

    Operation* OP3 = new Multiplication(A);
    B->addOP(OP3);
    B->addOP(OP3);

    //print(std::cout, "A");
    print(std::cout, "B");

    Example
    res + rev
    res - cost
    rev + 200
    cost + sal
    sal + 20
    sal * 5
    cost + 10
    print res
    -> 90
*/


int main(int argc, char* argv[]) {
    Calculator calc{};

    // Read from file
    if (argc > 1) {
        std::cout << "Read from file" << std::endl;
        std::string filename = argv[1];
        calc.read(filename);
    }
    // Read from user
    else {
        std::cout << "Read from user" << std::endl;
    }
    calc.readInput();

    return 0;
}

