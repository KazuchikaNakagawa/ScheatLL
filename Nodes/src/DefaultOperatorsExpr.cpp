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
        return ScheatllLLVMConverter->Builder().CreateSub(Lhs, Rhs);
    }

    else if (operatorSymbol == ">")
    {
        return ScheatllLLVMConverter->Builder().CreateICmpSGT(Lhs, Rhs);
    }
    
    else if (operatorSymbol == "<")
    {
        return ScheatllLLVMConverter->Builder().CreateICmpSLT(Lhs, Rhs);
    }
    
    else if (operatorSymbol == ">=")
    {
        return ScheatllLLVMConverter->Builder().CreateICmpSGE(Lhs, Rhs);
    }
    
    else if (operatorSymbol == "<=")
    {
        return ScheatllLLVMConverter->Builder().CreateICmpSLE(Lhs, Rhs);
    }

    else if (operatorSymbol == "==")
    {
        return ScheatllLLVMConverter->Builder().CreateICmpEQ(Lhs, Rhs);
    }

    else if (operatorSymbol == "!=")
    {
        return ScheatllLLVMConverter->Builder().CreateICmpNE(Lhs, Rhs);
    }
    
    else
    {
        throw scheatll_operator_not_exist_error();
    }
}

scheatll_type* IntIntInfixOperatorExpr::Type()
{
    if (operatorSymbol == "+")
    {
        return scheatll::Type(Int32);
    }

    else if (operatorSymbol == "-")
    {
        return scheatll::Type(Int32);
    }

    else if (operatorSymbol == ">")
    {
        return scheatll::Type(Int1);
    }
    
    else if (operatorSymbol == "<")
    {
        return scheatll::Type(Int1);
    }
    
    else if (operatorSymbol == ">=")
    {
        return scheatll::Type(Int1);
    }
    
    else if (operatorSymbol == "<=")
    {
        return scheatll::Type(Int1);
    }

    else if (operatorSymbol == "==")
    {
        return scheatll::Type(Int1);
    }

    else if (operatorSymbol == "!=")
    {
        return scheatll::Type(Int1);
    }
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
        auto lfp = ScheatllLLVMConverter->Builder().CreateSIToFP(Lhs, ScheatllLLVMConverter->Builder().getDoubleTy());
        auto rfp = ScheatllLLVMConverter->Builder().CreateSIToFP(Rhs, ScheatllLLVMConverter->Builder().getDoubleTy());
        return ScheatllLLVMConverter->Builder().CreateFDiv(lfp, rfp);
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

DoubleDoubleInfixOperatorExpr::DoubleDoubleInfixOperatorExpr(Expr *l, std::string o, Expr *r, scheat::SourceLocation loc)
: Expr(loc)
{
    lhs = l;
    operatorSymbol = o;
    rhs = r;
}

DoubleDoubleInfixOperatorExpr::~DoubleDoubleInfixOperatorExpr()
{
}

std::string DoubleDoubleInfixOperatorExpr::Decode()
{
    return lhs->Decode() + " " + operatorSymbol + " " + rhs->Decode();
}

scheatll_type* DoubleDoubleInfixOperatorExpr::Type()
{
    if (operatorSymbol == ">")
    {
        return scheatll::Type(Int1);
    }
    
    else if (operatorSymbol == "<")
    {
        return scheatll::Type(Int1);
    }
    
    else if (operatorSymbol == ">=")
    {
        return scheatll::Type(Int1);
    }
    
    else if (operatorSymbol == "<=")
    {
        return scheatll::Type(Int1);
    }

    else if (operatorSymbol == "==")
    {
        return scheatll::Type(Int1);
    }

    else if (operatorSymbol == "!=")
    {
        return scheatll::Type(Int1);
    }
    return scheatll::Type(Double);
}

llvm::Value *DoubleDoubleInfixOperatorExpr::LLVMConvert()
{
    auto Lhs = lhs->LLVMEncode();
    auto Rhs = rhs->LLVMEncode();
    if (operatorSymbol == "+")
    {
        return ScheatllLLVMConverter->Builder().CreateFAdd(Lhs, Rhs);
    }

    else if (operatorSymbol == "-")
    {
        return ScheatllLLVMConverter->Builder().CreateFSub(Lhs, Rhs);
    }

    else if (operatorSymbol == ">")
    {
        return ScheatllLLVMConverter->Builder().CreateFCmpOGT(Lhs, Rhs);
    }
    
    else if (operatorSymbol == "<")
    {
        return ScheatllLLVMConverter->Builder().CreateFCmpOLT(Lhs, Rhs);
    }
    
    else if (operatorSymbol == ">=")
    {
        return ScheatllLLVMConverter->Builder().CreateFCmpOGE(Lhs, Rhs);
    }
    
    else if (operatorSymbol == "<=")
    {
        return ScheatllLLVMConverter->Builder().CreateFCmpOLE(Lhs, Rhs);
    }

    else if (operatorSymbol == "==")
    {
        return ScheatllLLVMConverter->Builder().CreateFCmpOEQ(Lhs, Rhs);
    }

    else if (operatorSymbol == "!=")
    {
        return ScheatllLLVMConverter->Builder().CreateFCmpONE(Lhs, Rhs);
    }
    
    else
    {
        throw scheatll_operator_not_exist_error();
    }
}

// Primary

DoubleDoubleInfixPrimaryOperatorExpr::DoubleDoubleInfixPrimaryOperatorExpr(PrimaryExpr *l, std::string o, PrimaryExpr *r, scheat::SourceLocation loc)
: PrimaryExpr(loc)
{
    lhs = l;
    operatorSymbol = o;
    rhs = r;
}

DoubleDoubleInfixPrimaryOperatorExpr::~DoubleDoubleInfixPrimaryOperatorExpr()
{
}

std::string DoubleDoubleInfixPrimaryOperatorExpr::Decode()
{
    return lhs->Decode() + " " + operatorSymbol + " " + rhs->Decode();
}

llvm::Value *DoubleDoubleInfixPrimaryOperatorExpr::LLVMConvert()
{
    auto Lhs = lhs->LLVMEncode();
    auto Rhs = rhs->LLVMEncode();
    if (operatorSymbol == "*")
    {
        return ScheatllLLVMConverter->Builder().CreateFMul(Lhs, Rhs);
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

scheatll_type* DoubleDoubleInfixPrimaryOperatorExpr::Type()
{
    return scheatll::Type(Double);
}
