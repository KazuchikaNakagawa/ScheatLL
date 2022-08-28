#if !defined(SCHEATREFERENCEEXPR_HPP)
#define SCHEATREFERENCEEXPR_HPP

#include "BasicNodes.hpp"

namespace scheatll
{

// it made identifier expression into TermExpr level.
class ReferenceExpr : public Term
{
private:
    Expr* src;
protected:
    llvm::Value *LLVMConvert() override;
public:
    ReferenceExpr(Expr *, scheat::SourceLocation);
    std::string Decode() override;
    scheatll_type* Type() override;
    Expr* getSrc() { return src; };
    ~ReferenceExpr();
};

} // namespace scheatll


#endif // SCHEATREFERENCEEXPR_HPP
