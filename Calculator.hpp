
#include <string>
#include <iostream>
#include <vector>

#pragma once

/**
 * Assumptions:
 * Calculator is only required to handle integers and not any other data type.
 *     Possible extension: add template parameter to be able to represent values
 *                         as any integer or floating point.
 *
*/


/* --- Declarations --- */
class Calculator;
class Expression;
class Operation;
class Addition;
class Subtraction;
class Multiplication;


/* --- Definitions --- */
class Calculator {
public:
    Calculator() = default;
    ~Calculator();
    void print(std::ostream& os, std::string const& target);
    void readInput();
    void read(std::string filename);
    Expression* findToken(std::string const& name);
private:
    void parseInput(std::string const& input);

    // Data Members
    std::vector<Expression*> tokens;
};

class Expression {
public:
    Expression(int const& val);
    Expression(std::string const& name);
    Expression(Operation* OP, std::string const& name);
    ~Expression();
    void addOP(Operation* OP);
    int evaluate() const;
    std::string getName() const;
private:
    std::string name{ "VALUE" };
    int value{ 0 };
    std::vector<Operation*> operations;
};

class Operation {
public:
    Operation(Expression* exp);
    ~Operation();
    virtual int evaluate(int const& val) const = 0;
    Expression* exp;
protected:
};

class Addition : public Operation {
public:
    using Operation::Operation;
    int evaluate(int const& val) const override;
};

class Subtraction : public Operation {
public:
    using Operation::Operation;
    int evaluate(int const& val) const override;
};

class Multiplication : public Operation {
public:
    using Operation::Operation;
    int evaluate(int const& val) const override;
};
