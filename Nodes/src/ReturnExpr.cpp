#include "../ReturnExpr.hpp"
#include "../../API/ScheatLL.hpp"
#include "../../Global/Globals.hpp"
#include "../../LLVMConverter/LLVMConverter.hpp"
#include "../../Type/ScheatLLType.hpp"
using namespace scheatll;

ReturnExpr::ReturnExpr(Expr *expr)
{
    value = expr;
}

ReturnExpr::~ReturnExpr()
{
}

scheatll_attribute ReturnExpr::getAttribute()
{
    return Attribute(unreadable, unwritable);
}

scheatll_type* ReturnExpr::Type()
{
    return scheatll::Type(Void);
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
