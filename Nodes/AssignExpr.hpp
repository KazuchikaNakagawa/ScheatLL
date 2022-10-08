#if !defined(SCHEATASSIGNEXPR_HPP)
#define SCHEATASSIGNEXPR_HPP

#include "BasicNodes.hpp"

namespace scheat
{

class AssignExpr : public Expr
{
private:
    Expr *pointer;
    Expr *value;
protected:
    llvm::Value *LLVMConvert() override;
public:
    AssignExpr(Expr *, Expr *, scheat::SourceLocation);
    std::string Decode() override;
    scheat_type* Type() override;
    ~AssignExpr();
};

} // namespace scheat


#endif // SCHEATASSIGNEXPR_HPP
