#include "../ParenExpr.hpp"
using namespace scheat;

llvm::Value *ParenExpr::LLVMConvert()
{
    return src->LLVMEncode();
}

ParenExpr::ParenExpr(Expr *expr, scheat::SourceLocation l)
: Term(l)
{
    src = expr;
}

ParenExpr::~ParenExpr()
{
}

std::string ParenExpr::Decode()
{
    return "(" + src->Decode() + ")";
}

scheat_type* ParenExpr::Type()
{
    return src->Type();
}
