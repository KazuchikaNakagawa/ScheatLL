#if !defined(GLOBALALLOCEXPR_H)
#define GLOBALALLOCEXPR_H

#include "BasicNodes.hpp"
#include "../Attribute/ScLLAttribute.hpp"
#include <string>

namespace scheatll
{

class scheatll_type;

class GlobalAllocExpr : public Expr
{
private:
    // this type is value's. not its type.
    scheatll_type* variableType;
    std::string variableName;
    scheatll_attribute attribute;
    bool defined = false;
protected:
    llvm::Value *LLVMConvert() override;
public:
    GlobalAllocExpr(std::string, scheatll_type*, scheatll_attribute, scheat::SourceLocation);

    std::string Decode() override;

    scheatll_type* Type() override;

    scheatll_attribute getAttribute() override
    {
        return attribute;
    }

    void setType(scheatll_type*);

    ~GlobalAllocExpr();
};


} // namespace scheatll


#endif // GLOBALALLOCEXPR_H
