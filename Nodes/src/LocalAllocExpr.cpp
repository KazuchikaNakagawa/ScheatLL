#include "../LocalAllocExpr.hpp"
#include "../../Global/Globals.hpp"
#include "../../LLVMConverter/LLVMConverter.hpp"
#include "../../Type/ScheatLLType.hpp"
using namespace scheatll;

llvm::Value* LocalAllocExpr::LLVMConvert(){
    auto ltype = variableType->LLVMType();
    return ScheatllLLVMConverter->Builder().CreateAlloca(ltype, nullptr, variableName);
}

LocalAllocExpr::LocalAllocExpr(std::string nm, scheatll_type* tp, scheatll_attribute attr)
: attribute(attr)
{
    variableName = nm;
    variableType = tp;
}

LocalAllocExpr::~LocalAllocExpr()
{
}

std::string LocalAllocExpr::Decode() {
    if (!defined) {
        defined = true; 
        return variableType->typeName() + " " + variableName + " --" + attribute.to_string();
    }else{
        return variableName;
    }
}

scheatll_type* LocalAllocExpr::Type()
{
    return variableType->getPointerTo();
}
