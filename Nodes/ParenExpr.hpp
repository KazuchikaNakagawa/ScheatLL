#if !defined(SCHEATPARENEXPR_H)
#define SCHEATPARENEXPR_H

#include "BasicNodes.hpp"

namespace scheatll
{

class ParenExpr : public Term
{
private:
    Expr *src;

protected:
    llvm::Value *LLVMConvert() override;
public:
    ParenExpr(Expr *, scheat::SourceLocation);
    std::string Decode() override;
    scheatll_type* Type() override;
    ~ParenExpr();
};

} // namespace scheatll


#endif // SCHEATPARENEXPR_H
