#include "OperatorImpl.hpp"
using namespace scheatll;


OperatorImpl::OperatorImpl(/* args */)
{
}

OperatorImpl::~OperatorImpl()
{
}

void OperatorImpl::AddInfixOperator(std::string n, OperatorPrecedence p)
{
    Operator newOp;
    newOp.Position = Infix;
    newOp.Precedence = p;
    OperatorTable[n] = newOp;
}

void OperatorImpl::AddPrefixOperator(std::string n, OperatorPrecedence p)
{
    Operator newOp;
    newOp.Position = Prefix;
    newOp.Precedence = p;
    OperatorTable[n] = newOp;
}

void OperatorImpl::AddPostfixOperator(std::string n, OperatorPrecedence p)
{
    Operator newOp;
    newOp.Position = Postfix;
    newOp.Precedence = p;
    OperatorTable[n] = newOp;
}

Operator *OperatorImpl::FindOperator(std::string key)
{
    auto iter = OperatorTable.find(key);
    if (iter == OperatorTable.end())
    {
        return nullptr;
    }
    return &iter->second;
}
