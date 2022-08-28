#if !defined(SCHEATASSIGNEXPR_HPP)
#define SCHEATASSIGNEXPR_HPP

#include "BasicNodes.hpp"

namespace scheatll
{

class AssignExpr : public Expr
{
private:
    Expr *pointer;
    Expr *value;
protected:
    llvm::Value *LLVMConvert() override;
public:
    AssignExpr(Expr *, Expr *, scheat::SourceLocation);
    std::string Decode() override;
    scheatll_type* Type() override;
    ~AssignExpr();
};

} // namespace scheatll


#endif // SCHEATASSIGNEXPR_HPP
