#include "ScheatLLType.hpp"
#include "../LLVMConverter/LLVMConverter.hpp"
#include "../Global/Globals.hpp"
#include "ScheatLLPointerType.hpp"
#include "../ScheatLL/ScheatLL.hpp"
#include "../Error/ScheatLLError.hpp"

using namespace scheat;

scheat_type* scheat_type::int_type = new scheat_type(Int32);
scheat_type* scheat_type::int8_type = new scheat_type(Int8);
scheat_type* scheat_type::int64_type = new scheat_type(Int64);
scheat_type* scheat_type::int1_type = new scheat_type(Int1);
scheat_type* scheat_type::float_type = new scheat_type(Double);
scheat_type* scheat_type::void_type = new scheat_type(Void);

llvm::Type* scheat_type::LLVMType() {
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

std::string scheat_type::typeName() {
    switch (this->defType)
    {
    case Int32:
        return "Int";
    case Int8:
        return "Char";
    case Int64:
        return "Int64";
    case Int1:
        return "Bool";
    case Double:
        return "Float";
    case Void:
        return "Void";
    default:
        // this means structures/classes did not have a correct typeName() function.
        return "";
    }
}

Term* scheat_type::SizeOf()
{
    switch (this->defType)
    {
    case Int32:
        return Constant(4);
        break;
    case Int8:
        return Constant(1);
    case Int64:
        return Constant(8);
    case Int1:
        return Constant(1);
    case Double:
        return Constant(8);
    default:
        return Constant(8);
    }
    return Constant(8);
}

scheat_type* scheat_type::getPointerTo() {
    if (this->pointerOfSelf == nullptr)
    {
        pointerOfSelf = new scheat_poiner_type(this);
    }
    return pointerOfSelf;
}


// do not use about structures, classes, and pointer types.
scheat_type::scheat_type(DefaultType dt)
{
    defType = dt;
}

scheat_type::~scheat_type()
{
}

Term* scheat_type::Access(Expr *lhs, std::string rhs, scheat::SourceLocation)
{
    throw scheat_unavailable_feature_error();
}

static std::string to_string(std::vector<scheat_type*>& list)
{
    std::string result = "";
    for (auto &&tp : list)
    {
        result += tp->typeName() + ", ";
    }
    if (!list.empty())
    {
        result.pop_back(); result.pop_back();
    }
    return result;
}

Term* scheat_type::Access(
    Expr *lhs, std::string rhs, std::vector<scheat_type*> rhsSub, scheat::SourceLocation
)
{
    std::string name = typeName() + rhs + " from(" + to_string(rhsSub) + ")";
    return ID(name); 
}

Term* scheat_type::DefaultValue()
{
    switch (defType)
    {
    case Int32:
        return Constant(0);
        break;
    case Int1:
        return Constant(false);
    case Int8:
        return Constant(0);
    case Double:
        return Constant(0.0);
    case Pointer:
        return Nil(this);
    default:
        throw scheat_value_error();
        break;
    }
}
