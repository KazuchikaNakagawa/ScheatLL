#if !defined(SCHEATIFEXPR_HPP)
#define SCHEATIFEXPR_HPP

#include "BasicNodes.hpp"

namespace scheatll
{

class Codes;

// Scheat has two kinds of if statement
// if statement -> normal void if statement
// value_if statement -> have a value because of 'become' statement
/*

this message is if login_is_completed, become "welcome",
else, become "please login".

return if login_is_completed, become user_data.

*/

// normal if
class IfExpr : public Expr
{
protected:
    Expr *Condition;
    Codes *Then;
    llvm::Value *LLVMConvert() override;
public:
    IfExpr(Expr *, Codes *);
    std::string Decode() override;
    scheatll_type* Type() override;
    ~IfExpr();
};

class IfElseExpr : public Expr
{
protected:
    Expr *Condition;
    Codes *Then;
    Codes *Else;
    llvm::Value *LLVMConvert() override;
public:
    IfElseExpr(Expr *, Codes *, Codes *);
    std::string Decode() override;
    scheatll_type* Type() override;
    ~IfElseExpr();
};


} // namespace scheatll

#endif // SCHEATIFEXPR_HPP
