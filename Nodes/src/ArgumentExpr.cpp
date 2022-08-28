#include "../ArgumentExpr.hpp"
#include "../DeclareFuncExpr.hpp"
#include "../../LLVMConverter/LLVMConverter.hpp"
using namespace scheatll;


ArgumentExpr::ArgumentExpr(DeclareFuncExpr *f,std::string nm, scheatll_type* tp, unsigned int idx)
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
            return &arg;
        }

        i++;
    }
    return nullptr;
}
