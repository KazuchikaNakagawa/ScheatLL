#include "../LocalAllocExpr.hpp"
#include "../../Global/Globals.hpp"
#include "../../LLVMConverter/LLVMConverter.hpp"
#include "../../Exec/ScheatLLExec.hpp"
#include "../../Type/ScheatLLType.hpp"
#include "../../ScheatLL/ScheatLL.hpp"
#include "../Nodes.hpp"
using namespace scheat;

llvm::Value* LocalAllocExpr::LLVMConvert(){
    auto ltype = variableType->LLVMType();
    return ScheatllLLVMConverter->Builder().CreateAlloca(ltype, nullptr, variableName);
}

LocalAllocExpr::LocalAllocExpr(std::string nm, scheat_type* tp, scheat_attribute attr, scheat::SourceLocation l)
: attribute(attr), Expr(l)
{
    variableName = nm;
    if (tp != nullptr) setType(tp);
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

scheat_type* LocalAllocExpr::Type()
{
    if (variableType == nullptr)
    {
        return nullptr;
    }
    
    return variableType->getPointerTo();
}

void LocalAllocExpr::setType(scheat_type *tp)
{
    variableType = tp;
    if (tp->isInManaged())
    {
        CallVoid(tp->getInitializer(), {this});
    }
}
