#if !defined(SCHEATLLTYPE_HPP)
#define SCHEATLLTYPE_HPP

#include "ScLLDefaultTypes.hpp"
#include "OperatorImpl.hpp"
#include "../SourceLocation/SourceLocation.h"
#include "../Error/ScheatLLError.hpp"
#include <string>
#include <map>

namespace llvm
{
class Type;
} // namespace llvm

namespace scheat
{

class Term;
class Expr;
class DeclareFuncExpr;

class scheat_type : public OperatorImpl
{
protected:
    DefaultType defType;
    scheat_type* pointerOfSelf = nullptr;
public:
    scheat_type(DefaultType);

    static scheat_type* int_type;
    static scheat_type* int8_type;
    static scheat_type* int64_type;
    static scheat_type* int1_type;
    static scheat_type* float_type;
    static scheat_type* void_type;

    // defaultType do not have a manager
    bool isInManaged() { return defType == StructType || defType == NotDefaultType; };

    // !!
    // before using this function, need to call Exec->ConvertToLLVM
    virtual llvm::Type *LLVMType();

    virtual std::string typeName();

    virtual Term* SizeOf();

    virtual Term* DefaultValue();

    scheat_type* getPointerTo();

    // TODO: define a new error.
    virtual scheat_type* getElementType() { return nullptr; };

    bool isPointerType() { return defType == Pointer; };

    bool isFunctionType() { return defType == FunctionType; };

    virtual scheat_type* getReturnType() { throw std::runtime_error("type has no return type"); return nullptr; };

    std::map<std::string, scheat_type*> funcTypeTable; 

    virtual Term* Access(Expr*, std::string, scheat::SourceLocation);
    virtual Term* Access(Expr*, std::string, std::vector<scheat_type*>, scheat::SourceLocation);

    virtual DeclareFuncExpr *getInitializer() {
        throw scheat_unavailable_feature_error();
        return nullptr;
    };
    virtual DeclareFuncExpr *getDeinitializer()
    {
        throw scheat_unavailable_feature_error();
        return nullptr;
    };

    ~scheat_type();
};


} // namespace scheat


#endif // SCHEATLLTYPE_HPP
