#if !defined(SCHEATARGUMENTEXPR_HPP)
#define SCHEATARGUMENTEXPR_HPP

#include "BasicNodes.hpp"
#include "../Type/ScheatLLType.hpp"

namespace scheat
{

class DeclareFuncExpr;

class ArgumentExpr : public Expr
{
private:
    unsigned int index;
    scheat_type* type;
    std::string name;
    DeclareFuncExpr *func;
protected:
    llvm::Value *LLVMConvert() override;
public:
    ArgumentExpr(DeclareFuncExpr *, std::string, scheat_type*, unsigned int);

    // itsumono
    std::string Decode() override { return "@" + name; };

    // itsumono
    scheat_type* Type() override { 
        if (name == "its") return type;
        return type->getPointerTo(); 
    };

    ~ArgumentExpr();
};

} // namespace scheat


#endif // SCHEATARGUMENTEXPR_HPP
