#if !defined(SCHEATLOCALALLOCEXPR_HPP)
#define SCHEATLOCALALLOCEXPR_HPP

#include "BasicNodes.hpp"
#include "../Attribute/ScLLAttribute.hpp"
#include "../SourceLocation/SourceLocation.h"
#include <string>

namespace scheatll
{

class scheatll_type;

class LocalAllocExpr : public Expr
{
private:
    // variable type(element). not a itself type
    scheatll_type* variableType;
    std::string variableName;
    scheatll_attribute attribute;
    bool defined = false;
protected:
    llvm::Value *LLVMConvert() override;
public:
    LocalAllocExpr(std::string, scheatll_type*, scheatll_attribute, scheat::SourceLocation);

    std::string Decode() override;

    scheatll_type* Type() override;

    scheatll_attribute getAttribute() override
    {
        return attribute;
    }

    void setType(scheatll_type *);

    ~LocalAllocExpr();
};

} // namespace scheatll


#endif // SCHEATLOCALALLOCEXPR_HPP
