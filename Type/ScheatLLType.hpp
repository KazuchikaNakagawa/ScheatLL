#if !defined(SCHEATLLTYPE_HPP)
#define SCHEATLLTYPE_HPP

#include "ScLLDefaultTypes.hpp"
#include <string>
#include <map>

namespace llvm
{
class Type;
} // namespace llvm

namespace scheatll
{

class scheatll_type
{
protected:
    DefaultType defType;
    scheatll_type* pointerOfSelf = nullptr;
public:
    scheatll_type(DefaultType);

    static scheatll_type* int_type;
    static scheatll_type* int8_type;
    static scheatll_type* int64_type;
    static scheatll_type* int1_type;
    static scheatll_type* float_type;
    static scheatll_type* void_type;

    // defaultType do not have a manager
    bool isInManaged() { return defType == NotDefaultType; };

    // !!
    // before using this function, need to call Exec->ConvertToLLVM
    virtual llvm::Type *LLVMType();

    virtual std::string typeName();

    scheatll_type* getPointerTo();

    // TODO: define a new error.
    virtual scheatll_type* getElementType() { return nullptr; };

    bool isPointerType() { return defType == Pointer; };

    std::map<std::string, scheatll_type*> funcTypeTable; 

    ~scheatll_type();
};


} // namespace scheatll


#endif // SCHEATLLTYPE_HPP
