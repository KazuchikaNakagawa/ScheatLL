#include "../WhileExpr.hpp"
#include "../../Codes/Codes.hpp"
#include "../../Exec/ScheatLLExec.hpp"
#include "../../Global/Globals.hpp"
#include "../../ScheatLL/ScheatLL.hpp"
#include "../../LLVMConverter/LLVMConverter.hpp"
#include "../../Type/ScheatLLType.hpp"

using namespace scheat;


WhileExpr::WhileExpr(Expr *c, Codes *bd)
: Expr(c->Location())
{
    Condition = c;
    Body = bd;
}

WhileExpr::~WhileExpr()
{
}

scheat_type* WhileExpr::Type()
{
    return scheat::Type(Void);
}

llvm::Value *WhileExpr::LLVMConvert()
{
    auto parent = ScheatllLLVMConverter->Builder().GetInsertBlock()->getParent();
    auto bbw = llvm::BasicBlock::Create(
        ScheatllLLVMConverter->Context(),
        "while",
        parent
    );
    auto bb = llvm::BasicBlock::Create(
        ScheatllLLVMConverter->Context(),
        "then",
        parent
    );
    auto EndBlock = llvm::BasicBlock::Create(
        ScheatllLLVMConverter->Context(),
        "finally",
        parent
    );
    ScheatllLLVMConverter->Builder().CreateBr(bbw);
    ScheatllLLVMConverter->Builder().SetInsertPoint(bbw);
    ScheatllLLVMConverter->Builder().CreateCondBr(Condition->LLVMEncode(), bb, EndBlock);
    ScheatllLLVMConverter->Builder().SetInsertPoint(bb);
    Body->ConvertAll();
    ScheatllLLVMConverter->Builder().CreateBr(bbw);
    ScheatllLLVMConverter->Builder().SetInsertPoint(EndBlock);
    return nullptr;
}

std::string WhileExpr::Decode()
{
    std::string result = "while ";
    result += Condition->Decode() + " {\n";
    EditingTarget->IncreaseIndent();
    for (auto &&inst : Body->getBuffer())
    {
        result += EditingTarget->getIndent() + inst->Decode() + "\n";
    }
    EditingTarget->DecreaseIndent();
    result += EditingTarget->getIndent() + "}";
    return result;
}
