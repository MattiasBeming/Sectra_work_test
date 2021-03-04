
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <memory>

#include "Calculator.hpp"


/* --- Token --- */
Token::Token(int const& val) : value{ val } {}
Token::Token(std::string const& name) : name{ name } {}

void Token::addOP(std::shared_ptr<Operation> OP) {
    operations.push_back(OP);
}

int Token::evaluate() const {
    // If Token is a number
    if (operations.empty())
        return value;

    // If Token has operations
    int val = value;
    std::for_each(operations.begin(), operations.end(),
        [&val](std::shared_ptr<Operation> OP) {
            val = OP->evaluate(val); });
    return val;
}

std::string Token::getName() const {
    return name;
}

/* --- Operation --- */
Operation::Operation(std::shared_ptr<Token> token) : token{ token } {}

/* --- Addition --- */
int Addition::evaluate(int const& val) const {
    return val + token->evaluate();
}

/* --- Subtraction --- */
int Subtraction::evaluate(int const& val) const {
    return val - token->evaluate();
}

/* --- Multiplication --- */
int Multiplication::evaluate(int const& val) const {
    return val * token->evaluate();
}
