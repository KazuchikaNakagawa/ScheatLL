#if !defined(SCHEATLOCALALLOCEXPR_HPP)
#define SCHEATLOCALALLOCEXPR_HPP

#include "BasicNodes.hpp"
#include "../Attribute/ScLLAttribute.hpp"
#include "../SourceLocation/SourceLocation.h"
#include <string>

namespace scheat
{

class scheat_type;

class LocalAllocExpr : public Expr
{
private:
    // variable type(element). not a itself type
    scheat_type* variableType;
    std::string variableName;
    scheat_attribute attribute;
    bool defined = false;
protected:
    llvm::Value *LLVMConvert() override;
public:
    LocalAllocExpr(std::string, scheat_type*, scheat_attribute, scheat::SourceLocation);

    std::string Decode() override;

    scheat_type* Type() override;

    scheat_attribute getAttribute() override
    {
        return attribute;
    }

    void setType(scheat_type *);

    ~LocalAllocExpr();
};

} // namespace scheat


#endif // SCHEATLOCALALLOCEXPR_HPP
