#include "../ConstantExpr.hpp"
#include "../../Global/Globals.hpp"
#include "../../LLVMConverter/LLVMConverter.hpp"
#include "../../Type/ScheatLLType.hpp"
#include "../../Type/ScLLType.hpp"
#include <iostream>

using namespace scheat;

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

scheat_type* ConstantInt32Expr::Type()
{
    return scheat::Type(Int32);
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

scheat_type* ConstantDoubleExpr::Type()
{
    return scheat::Type(Double);
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

scheat_type* ConstantRawStringExpr::Type()
{
    return (PointerType(scheat::Type(Int8)));
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

scheat_type* ConstantBoolExpr::Type()
{
    return scheat::Type(Int1);
}

llvm::Value* ConstantBoolExpr::LLVMConvert()
{
    return ScheatllLLVMConverter->Builder().getInt1(data);
}


ConstantExprNil::ConstantExprNil(scheat_type* tp, scheat::SourceLocation l)
:Term(l)
{
    type = tp;
}

llvm::Value *ConstantExprNil::LLVMConvert()
{
    return llvm::ConstantPointerNull::get(type->LLVMType()->getPointerTo());
}

ConstantExprNil::~ConstantExprNil()
{
}

scheat_type* ConstantExprNil::Type() {
    return type->getPointerTo();
};

std::string ConstantExprNil::Decode() {
    return type->typeName() + " nil";
};
