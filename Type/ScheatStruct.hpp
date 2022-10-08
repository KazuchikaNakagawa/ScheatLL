#if !defined(SCHEATSTRUCT_HPP)
#define SCHEATSTRUCT_HPP

#include "ScheatLLType.hpp"
#include "MemberImpl.hpp"
#include "../SourceLocation/SourceLocation.h"

namespace llvm {
    class StructType;
};

namespace scheat
{

class DeclareFuncExpr;
class Expr;

class Struct : public scheat_type, public MemberImpl
{
protected:
    scheat::SourceLocation location;
    DeclareFuncExpr *Initializer = nullptr;
    DeclareFuncExpr *Deinitializer = nullptr; 
    llvm::StructType *_LLVMType = nullptr;
public:
    std::string StructName; 
    // gives parent initializer StructType
    // it does lots of things
    // defines initializer and deinitializer
    Struct(std::string, scheat::SourceLocation);
    DeclareFuncExpr *getInitializer() override;
    DeclareFuncExpr *getDeinitializer() override;
    std::string typeName() override{ return StructName; };
    Term* Access(Expr *, std::string, scheat::SourceLocation) override;
    Term* Access(Expr *, std::string, std::vector<scheat_type*>, scheat::SourceLocation) override;
    void AddMember(std::string, scheat_type*, AccessAttribute) override;
    llvm::Type* LLVMType() override;
    ~Struct();
};

} // namespace scheat


#endif // SCHEATSTRUCT_HPP
