#include "../GlobalAllocExpr.hpp"
#include "../../Global/Globals.hpp"
#include "../../LLVMConverter/LLVMConverter.hpp"
#include "../../Type/ScheatLLType.hpp"
#include "../../API/ScheatLL.hpp"

using namespace scheatll;

llvm::Value *GlobalAllocExpr::LLVMConvert(){
    auto ltype = variableType->LLVMType();
    llvm::Constant *defaultVal = nullptr;
    if (variableType == scheatll::Type(Int32))
    {
        defaultVal = ScheatllLLVMConverter->Builder().getInt32(0);
    }else if (variableType == scheatll::Type(Double))
    {
        defaultVal = llvm::ConstantFP::get(ScheatllLLVMConverter->Builder().getDoubleTy(), 0.0);
    }else{
        defaultVal = llvm::ConstantAggregateZero::get(ltype);
    }
    
    return new llvm::GlobalVariable(
        *ScheatllLLVMConverter->Module(),
        ltype,
        false, 
        llvm::GlobalValue::ExternalLinkage,
        defaultVal, 
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

GlobalAllocExpr::GlobalAllocExpr(std::string s, scheatll_type* t, scheatll_attribute att, scheat::SourceLocation l) 
: attribute(att), Expr(l)
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
