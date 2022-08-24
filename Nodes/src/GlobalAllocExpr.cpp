#include "../GlobalAllocExpr.hpp"
#include "../../Global/Globals.hpp"
#include "../../LLVMConverter/LLVMConverter.hpp"
#include "../../Type/ScheatLLType.hpp"

using namespace scheatll;

llvm::Value *GlobalAllocExpr::LLVMConvert(){
    auto ltype = variableType->LLVMType();
    return new llvm::GlobalVariable(
        *ScheatllLLVMConverter->Module(),
        ltype,
        false, 
        llvm::GlobalValue::ExternalLinkage,
        nullptr, 
        variableName
    );
}

std::string GlobalAllocExpr::Decode() {
    if (!defined) {
        defined = true; 
        return variableType->typeName() + " " + variableName + " --" + attribute.to_string();
    }else{
        return variableName;
    }
}

scheatll_type* GlobalAllocExpr::Type() {
    if (variableType == nullptr)
    {
        return nullptr;
    }
    
    return variableType->getPointerTo();
}

GlobalAllocExpr::GlobalAllocExpr(std::string s, scheatll_type* t, scheatll_attribute att) 
: attribute(att)
{
    variableName = s;
    variableType = t;
}

GlobalAllocExpr::~GlobalAllocExpr()
{
}

void GlobalAllocExpr::setType(scheatll_type *tp)
{
    variableType = tp;
}
