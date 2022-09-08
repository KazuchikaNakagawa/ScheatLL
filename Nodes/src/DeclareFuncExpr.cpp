#include "../DeclareFuncExpr.hpp"
#include "../../Global/Globals.hpp"
#include "../../LLVMConverter/LLVMConverter.hpp"
#include "../../Type/ScheatLLType.hpp"
#include "../../Type/ScLLType.hpp"
#include "../../Codes/Codes.hpp"
#include "../ArgumentExpr.hpp"
#include "../../Error/ScheatLLError.hpp"
#include "../../Exec/ScheatLLExec.hpp"

namespace llvm
{
class Type;
} // namespace llvm


using namespace scheatll;

DeclareFuncExpr::DeclareFuncExpr(
    std::string nm, 
    scheatll_type* rtp, 
    std::vector<scheatll_type*> argtps, 
    scheatll_attribute attr,
    scheat::SourceLocation l)
: attribute(attr), Expr(l)
{
    functionName = nm;
    functionReturnType = rtp;
    functionArgsType = argtps;
    if (attr.is_writable())
    {
        throw scheatll_attribute_error();
    }
    body = new Codes(nm, rtp);
}

DeclareFuncExpr::~DeclareFuncExpr()
{
}

llvm::Value* DeclareFuncExpr::LLVMConvert(){
    if ((!body->hasReturnValue() 
    && functionReturnType != scheatll::Type(Void)))
    {
        throw scheatll_return_error();
    }
    
    std::vector<llvm::Type *> ltps;
    for (auto &&i : functionArgsType)
    {
        ltps.push_back(i->LLVMType());
    }
    llvm::FunctionType *fty = llvm::FunctionType::get(functionReturnType->LLVMType(), ltps, false);
    llvm::Function *F = llvm::Function::Create(fty, llvm::Function::ExternalLinkage, functionName, ScheatllLLVMConverter->Module());
    LLVMVal = F;
    // TODO: enable to use named arguments and Arg->setName
    llvm::BasicBlock *BB = llvm::BasicBlock::Create(
        ScheatllLLVMConverter->Context(), 
        "entry", 
        F);
    ScheatllLLVMConverter->Builder().SetInsertPoint(BB);
    body->ConvertAll();
    if (functionReturnType == scheatll::Type(Void))
        ScheatllLLVMConverter->Builder().CreateRetVoid();
    llvm::verifyFunction(*F);
    return F;
}

std::string DeclareFuncExpr::Decode() {
    if (defined)
    {
        return functionName;
    }
    
    std::string result;
    // ex) int32(int32 argc, int8** argc) main
    result += functionReturnType->typeName() + "(";
    int count = 0;
    for (auto &&tp : functionArgsType)
    {
        result += tp->typeName();
        if (!functionArgNames.empty())
        {
            result += " " + functionArgNames[count];
        }
        
        count++;
        if (functionArgsType.size() != count)
        {
            result += ", ";
        }
    }
    result += ") " + functionName + " --" + attribute.to_string() + " {\n";
    EditingTarget->IncreaseIndent();
    for (auto &&expr : body->getBuffer())
    {
        result += EditingTarget->getIndent() + expr->Decode() + "\n";
    }
    EditingTarget->DecreaseIndent();
    result += "}";
    defined = true;
    return result;
}

void DeclareFuncExpr::setArgNames(std::vector<std::string>& nms)
{
    if (nms.size() != functionArgsType.size())
    {
        return;
    }

    // first, before setting new names, delete previous names.
    for (auto &&oldnames : functionArgNames)
    {
        body->localVariables.erase(oldnames);
    }
    
    functionArgNames = nms;
    int index = 0;
    for (auto &&str : functionArgNames)
    {
        body->localVariables[str] = new ArgumentExpr(
            this, 
            str, 
            functionArgsType[index], 
            index);
    }
    
}

scheatll_type* DeclareFuncExpr::Type() {
    return scheatll::FuncType(functionReturnType, functionArgsType);
}

void DeclareFuncExpr::setReturnType(scheatll_type *tp){
    functionReturnType = tp;
}
