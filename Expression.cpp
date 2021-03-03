
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <memory>

#include "Calculator.hpp"


/* --- Expression --- */
Expression::Expression(int const& val) : value{ val } {}
Expression::Expression(std::string const& name) : name{ name } {}
Expression::Expression(std::shared_ptr<Operation> OP, std::string const& name) :
    operations{ OP }, name{ name } {}

void Expression::addOP(std::shared_ptr<Operation> OP) {
    operations.push_back(OP);
}

int Expression::evaluate() const {
    // If expression is a number
    if (operations.empty())
        return value;

    // If expression has operations
    int val = value;
    std::string expName = name;
    std::for_each(operations.begin(), operations.end(),
        [&val, expName](std::shared_ptr<Operation> OP) {
            if (OP->getExpName() != expName)
                val = OP->evaluate(val);
            else // Expression has the same expression in operations (ex. A add A)
                val = OP->evaluateSelf(val);
        });
    return val;
}

std::string Expression::getName() const {
    return name;
}

/* --- Operation --- */
Operation::Operation(std::shared_ptr<Expression> exp) : exp{ exp } {}

std::string Operation::getExpName() const {
    return exp->getName();
}

/* --- Addition --- */
int Addition::evaluate(int const& val) const {
    return val + exp->evaluate();
}

int Addition::evaluateSelf(int const& val) const {
    return val + val;
}

/* --- Subtraction --- */
int Subtraction::evaluate(int const& val) const {
    return val - exp->evaluate();
}

int Subtraction::evaluateSelf(int const& val) const {
    return 0;
}

/* --- Multiplication --- */
int Multiplication::evaluate(int const& val) const {
    return val * exp->evaluate();
}

int Multiplication::evaluateSelf(int const& val) const {
    return val * val;
}
