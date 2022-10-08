#include "../ReturnExpr.hpp"
#include "../../ScheatLL/ScheatLL.hpp"
#include "../../Global/Globals.hpp"
#include "../../LLVMConverter/LLVMConverter.hpp"
#include "../../Type/ScheatLLType.hpp"
using namespace scheat;

ReturnExpr::ReturnExpr(Expr *expr, scheat::SourceLocation l)
: Expr(l)
{
    value = expr;
}

ReturnExpr::~ReturnExpr()
{
}

scheat_attribute ReturnExpr::getAttribute()
{
    return Attribute(unreadable, unwritable);
}

scheat_type* ReturnExpr::Type()
{
    return scheat::Type(Void);
}

llvm::Value* ReturnExpr::LLVMConvert()
{
    ScheatllLLVMConverter->Builder().CreateRet(value->LLVMEncode());
    return nullptr;
}

std::string ReturnExpr::Decode()
{
    return "return " + value->Decode();
}
