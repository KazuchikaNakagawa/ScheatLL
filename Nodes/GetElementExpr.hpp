#if !defined(SCHEATGETELEMENTEXPR_HPP)
#define SCHEATGETELEMENTEXPR_HPP

#include "BasicNodes.hpp"

namespace scheat
{

class GetElementExpr : public Term
{
protected:
    llvm::Value *LLVMConvert() override;
    Expr *ptr;
    int index;
    scheat_type* resultType;
public:
    GetElementExpr(Expr *, int, scheat_type*, scheat::SourceLocation);
    std::string Decode() override;
    scheat_type* Type() override;
    ~GetElementExpr();
};

} // namespace scheat


#endif // SCHEATGETELEMENTEXPR_HPP
