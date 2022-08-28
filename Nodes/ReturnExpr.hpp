#if !defined(SCHEATEXPR_HPP)
#define SCHEATEXPR_HPP

#include "BasicNodes.hpp"

namespace scheatll
{

class ReturnExpr : public Expr
{
private:
    Expr *value;
protected:
    llvm::Value *LLVMConvert() override;
public:
    ReturnExpr(Expr *, scheat::SourceLocation);
    std::string Decode() override;
    scheatll_type* Type() override;
    scheatll_attribute getAttribute() override;
    ~ReturnExpr();
};


} // namespace scheatll

#endif // SCHEATEXPR_HPP
