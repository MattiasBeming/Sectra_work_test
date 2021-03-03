
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

#include "Calculator.hpp"


/* --- Expression --- */
Expression::Expression(int const& val) : value{ val } {}
Expression::Expression(std::string const& name) : name{ name } {}
Expression::Expression(Operation* OP, std::string const& name) :
    operations{ OP }, name{ name } {}

Expression::~Expression() {
    for (auto&& OP : operations) {
        std::cout << "Exp del " << OP->exp->getName() << std::endl;
        delete OP;
    }
}

void Expression::addOP(Operation* OP) {
    // Check existing tokens and do not if exist ??
    operations.push_back(OP);
}

int Expression::evaluate() const {
    // If expression is a number
    if (operations.empty())
        return value;

    // If expression has operations
    int val = value;
    std::for_each(operations.begin(), operations.end(),
        [&val](Operation* OP) {
            val = OP->evaluate(val);
        });
    return val;
}

std::string Expression::getName() const {
    return name;
}

/* --- Operation --- */
Operation::Operation(Expression* exp) : exp{ exp } {}
Operation::~Operation() {
    delete exp;
}

/* --- Addition --- */
int Addition::evaluate(int const& val) const {
    return val + exp->evaluate();
}

/* --- Subtraction --- */
int Subtraction::evaluate(int const& val) const {
    return val - exp->evaluate();
}

/* --- Multiplication --- */
int Multiplication::evaluate(int const& val) const {
    return val * exp->evaluate();
}
