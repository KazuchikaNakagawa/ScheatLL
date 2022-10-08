#include "../ExternalFuncExpr.hpp"
#include "../../Type/ScheatFuncType.hpp"
#include "../../Type/ScLLType.hpp"
#include "../../Global/Globals.hpp"
#include "../../LLVMConverter/LLVMConverter.hpp"
using namespace scheat;

ExternalFuncExpr::ExternalFuncExpr(scheat_type* tp, std::string nm, std::vector<scheat_type*> args, bool va, scheat::SourceLocation l)
: Expr(l), Return_Type(tp), Name(nm), ArgTypes(args), isVarArg(va)
{
}

ExternalFuncExpr::~ExternalFuncExpr()
{
}

scheat_type* ExternalFuncExpr::Type()
{
    return FuncType(Return_Type, ArgTypes);
}

std::string ExternalFuncExpr::Decode()
{
    std::string result;
    // ex) int32(int32 argc, int8** argc) main
    result += Return_Type->typeName() + "(";
    int count = 0;
    for (auto &&tp : ArgTypes)
    {
        result += tp->typeName();
        
        count++;
        if (ArgTypes.size() != count)
        {
            result += ", ";
        }
    }
    result += ") " + Name;
    return result;
}

llvm::Value *ExternalFuncExpr::LLVMConvert()
{
    std::vector<llvm::Type *> ltps;
    for (auto &&i : ArgTypes)
    {
        ltps.push_back(i->LLVMType());
    }
    llvm::FunctionType *fty = llvm::FunctionType::get(Return_Type->LLVMType(), ltps, isVarArg);
    llvm::Function *F = llvm::Function::Create(fty, llvm::Function::ExternalLinkage, Name, ScheatllLLVMConverter->Module());
    return F;
}
