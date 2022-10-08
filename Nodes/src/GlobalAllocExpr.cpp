#include "../GlobalAllocExpr.hpp"
#include "../../Global/Globals.hpp"
#include "../../LLVMConverter/LLVMConverter.hpp"
#include "../../Type/ScheatLLType.hpp"
#include "../../ScheatLL/ScheatLL.hpp"
#include "../Nodes.hpp"

using namespace scheat;

llvm::Value *GlobalAllocExpr::LLVMConvert(){
    auto ltype = variableType->LLVMType();
    llvm::Constant *defaultVal = nullptr;
    if (variableType == scheat::Type(Int32))
    {
        defaultVal = ScheatllLLVMConverter->Builder().getInt32(0);
    }else if (variableType == scheat::Type(Double))
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

scheat_type* GlobalAllocExpr::Type() {
    if (variableType == nullptr)
    {
        return nullptr;
    }
    
    return variableType->getPointerTo();
}

GlobalAllocExpr::GlobalAllocExpr(std::string s, scheat_type* t, scheat_attribute att, scheat::SourceLocation l) 
: attribute(att), Expr(l)
{
    variableName = s;
    if (t != nullptr) setType(t);
}

GlobalAllocExpr::~GlobalAllocExpr()
{
}

void GlobalAllocExpr::setType(scheat_type *tp)
{
    variableType = tp;
    if (tp->isInManaged())
    {
        EditingTarget->InsertIRToStart();
        CallVoid(tp->getInitializer(), {this});
        EditingTarget->insertPoint.PauseEditing();

        EditingTarget->InsertIRToExit();
        CallVoid(tp->getDeinitializer(), {this});
        EditingTarget->insertPoint.PauseEditing();
    }
}
