#include "ScheatLLExec.hpp"
#include "../Global/Globals.hpp"
#include "../Codes/Codes.hpp"
#include "../LLVMConverter/LLVMConverter.hpp"
#include "../Nodes/Nodes.hpp"
#include "../API/ScheatLL.hpp"
#include <iostream>

using namespace scheatll;

void ScheatLLExec::StartEditing() {
    if (EditingTarget != nullptr)
    {
        std::cout << "Scheat: tried to edit two modules simultaneously." << std::endl;
    }
    
    EditingTarget = this;
}

// modName insertPoint is modName() function's.
ScheatLLExec::ScheatLLExec(std::string modName)
{
    ModuleName = modName;
    firstScope = new DeclareFuncExpr(modName, Type(Void), {}, FunctionAttribute());
    exitScope = new DeclareFuncExpr("exit." + modName, Type(Void), {}, FunctionAttribute());
    globalScope = new Codes("global");
    insertPoint.StartEditing(((DeclareFuncExpr *)firstScope)->body);
}

ScheatLLExec::~ScheatLLExec()
{
}

std::string ScheatLLExec::getModuleName() {
    return ModuleName;
}

void ScheatLLExec::ConvertToLLVMIR() {
    llvm::InitializeAllTargetInfos();
    llvm::InitializeAllTargets();
    llvm::InitializeAllTargetMCs();
    llvm::InitializeAllAsmParsers();
    llvm::InitializeAllAsmPrinters();

    auto cvt = new LLVMConverter(this);
    globalScope->ConvertAll();

    for (auto &&f : globalFunctions)
    {
        std::cerr << f->LLVMEncode() << std::endl;
    }

    // 理論上は、ここに全て集約されているはず？
    firstScope->LLVMEncode();
    exitScope->LLVMEncode();
}

void ScheatLLExec::InsertIR(Expr *ir) {
    ((Codes *)insertPoint)->code(ir);
}

void ScheatLLExec::VerifyGlobalVariables(Expr *var) {
    globalScope->code(var);
}

void ScheatLLExec::LLVMDump()
{
    ScheatllLLVMConverter->Module()->print(llvm::errs(), nullptr);
}

void ScheatLLExec::VerifyGlobalFunc(Expr *f){
    globalFunctions.push_back(f);
}

void ScheatLLExec::Dump() {
    std::cerr << "# ModuleName: " << getModuleName() << std::endl;
    std::cerr << "global{" << std::endl;
    IncreaseIndent();
    globalScope->Dump();
    DecreaseIndent();
    std::cerr << "}" << std::endl << std::endl;
    std::cerr << firstScope->Decode() << std::endl << std::endl;
    std::cerr << exitScope->Decode() << std::endl << std::endl;
    for (auto &&f : globalFunctions)
    {
        std::cerr << getIndent() << f->Decode() << std::endl;
        std::cerr << std::endl;
    }
    
}

std::string ScheatLLExec::getIndent()
{
    std::string res;
    for (size_t i = 0; i < IndentCount; i++)
    {
        res += "    ";
    }
    return res;
}
