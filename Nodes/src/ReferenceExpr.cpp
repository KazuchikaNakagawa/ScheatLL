#include "../ReferenceExpr.hpp"
using namespace scheat;


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

scheat_type* ReferenceExpr::Type()
{
    return src->Type();
}
