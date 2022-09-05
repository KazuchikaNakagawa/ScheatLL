#if !defined(SCHEATEXTERNALFUNCEXPR_HPP)
#define SCHEATEXTERNALFUNCEXPR_HPP

#include "BasicNodes.hpp"
#include <vector>

namespace scheatll
{

class ExternalFuncExpr : public Expr
{
private:
    scheatll_type* Return_Type;
    std::string Name;
    std::vector<scheatll_type*> ArgTypes;
    bool isVarArg;
protected:
    llvm::Value *LLVMConvert() override;
public:
    ExternalFuncExpr(scheatll_type*, std::string, std::vector<scheatll_type*>, bool, scheat::SourceLocation);
    scheatll_type* Type() override;
    std::string Decode() override;
    ~ExternalFuncExpr();
};

} // namespace scheatll


#endif // SCHEATEXTERNALFUNCEXPR_HPP
