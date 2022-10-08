#include "../ReadExpr.hpp"
#include <typeinfo>
#include <cstdlib>
#include "../../Global/Globals.hpp"
#include "../../LLVMConverter/LLVMConverter.hpp"
#include "../../Type/ScheatLLType.hpp"

using namespace scheat;


ReadExpr::ReadExpr(Expr *expr, scheat::SourceLocation l)
: Term(l)
{
    // it does not check readability.
    src = expr;
}

ReadExpr::~ReadExpr()
{
}

std::string ReadExpr::Decode()
{
    return "*" + src->Decode();
}

llvm::Value* ReadExpr::LLVMConvert()
{
    return ScheatllLLVMConverter->Builder().CreateLoad(
        src->Type()->getElementType()->LLVMType(), 
        src->LLVMEncode()
    );
}

scheat_type* ReadExpr::Type()
{
    return src->Type()->getElementType();
}
