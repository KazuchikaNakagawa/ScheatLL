#if !defined(SCHEATLLWHILEEXPR_HPP)
#define SCHEATLLWHILEEXPR_HPP

#include "BasicNodes.hpp"

namespace scheat
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
    scheat_type* Type() override; 
    ~WhileExpr();
};

} // namespace scheat


#endif // SCHEATLLWHILEEXPR_HPP
