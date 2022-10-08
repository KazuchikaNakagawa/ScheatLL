#include "../GetElementExpr.hpp"
#include "../../ScheatLL/ScheatLL.hpp"
#include "../../Global/Globals.hpp"
#include "../../LLVMConverter/LLVMConverter.hpp"
using namespace scheat;

GetElementExpr::GetElementExpr(Expr *base, int i, scheat_type* tp, scheat::SourceLocation loc)
: Term(loc), ptr(base), index(i), resultType(tp)
{
}

GetElementExpr::~GetElementExpr()
{
}

scheat_type* GetElementExpr::Type()
{
    return resultType->getPointerTo();
}

llvm::Value* GetElementExpr::LLVMConvert()
{
    auto Src = ptr->LLVMEncode();
    auto Index = Constant(index)->LLVMEncode();
    auto Tp = ptr->Type()->LLVMType();
    return ScheatllLLVMConverter->Builder().CreateGEP(Tp->getPointerElementType(), Src, Index);
}

std::string GetElementExpr::Decode()
{
    return ptr->Decode() + "." + std::to_string(index);
}
