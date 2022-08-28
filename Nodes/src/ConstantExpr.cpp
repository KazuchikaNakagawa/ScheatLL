#include "../ConstantExpr.hpp"
#include "../../Global/Globals.hpp"
#include "../../LLVMConverter/LLVMConverter.hpp"
#include "../../Type/ScheatLLType.hpp"
#include "../../Type/ScLLType.hpp"
#include <iostream>

using namespace scheatll;

ConstantInt32Expr::ConstantInt32Expr(int i, scheat::SourceLocation l)
: Term(l)
{
    data = i;
}

ConstantInt32Expr::~ConstantInt32Expr()
{
}

std::string ConstantInt32Expr::Decode() {
    return std::to_string(data);
}

llvm::Value *ConstantInt32Expr::LLVMConvert() {
    return ScheatllLLVMConverter->Builder().getInt32(data);
}

scheatll_type* ConstantInt32Expr::Type()
{
    return scheatll::Type(Int32);
}


ConstantDoubleExpr::ConstantDoubleExpr(double d, scheat::SourceLocation l)
: Term(l)
{
    data = d;
}

ConstantDoubleExpr::~ConstantDoubleExpr()
{
}

std::string ConstantDoubleExpr::Decode() {
    return std::to_string(data);
}

llvm::Value *ConstantDoubleExpr::LLVMConvert() {
    return llvm::ConstantFP::get(
        ScheatllLLVMConverter->Builder().getDoubleTy(),
        data
    );
}

scheatll_type* ConstantDoubleExpr::Type()
{
    return scheatll::Type(Double);
}

ConstantRawStringExpr::ConstantRawStringExpr(const char *buf, scheat::SourceLocation l)
: Term(l)
{
    str = buf;
}

ConstantRawStringExpr::~ConstantRawStringExpr()
{
}

std::string ConstantRawStringExpr::Decode() {
    return "\"" + std::string(str) + "\"";
}

llvm::Value *ConstantRawStringExpr::LLVMConvert()
{
    return ScheatllLLVMConverter->Builder().CreateGlobalStringPtr(str);
}

scheatll_type* ConstantRawStringExpr::Type()
{
    return (PointerType(scheatll::Type(Int8)));
}

ConstantBoolExpr::ConstantBoolExpr(bool b, scheat::SourceLocation l)
: Term(l)
{
    data = b;
}

ConstantBoolExpr::~ConstantBoolExpr()
{
}

std::string ConstantBoolExpr::Decode()
{
    return (data ? "true":"false");
}

scheatll_type* ConstantBoolExpr::Type()
{
    return scheatll::Type(Int1);
}

llvm::Value* ConstantBoolExpr::LLVMConvert()
{
    return ScheatllLLVMConverter->Builder().getInt1(data);
}
