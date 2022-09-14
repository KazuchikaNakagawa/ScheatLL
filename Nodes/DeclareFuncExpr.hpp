#if !defined(SCHEATDECLAREFUNCEXPR_HPP)
#define SCHEATDECLAREFUNCEXPR_HPP

#include "./BasicNodes.hpp"
#include "../Attribute/ScLLAttribute.hpp"
#include <string>
#include <vector>

namespace scheatll
{

class scheatll_type;
class Codes;

class DeclareFuncExpr : public Expr
{
private:

    // holds return type.
    scheatll_type* functionReturnType = nullptr;

    // holds argument types.
    std::vector<scheatll_type*> functionArgsType;
    std::vector<std::string> functionArgNames;

    // the name of function
    std::string functionName;

    // attribute.
    scheatll_attribute attribute;

    bool defined = false;

protected:
    llvm::Value *LLVMConvert() override;
public:
    DeclareFuncExpr(std::string, scheatll_type*, std::vector<scheatll_type*>, scheatll_attribute, scheat::SourceLocation);
    Codes *body;

    // if the argument vector's size doesn't adjust to the number of arguments,
    // it does nothing.
    void setArgNames(std::vector<std::string>&);

    // changes return type.
    void setReturnType(scheatll_type *);

    std::string Decode() override;
    scheatll_type* Type() override;

    scheatll_attribute getAttribute() override
    {
        return attribute;
    }

    ~DeclareFuncExpr();
};


} // namespace scheatll


#endif // SCHEATDECLAREFUNCEXPR_HPP
