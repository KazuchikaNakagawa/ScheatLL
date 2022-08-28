#include "../IfExprs.hpp"
#include "../../Codes/Codes.hpp"
#include "../../Exec/ScheatLLExec.hpp"
#include "../../Global/Globals.hpp"
#include "../../API/ScheatLL.hpp"
#include "../../LLVMConverter/LLVMConverter.hpp"
#include "../../Type/ScheatLLType.hpp"

using namespace scheatll;

IfExpr::IfExpr(Expr *c, Codes *t)
: Expr(c->Location())
{
    Condition = c;
    Then = t;
}

IfExpr::~IfExpr()
{
}

std::string IfExpr::Decode() 
{
    std::string result = "if ";
    result += Condition->Decode() + " {\n";
    EditingTarget->IncreaseIndent();
    for (auto &&inst : Then->getBuffer())
    {
        result += EditingTarget->getIndent() + inst->Decode() + "\n";
    }
    EditingTarget->DecreaseIndent();
    result += EditingTarget->getIndent() + "}";
    return result;
}

scheatll_type *IfExpr::Type()
{
    return scheatll::Type(Void);
}

llvm::Value *IfExpr::LLVMConvert() 
{
    auto parent = ScheatllLLVMConverter->Builder().GetInsertBlock()->getParent();
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
    ScheatllLLVMConverter->Builder().CreateCondBr(Condition->LLVMEncode(), bb, EndBlock);
    ScheatllLLVMConverter->Builder().SetInsertPoint(bb);
    Then->ConvertAll();
    ScheatllLLVMConverter->Builder().CreateBr(EndBlock);
    ScheatllLLVMConverter->Builder().SetInsertPoint(EndBlock);
    return nullptr;
}

IfElseExpr::IfElseExpr(Expr *c, Codes *t, Codes *e)
: Expr(c->Location())
{
    Condition = c;
    Then = t;
    Else = e;
}

IfElseExpr::~IfElseExpr()
{
}

scheatll_type *IfElseExpr::Type()
{
    return scheatll::Type(Void);
}

llvm::Value *IfElseExpr::LLVMConvert() 
{
    auto parent = ScheatllLLVMConverter->Builder().GetInsertBlock()->getParent();
    auto bbt = llvm::BasicBlock::Create(
        ScheatllLLVMConverter->Context(),
        "then",
        parent
    );

    auto bbe = llvm::BasicBlock::Create(
        ScheatllLLVMConverter->Context(),
        "else",
        parent
    );

    auto EndBlock = llvm::BasicBlock::Create(
        ScheatllLLVMConverter->Context(),
        "finally",
        parent
    );
    ScheatllLLVMConverter->Builder().CreateCondBr(Condition->LLVMEncode(), bbt, bbe);
    ScheatllLLVMConverter->Builder().SetInsertPoint(bbt);
    Then->ConvertAll();
    ScheatllLLVMConverter->Builder().CreateBr(EndBlock);
    ScheatllLLVMConverter->Builder().SetInsertPoint(bbe);
    Else->ConvertAll();
    ScheatllLLVMConverter->Builder().CreateBr(EndBlock);
    ScheatllLLVMConverter->Builder().SetInsertPoint(EndBlock);
    return nullptr;
}

std::string IfElseExpr::Decode() 
{
    std::string result = "if ";
    result += Condition->Decode() + " {\n";
    EditingTarget->IncreaseIndent();
    for (auto &&inst : Then->getBuffer())
    {
        result += EditingTarget->getIndent() + inst->Decode() + "\n";
    }
    EditingTarget->DecreaseIndent();
    result += EditingTarget->getIndent() + "}else{\n";
    EditingTarget->IncreaseIndent();
    for (auto &&inst : Else->getBuffer())
    {
        result += EditingTarget->getIndent() + inst->Decode() + "\n";
    }
    EditingTarget->DecreaseIndent();
    result += EditingTarget->getIndent() + "}";
    return result;
}
