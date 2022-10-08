#if !defined(GLOBALALLOCEXPR_H)
#define GLOBALALLOCEXPR_H

#include "BasicNodes.hpp"
#include "../Attribute/ScLLAttribute.hpp"
#include <string>

namespace scheat
{

class scheat_type;

class GlobalAllocExpr : public Expr
{
private:
    // this type is value's. not its type.
    scheat_type* variableType = nullptr;
    std::string variableName;
    scheat_attribute attribute;
    bool defined = false;
protected:
    llvm::Value *LLVMConvert() override;
public:
    GlobalAllocExpr(std::string, scheat_type*, scheat_attribute, scheat::SourceLocation);

    std::string Decode() override;

    scheat_type* Type() override;

    scheat_attribute getAttribute() override
    {
        return attribute;
    }

    void setType(scheat_type*);

    ~GlobalAllocExpr();
};


} // namespace scheat


#endif // GLOBALALLOCEXPR_H
