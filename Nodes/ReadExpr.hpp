#if !defined(SCHEATREADEXPR_HPP)
#define SCHEATREADEXPR_HPP

#include "BasicNodes.hpp"

namespace scheatll
{

// creates Load instruction in LLVM
class ReadExpr : public Term
{
private:
    Expr *src;

protected:
    llvm::Value *LLVMConvert() override;
public:
    ReadExpr(Expr *, scheat::SourceLocation);
    std::string Decode() override;
    scheatll_type* Type() override;
    ~ReadExpr();
};

} // namespace scheatll


#endif // SCHEATREADEXPR_HPP
