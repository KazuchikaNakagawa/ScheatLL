#include "ScheatLLType.hpp"
#include "../LLVMConverter/LLVMConverter.hpp"
#include "../Global/Globals.hpp"
#include "ScheatLLPointerType.hpp"

using namespace scheatll;

scheatll_type* scheatll_type::int_type = new scheatll_type(Int32);
scheatll_type* scheatll_type::int8_type = new scheatll_type(Int8);
scheatll_type* scheatll_type::int64_type = new scheatll_type(Int64);
scheatll_type* scheatll_type::int1_type = new scheatll_type(Int1);
scheatll_type* scheatll_type::float_type = new scheatll_type(Double);
scheatll_type* scheatll_type::void_type = new scheatll_type(Void);

llvm::Type* scheatll_type::LLVMType() {
    switch (this->defType)
    {
    case Int32:
        return ScheatllLLVMConverter->Builder().getInt32Ty();
    case Int8:
        return ScheatllLLVMConverter->Builder().getInt8Ty();
    case Int64:
        return ScheatllLLVMConverter->Builder().getInt64Ty();
    case Int1:
        return ScheatllLLVMConverter->Builder().getInt1Ty();
    case Double:
        return ScheatllLLVMConverter->Builder().getDoubleTy();
    case Void:
        return ScheatllLLVMConverter->Builder().getVoidTy();
    default:
        // this means structures/classes did not have a correct LLVMType() function.
        break;
    }
    return nullptr;
}

std::string scheatll_type::typeName() {
    switch (this->defType)
    {
    case Int32:
        return "int32";
    case Int8:
        return "int8";
    case Int64:
        return "int64";
    case Int1:
        return "int1";
    case Double:
        return "double";
    case Void:
        return "void";
    default:
        // this means structures/classes did not have a correct typeName() function.
        return "";
    }
}

scheatll_type* scheatll_type::getPointerTo() {
    if (this->pointerOfSelf == nullptr)
    {
        pointerOfSelf = new scheatll_poiner_type(this);
    }
    return pointerOfSelf;
}


// do not use about structures, classes, and pointer types.
scheatll_type::scheatll_type(DefaultType dt)
{
    defType = dt;
}

scheatll_type::~scheatll_type()
{
}
