#if !defined(SCHEATPARENEXPR_H)
#define SCHEATPARENEXPR_H

#include "BasicNodes.hpp"

namespace scheat
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
    scheat_type* Type() override;
    ~ParenExpr();
};

} // namespace scheat


#endif // SCHEATPARENEXPR_H
