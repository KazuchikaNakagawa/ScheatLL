#include "../BasicNodes.hpp"
#include "../../Type/ScLLType.hpp"

using namespace scheatll;

llvm::Value *Expr::LLVMEncode() 
{
    if (LLVMVal == nullptr)
    {
        LLVMVal = LLVMConvert();
    }
    return LLVMVal;
}

scheatll_type* Expr::Type() {
    return scheatll::Type(Void);
}

Expr::Expr(scheat::SourceLocation loc) : location(loc)
{
}

Expr::~Expr()
{
}

PrimaryExpr::PrimaryExpr()
{
}

PrimaryExpr::~PrimaryExpr()
{
}

Term::Term() 
{
}

Term::~Term()
{
}


Attributed::Attributed()
{
}

Attributed::~Attributed()
{
}
