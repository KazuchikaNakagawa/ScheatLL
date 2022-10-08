#if !defined(SCHEATCALLEXPR_H)
#define SCHEATCALLEXPR_H

#include "BasicNodes.hpp"
#include <vector>

namespace scheat
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
    scheat_type* Type() override;
    ~CallExpr();
};


} // namespace scheat


#endif // SCHEATCALLEXPR_H
