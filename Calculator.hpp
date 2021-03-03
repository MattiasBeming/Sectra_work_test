
#include <string>
#include <iostream>
#include <vector>
#include <memory>

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
    void print(std::ostream& os, std::string const& target);
    void readInput();
    void read(std::string const& filename);
    std::shared_ptr<Expression> findToken(std::string const& name);
private:
    void parseInput(std::string const& input);

    // Data Members
    std::vector<std::shared_ptr<Expression>> tokens;
};

class Expression {
public:
    Expression(int const& val);
    Expression(std::string const& name);
    Expression(std::shared_ptr<Operation> OP, std::string const& name);
    void addOP(std::shared_ptr<Operation> OP);
    int evaluate() const;
    std::string getName() const;
private:
    std::string name{ "VALUE" };
    int value{ 0 };
    std::vector<std::shared_ptr<Operation>> operations;
};

class Operation {
public:
    Operation(std::shared_ptr<Expression> exp);
    ~Operation() = default;
    virtual int evaluate(int const& val) const = 0; // Evaluates recursively
    virtual int evaluateSelf(int const& val) const = 0; // Evaluates expression
    std::string getExpName() const;
protected:
    std::shared_ptr<Expression> exp;
};

class Addition : public Operation {
public:
    using Operation::Operation;
    int evaluate(int const& val) const override;
    int evaluateSelf(int const& val) const override;
};

class Subtraction : public Operation {
public:
    using Operation::Operation;
    int evaluate(int const& val) const override;
    int evaluateSelf(int const&) const override;
};

class Multiplication : public Operation {
public:
    using Operation::Operation;
    int evaluate(int const& val) const override;
    int evaluateSelf(int const& val) const override;
};
