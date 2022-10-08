#include "../ArgumentExpr.hpp"
#include "../DeclareFuncExpr.hpp"
#include "../../Global/Globals.hpp"
#include "../../LLVMConverter/LLVMConverter.hpp"
#include "../../Type/ScheatLLType.hpp"
using namespace scheat;


ArgumentExpr::ArgumentExpr(DeclareFuncExpr *f,std::string nm, scheat_type* tp, unsigned int idx)
: Expr(f->Location())
{
    name = nm;
    type = tp;
    index = idx;
    func = f;
}

ArgumentExpr::~ArgumentExpr()
{
}

llvm::Value *ArgumentExpr::LLVMConvert()
{
    auto lf = func->LLVMEncode();
    auto llvmfunc = (llvm::Function *)lf;
    int i = 0;
    for (auto &&arg : llvmfunc->args())
    {
        if (i == index)
        {
            auto arg_val = &arg;
            if (name == "its")
            {
                return arg_val;
            }
            
            auto arg_ref = ScheatllLLVMConverter->Builder().CreateAlloca(type->LLVMType());
            ScheatllLLVMConverter->Builder().CreateStore(arg_val, arg_ref);
            return arg_ref;
        }

        i++;
    }
    return nullptr;
}
