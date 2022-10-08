#if !defined(SCHEATREADEXPR_HPP)
#define SCHEATREADEXPR_HPP

#include "BasicNodes.hpp"

namespace scheat
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
    scheat_type* Type() override;
    ~ReadExpr();
};

} // namespace scheat


#endif // SCHEATREADEXPR_HPP
