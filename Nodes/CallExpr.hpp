#if !defined(SCHEATCALLEXPR_H)
#define SCHEATCALLEXPR_H

#include "BasicNodes.hpp"
#include <vector>

namespace scheatll
{

class DeclareFuncExpr;

class CallExpr : public Term
{
protected:
    llvm::Value *LLVMConvert() override;
    std::vector<Expr *> Args;
    Expr *Function;
public:
    CallExpr(Expr *, std::vector<Expr *>, scheat::SourceLocation);
    std::string Decode() override;
    scheatll_type* Type() override;
    ~CallExpr();
};


} // namespace scheatll


#endif // SCHEATCALLEXPR_H
