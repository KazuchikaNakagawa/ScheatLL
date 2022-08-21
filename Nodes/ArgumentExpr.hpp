#if !defined(SCHEATARGUMENTEXPR_HPP)
#define SCHEATARGUMENTEXPR_HPP

#include "BasicNodes.hpp"

namespace scheatll
{

class DeclareFuncExpr;

class ArgumentExpr : public Expr
{
private:
    unsigned int index;
    scheatll_type* type;
    std::string name;
    DeclareFuncExpr *func;
protected:
    llvm::Value *LLVMConvert() override;
public:
    ArgumentExpr(DeclareFuncExpr *, std::string, scheatll_type*, unsigned int);

    // itsumono
    std::string Decode() override { return "@" + name; };

    // itsumono
    scheatll_type* Type() override { return type; };

    ~ArgumentExpr();
};

} // namespace scheatll


#endif // SCHEATARGUMENTEXPR_HPP
