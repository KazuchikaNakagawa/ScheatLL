
#include "../CallExpr.hpp"
#include "../Nodes.hpp"
#include "../../Type/ScheatLLType.hpp"
#include "../../Type/ScLLType.hpp"
#include "../../Global/Globals.hpp"
#include "../../LLVMConverter/LLVMConverter.hpp"

using namespace scheat;


CallExpr::CallExpr(Expr *func, std::vector<Expr *> args, scheat::SourceLocation l)
: Term(l), Function(func), Args(args)
{
}

CallExpr::~CallExpr()
{
}

std::string CallExpr::Decode()
{
    std::string result = Function->Decode() + "(";

    for (auto &&arg : Args)
    {
        result += arg->Decode() + ", ";
    }

    if (!Args.empty())
    {
        result.pop_back();
        result.pop_back();
    }
    
    result += ")";
    return result;
}

scheat_type* CallExpr::Type()
{
    return Function->Type()->getReturnType();
}

llvm::Value *CallExpr::LLVMConvert()
{
    auto ref = Function->LLVMEncode();
    std::vector<llvm::Value *> args;
    for (auto &&arg : Args)
    {
        args.push_back(arg->LLVMEncode());
    }

    return ScheatllLLVMConverter->Builder().CreateCall((llvm::FunctionType *)Function->Type()->LLVMType(), ref, args);
    
}
