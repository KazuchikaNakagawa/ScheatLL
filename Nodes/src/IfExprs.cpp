#include "../IfExprs.hpp"
#include "../../Codes/Codes.hpp"
#include "../../Exec/ScheatLLExec.hpp"
#include "../../Global/Globals.hpp"
#include "../../ScheatLL/ScheatLL.hpp"
#include "../../LLVMConverter/LLVMConverter.hpp"
#include "../../Type/ScheatLLType.hpp"

using namespace scheat;

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

scheat_type *IfExpr::Type()
{
    return scheat::Type(Void);
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
        "finally"//,
        //parent
    );
    ScheatllLLVMConverter->Builder().CreateCondBr(Condition->LLVMEncode(), bb, EndBlock);
    ScheatllLLVMConverter->Builder().SetInsertPoint(bb);
    Then->ConvertAll();
    parent->getBasicBlockList().push_back(EndBlock);
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

scheat_type *IfElseExpr::Type()
{
    return scheat::Type(Void);
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
        "finally"//,
        //parent
    );
    ScheatllLLVMConverter->Builder().CreateCondBr(Condition->LLVMEncode(), bbt, bbe);
    ScheatllLLVMConverter->Builder().SetInsertPoint(bbt);
    Then->ConvertAll();
    ScheatllLLVMConverter->Builder().CreateBr(EndBlock);
    ScheatllLLVMConverter->Builder().SetInsertPoint(bbe);
    Else->ConvertAll();
    parent->getBasicBlockList().push_back(EndBlock);
    ScheatllLLVMConverter->Builder().CreateBr(EndBlock);
    ScheatllLLVMConverter->Builder().SetInsertPoint(EndBlock);
    return nullptr;
    /*ScheatllLLVMConverter->Builder().CreateCondBr(Condition->LLVMEncode(), bbt, bbe);
    ScheatllLLVMConverter->Builder().SetInsertPoint(bbt);
    Then->ConvertAll();

    ScheatllLLVMConverter->Builder().SetInsertPoint(bbe);
    Else->ConvertAll();

    auto EndBlock = llvm::BasicBlock::Create(
        ScheatllLLVMConverter->Context(),
        "finally",
        parent
    );

    ScheatllLLVMConverter->Builder().SetInsertPoint(bbt);
    ScheatllLLVMConverter->Builder().CreateBr(EndBlock);

    ScheatllLLVMConverter->Builder().SetInsertPoint(bbe);
    ScheatllLLVMConverter->Builder().CreateBr(EndBlock);

    ScheatllLLVMConverter->Builder().SetInsertPoint(EndBlock);

    return nullptr;*/
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
