#include "ScheatLLPointerType.hpp"
#include "../LLVMConverter/LLVMConverter.hpp"
#include "../ScheatLL/ScheatLL.hpp"
using namespace scheat;

llvm::Type *scheat_poiner_type::LLVMType() {
    return elementType->LLVMType()->getPointerTo();
}

std::string scheat_poiner_type::typeName() {
    return elementType->typeName() + "*";
}

scheat_poiner_type::scheat_poiner_type(scheat_type* et) : scheat_type(Pointer)
{
    elementType = et;
}

scheat_poiner_type::~scheat_poiner_type()
{
}

Term* scheat_poiner_type::SizeOf()
{
    return Constant(8);
}
