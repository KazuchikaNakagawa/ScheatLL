#include "../ExternalFuncExpr.hpp"
#include "../../Type/ScheatFuncType.hpp"
#include "../../Type/ScLLType.hpp"
#include "../../Global/Globals.hpp"
#include "../../LLVMConverter/LLVMConverter.hpp"
using namespace scheatll;

ExternalFuncExpr::ExternalFuncExpr(scheatll_type* tp, std::string nm, std::vector<scheatll_type*> args, scheat::SourceLocation l)
: Expr(l), Return_Type(tp), Name(nm), ArgTypes(args)
{
}

ExternalFuncExpr::~ExternalFuncExpr()
{
}

scheatll_type* ExternalFuncExpr::Type()
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
    llvm::FunctionType *fty = llvm::FunctionType::get(Return_Type->LLVMType(), ltps, false);
    llvm::Function *F = llvm::Function::Create(fty, llvm::Function::ExternalLinkage, Name, ScheatllLLVMConverter->Module());
    return F;
}
