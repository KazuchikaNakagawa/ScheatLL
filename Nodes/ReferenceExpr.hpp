#if !defined(SCHEATREFERENCEEXPR_HPP)
#define SCHEATREFERENCEEXPR_HPP

#include "BasicNodes.hpp"

namespace scheat
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
    scheat_type* Type() override;
    Expr* getSrc() { return src; };
    scheat_attribute getAttribute() override{
        return src->getAttribute();
    }
    ~ReferenceExpr();
};

} // namespace scheat


#endif // SCHEATREFERENCEEXPR_HPP
