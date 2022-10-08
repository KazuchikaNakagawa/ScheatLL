#if !defined(SCHEATDECLAREFUNCEXPR_HPP)
#define SCHEATDECLAREFUNCEXPR_HPP

#include "./BasicNodes.hpp"
#include "../Attribute/ScLLAttribute.hpp"
#include <string>
#include <vector>

namespace scheat
{

class scheat_type;
class Codes;

class DeclareFuncExpr : public Expr
{
private:

    // holds return type.
    scheat_type* functionReturnType = nullptr;

    // holds argument types.
    std::vector<scheat_type*> functionArgsType;
    std::vector<std::string> functionArgNames;

    // the name of function
    std::string functionName;

    // attribute.
    scheat_attribute attribute;

    bool defined = false;

protected:
    llvm::Value *LLVMConvert() override;
public:
    DeclareFuncExpr(std::string, scheat_type*, std::vector<scheat_type*>, scheat_attribute, scheat::SourceLocation);
    Codes *body;

    // if the argument vector's size doesn't adjust to the number of arguments,
    // it does nothing.
    void setArgNames(std::vector<std::string>&);

    // changes return type.
    void setReturnType(scheat_type *);

    std::string Decode() override;
    scheat_type* Type() override;

    scheat_attribute getAttribute() override
    {
        return attribute;
    }

    ~DeclareFuncExpr();
};


} // namespace scheat


#endif // SCHEATDECLAREFUNCEXPR_HPP
