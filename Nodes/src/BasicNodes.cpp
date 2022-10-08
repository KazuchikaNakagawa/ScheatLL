#include "../BasicNodes.hpp"
#include "../../Type/ScLLType.hpp"
#include "../../Global/Globals.hpp"
#include "../../Exec/ScheatLLExec.hpp"
#include "../../Error/ScheatLLError.hpp"

using namespace scheat;

llvm::Value *Expr::LLVMEncode() 
{
    if (LLVMVal == nullptr)
    {
        LLVMVal = LLVMConvert();
    }
    return LLVMVal;
}

scheat_type* Expr::Type() {
    return scheat::Type(Void);
}

Expr::Expr(scheat::SourceLocation loc) : location(loc)
{
}

Expr::~Expr()
{
}

PrimaryExpr::~PrimaryExpr()
{
}

Term::~Term()
{
}

Term* Expr::AccessTo(std::string id, scheat::SourceLocation l)
{
    if (Type() == nullptr)
    {
        throw scheat_value_error();
    }
    
    return Type()->getElementType()->Access(this, id, l);
}

Attributed::Attributed()
{
}

Attributed::~Attributed()
{
}
