#if !defined(SCHEATLLWHILEEXPR_HPP)
#define SCHEATLLWHILEEXPR_HPP

#include "BasicNodes.hpp"

namespace scheatll
{

class Codes;

class WhileExpr : public Expr
{
protected:
    Expr *Condition;
    Codes *Body;
    llvm::Value *LLVMConvert() override;
public:
    WhileExpr(Expr *, Codes *);
    std::string Decode() override;
    scheatll_type* Type() override; 
    ~WhileExpr();
};

} // namespace scheatll


#endif // SCHEATLLWHILEEXPR_HPP
