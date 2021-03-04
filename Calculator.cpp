
#include <string>
#include <cctype>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <memory>

#include "Calculator.hpp"


/* --- Declarations --- */
bool isNumber(std::string const& s);
std::string getArgument(std::vector<std::string>& vec);
void printInstructions();

/* --- Implementations --- */
void Calculator::print(std::ostream& os, std::string const& target) {
    auto it = std::find_if(tokens.begin(), tokens.end(),
        [&target](auto& it) { return it->getName() == target; });
    if (it != std::end(tokens))
        os << (*it)->evaluate() << std::endl;
    else
        os << "Evaluation of expression \"" << target
        << "\" failed, register not found." << std::endl;
}

void Calculator::readInput() {
    std::string input;
    while (std::getline(std::cin, input)) {
        if (input == "quit" || input == "QUIT" || input == "q")
            break;
        parseInput(input);
    }
}

void Calculator::read(std::string const& filename) {
    // Read from text file
    std::ifstream f;
    f.open(filename, std::ifstream::in);

    std::string input;
    while (getline(f, input)) {
        parseInput(input);
    }

    // Close the text file
    f.close();
}

void Calculator::parseInput(std::string const& input) {
    // Split input into separate strings (copy stream into vector)
    std::vector<std::string> inputVec;
    std::istringstream stream(input);
    std::copy(std::istream_iterator<std::string>(stream),
        std::istream_iterator<std::string>(),
        std::back_inserter(inputVec));

    // 3 arguments are given 
    if (inputVec.size() == 3) {
        std::string arg3 = getArgument(inputVec);
        std::string arg2 = getArgument(inputVec);
        std::string arg1 = getArgument(inputVec);

        // Create Token from argument 3
        std::shared_ptr<Token> t3;
        if (isNumber(arg3))
            t3 = std::make_shared<Token>(stoi(arg3)); //Create value-Token
        else
            t3 = findToken(arg3);

        // Create operation from argument 2 and 3
        std::shared_ptr<Operation> OP;
        if ((arg2 == "ADD") | (arg2 == "+"))
            OP = std::make_shared<Addition>(t3);
        else if ((arg2 == "SUBTRACT") | (arg2 == "SUB") | (arg2 == "-"))
            OP = std::make_shared<Subtraction>(t3);
        else if ((arg2 == "MULTIPLY") | (arg2 == "MULT") | (arg2 == "*"))
            OP = std::make_shared<Multiplication>(t3);
        else
            std::cout << "Invalid operation from user (input: " << input << ")" << std::endl;

        // Create Token from argument 1 with the above operation
        std::shared_ptr<Token> t1 = findToken(arg1);
        t1->addOP(OP);
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
    // HELP argument is given
    else if (inputVec.size() == 1 && getArgument(inputVec) == "HELP") {
        printInstructions();
        return;
    }
    // All other input
    std::cout << "Invalid input from user (input: " << input << ")" << std::endl;
}

// Try to find token with name and add it if not found
std::shared_ptr<Token> Calculator::findToken(std::string const& name) {
    auto it = std::find_if(tokens.begin(), tokens.end(),
        [&name](auto& it) { return it->getName() == name; });

    if (it != std::end(tokens))
        return (*it);

    // If token not found, create a new token and add it
    std::shared_ptr<Token> t = std::make_shared<Token>(name);
    tokens.push_back(t);
    return t;
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

void printInstructions() {
    std::cout
        << "Available Commands:\n"
        << "Command #1: [register] [operation] [value]\n"
        << "Command #2: print [register]\n"
        << "Command #3: help\n"
        << "Command #4: quit, q\n"
        << "Available Operations:\n"
        << "Operation #1: add, +\n"
        << "Operation #2: subtract, sub, -\n"
        << "Operation #3: multiply, mult, *"
        << std::endl;
}

int main(int argc, char* argv[]) {
    Calculator calc{};

    // Read from file
    if (argc > 1) {
        std::cout << "Results from file: " << std::endl;
        std::string filename = argv[1];
        calc.read(filename);
    }
    // Read from terminal
    else {
        std::cout << "Simple Calculator\n"
            << "Write help to see available commands!"
            << std::endl;
        calc.readInput();
    }

    return 0;
}

