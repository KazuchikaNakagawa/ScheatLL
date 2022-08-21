#include "ScheatLLPointerType.hpp"
#include "../LLVMConverter/LLVMConverter.hpp"
using namespace scheatll;

llvm::Type *scheatll_poiner_type::LLVMType() {
    return elementType->LLVMType()->getPointerTo();
}

std::string scheatll_poiner_type::typeName() {
    return elementType->typeName() + "*";
}

scheatll_poiner_type::scheatll_poiner_type(scheatll_type* et) : scheatll_type(Pointer)
{
    elementType = et;
}

scheatll_poiner_type::~scheatll_poiner_type()
{
}

