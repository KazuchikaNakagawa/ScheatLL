#include "../ReferenceExpr.hpp"
using namespace scheatll;


ReferenceExpr::ReferenceExpr(Expr *ptr, scheat::SourceLocation l)
: Term(l)
{
    src = ptr;
}

ReferenceExpr::~ReferenceExpr()
{
}

llvm::Value *ReferenceExpr::LLVMConvert() {
    return src->LLVMEncode();
}

std::string ReferenceExpr::Decode()
{
    return src->Decode();
}

scheatll_type* ReferenceExpr::Type()
{
    return src->Type();
}
