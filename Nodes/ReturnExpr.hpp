#if !defined(SCHEATEXPR_HPP)
#define SCHEATEXPR_HPP

#include "BasicNodes.hpp"

namespace scheat
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
    scheat_type* Type() override;
    scheat_attribute getAttribute() override;
    ~ReturnExpr();
};


} // namespace scheat

#endif // SCHEATEXPR_HPP
