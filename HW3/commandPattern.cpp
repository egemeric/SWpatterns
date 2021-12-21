#include <iostream>
#include <vector>
#include <math.h>
using namespace std;
class Expression
{
private:
    double current;

public:
    Expression();
    ~Expression();
    double getCurrentValue();
    void updateSum(double val);
};

Expression::Expression(/* args */)
{
    this->current = 0;
}

Expression::~Expression()
{
}
double Expression::getCurrentValue()
{
    return this->current;
}

void Expression::updateSum(double x)
{
    this->current = x;
}

class Operation
{
private:
    double dx;

protected:
    Expression *expression;
    double nextValue;

public:
    Operation(Expression *expression, double nextValue, double dx);
    ~Operation();
    virtual void execute() = 0;
    double getDx();
};

Operation::Operation(Expression *expression, double nextValue, double dx)
{
    this->expression = expression;
    this->dx = dx;
    this->nextValue = nextValue;
}

double Operation::getDx()
{
    return this->dx;
}

Operation::~Operation()
{
}

class IntegrationOperation : public Operation
{
private:
public:
    IntegrationOperation(Expression *expression, double dx, double nextValue);
    ~IntegrationOperation();
    virtual void execute();
};

IntegrationOperation::IntegrationOperation(Expression *expression, double dx, double nextValue) : Operation(expression, nextValue, dx)
{
}

IntegrationOperation::~IntegrationOperation()
{
}

void IntegrationOperation::execute()
{ 
    expression->updateSum(expression->getCurrentValue() + (this->nextValue * this->getDx()));    
}

class DifferentiationOperation : public Operation
{

public:
    DifferentiationOperation(Expression *expression, double dx, double nextValue);
    ~DifferentiationOperation();
    virtual void execute();
};

DifferentiationOperation::DifferentiationOperation(Expression *expression, double dx, double nextValue) : Operation(expression, nextValue, dx)
{
    this->nextValue = nextValue;
}

DifferentiationOperation::~DifferentiationOperation()
{
}

void DifferentiationOperation::execute()
{
    expression->updateSum((this->nextValue - expression->getCurrentValue()) / (this->getDx()));
}

class Statement
{
private:
    vector<Operation *> op;
    double nextValue;

public:
    Statement(/* args */);
    ~Statement();
    void appendOperation(Operation *op);
    void evulate();
};

Statement::Statement(/* args */)
{
}

Statement::~Statement()
{
}
void Statement::appendOperation(Operation *op)
{
    this->op.push_back(op);
}

void Statement::evulate()
{
    for (vector<Operation *>::iterator it = op.begin(); it != op.end(); it++)
    {
        (*it)->execute();
    }
}

int main()
{
    Expression *expression = new Expression();
    Operation *integrationOperation = new IntegrationOperation(expression, 0.1, 5);
    Operation *diffOperation = new DifferentiationOperation(expression, 0.1, 5);
    Statement *statement = new Statement();
    statement->appendOperation(integrationOperation);
    statement->appendOperation(diffOperation);
    statement->evulate();
    cout << expression->getCurrentValue();
    return 0;
}
