
#include <string>
#include <iostream>
#include <vector>
#include <memory>

#pragma once


/* --- Declarations --- */
class Calculator;
class Token;
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
    std::shared_ptr<Token> findToken(std::string const& name);
private:
    void parseInput(std::string const& input);

    // Data Members
    std::vector<std::shared_ptr<Token>> tokens;
};

class Token {
public:
    Token(int const& val);
    Token(std::string const& name);
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
    Operation(std::shared_ptr<Token> token);
    ~Operation() = default;
    virtual int evaluate(int const& val) const = 0; // Evaluates recursively
protected:
    std::shared_ptr<Token> token;
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
