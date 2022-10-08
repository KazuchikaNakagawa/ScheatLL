#if !defined(SCHEATEXTERNALFUNCEXPR_HPP)
#define SCHEATEXTERNALFUNCEXPR_HPP

#include "BasicNodes.hpp"
#include <vector>

namespace scheat
{

class ExternalFuncExpr : public Expr
{
private:
    scheat_type* Return_Type;
    std::string Name;
    std::vector<scheat_type*> ArgTypes;
    bool isVarArg;
protected:
    llvm::Value *LLVMConvert() override;
public:
    ExternalFuncExpr(scheat_type*, std::string, std::vector<scheat_type*>, bool, scheat::SourceLocation);
    scheat_type* Type() override;
    std::string Decode() override;
    ~ExternalFuncExpr();
};

} // namespace scheat


#endif // SCHEATEXTERNALFUNCEXPR_HPP
