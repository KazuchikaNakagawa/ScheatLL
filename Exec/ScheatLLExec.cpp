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

void ScheatLLExec::ExportObjectFile()
{
    llvm::InitializeAllTargetInfos();
    llvm::InitializeAllTargets();
    llvm::InitializeAllTargetMCs();
    llvm::InitializeAllAsmParsers();
    llvm::InitializeAllAsmPrinters();
    
    auto TargetTriple = llvm::sys::getDefaultTargetTriple();
    ScheatllLLVMConverter->Module()->setTargetTriple(TargetTriple);

    std::string Error;
    auto Target = llvm::TargetRegistry::lookupTarget(TargetTriple, Error);
    if (!Target)
    {
        exit(9);
        return;
    }
    
    auto CPU = "generic";
    auto Features = "";

    llvm::TargetOptions opt;
    auto RM = llvm::Optional<llvm::Reloc::Model>();
    auto TheTargetMachine =
    Target->createTargetMachine(TargetTriple, CPU, Features, opt, RM);

    ScheatllLLVMConverter->Module()->setDataLayout(TheTargetMachine->createDataLayout());

    auto Filename = this->ModuleName + ".o";
    std::error_code EC;
    llvm::raw_fd_ostream dest(Filename, EC, llvm::sys::fs::OF_None);

    if (EC) {
        llvm::errs() << "Could not open file: " << EC.message();
        exit(9);
    }

    llvm::legacy::PassManager pass;
    auto FileType = llvm::CGFT_ObjectFile;

    if (TheTargetMachine->addPassesToEmitFile(pass, dest, nullptr, FileType)) {
        llvm::errs() << "TheTargetMachine can't emit a file of this type";
        exit(9);
    }

    pass.run(*ScheatllLLVMConverter->Module());
    dest.flush();
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
