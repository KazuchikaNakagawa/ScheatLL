#include "../AssignExpr.hpp"
#include "../../Global/Globals.hpp"
#include "../../LLVMConverter/LLVMConverter.hpp"
#include "../../Type/ScheatLLType.hpp"
#include "../../Type/ScLLType.hpp"
using namespace scheat;

AssignExpr::AssignExpr(Expr *ptr, Expr *val, scheat::SourceLocation l)
: Expr(l)
{
    pointer = ptr;
    value = val;
}

AssignExpr::~AssignExpr()
{
}

llvm::Value *AssignExpr::LLVMConvert()
{
    auto llptr = pointer->LLVMEncode();
    auto llval = value->LLVMEncode();
    return ScheatllLLVMConverter->Builder().CreateStore(llval, llptr);
}

std::string AssignExpr::Decode() {
    return pointer->Decode() + " = " + value->Decode();
}

scheat_type* AssignExpr::Type()
{
    return scheat::Type(Void);
}
