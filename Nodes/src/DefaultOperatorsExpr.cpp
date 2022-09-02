#include "../DefaultOperatorsExpr.hpp"
#include "../../Global/Globals.hpp"
#include "../../LLVMConverter/LLVMConverter.hpp"
#include "../../Error/ScheatLLError.hpp"
#include "../../API/ScheatLL.hpp"
using namespace scheatll;

IntIntInfixOperatorExpr::IntIntInfixOperatorExpr(Expr *l, std::string o, Expr *r, scheat::SourceLocation loc)
: Expr(loc)
{
    lhs = l;
    operatorSymbol = o;
    rhs = r;
}

IntIntInfixOperatorExpr::~IntIntInfixOperatorExpr()
{
}

llvm::Value *IntIntInfixOperatorExpr::LLVMConvert()
{
    auto Lhs = lhs->LLVMEncode();
    auto Rhs = rhs->LLVMEncode();
    if (operatorSymbol == "+")
    {
        return ScheatllLLVMConverter->Builder().CreateAdd(Lhs, Rhs);
    }

    else if (operatorSymbol == "-")
    {
        // TODO: is this okay?
        return ScheatllLLVMConverter->Builder().CreateSub(Lhs, Rhs);
    }
    
    else
    {
        throw scheatll_operator_not_exist_error();
    }
}

scheatll_type* IntIntInfixOperatorExpr::Type()
{
    return scheatll::Type(Int32);
}

std::string IntIntInfixOperatorExpr::Decode()
{
    return lhs->Decode() + " " + operatorSymbol + " " + rhs->Decode();
}

IntIntInfixPrimaryOperatorExpr::IntIntInfixPrimaryOperatorExpr(PrimaryExpr *l, std::string o, PrimaryExpr *r, scheat::SourceLocation loc)
: PrimaryExpr(loc)
{
    lhs = l;
    operatorSymbol = o;
    rhs = r;
}

IntIntInfixPrimaryOperatorExpr::~IntIntInfixPrimaryOperatorExpr()
{
}

llvm::Value *IntIntInfixPrimaryOperatorExpr::LLVMConvert()
{
    auto Lhs = lhs->LLVMEncode();
    auto Rhs = rhs->LLVMEncode();
    if (operatorSymbol == "*")
    {
        return ScheatllLLVMConverter->Builder().CreateMul(Lhs, Rhs);
    }

    else if (operatorSymbol == "/")
    {
        return ScheatllLLVMConverter->Builder().CreateFDiv(Lhs, Rhs);
    }
    
    else
    {
        throw scheatll_operator_not_exist_error();
    }
}

std::string IntIntInfixPrimaryOperatorExpr::Decode()
{
    return lhs->Decode() + " " + operatorSymbol + " " + rhs->Decode();
}

scheatll_type* IntIntInfixPrimaryOperatorExpr::Type()
{
    if (operatorSymbol == "/")
    {
        return scheatll::Type(Double);
    }
    return scheatll::Type(Int32);
}
