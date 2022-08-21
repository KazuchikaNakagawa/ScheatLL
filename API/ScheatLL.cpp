#include "ScheatLL.hpp"
#include "../Global/Globals.hpp"
#include "../Nodes/Nodes.hpp"
#include "../Codes/Codes.hpp"
#include "../Error/ScheatLLError.hpp"
#include "../Type/ScheatLLType.hpp"


using namespace scheatll;

void scheatll::MakeGlobalVar(scheatll_type* tp, std::string nm, scheatll_attribute attr) {
    auto iter = EditingTarget->globals.find(nm);
    if (iter != EditingTarget->globals.end())
    {
        throw scheatll_name_already_defined_error();
        return;
    }

    auto inst = new GlobalAllocExpr(nm, tp, attr);
    EditingTarget->globals[nm] = inst;
    EditingTarget->VerifyGlobalVariables(inst);

    return;
}

void scheatll::MakeVar(scheatll_type *tp, std::string nm, scheatll_attribute att)
{
    auto iter = EditingTarget->globals.find(nm);
    if (iter != EditingTarget->globals.end())
    {
        throw scheatll_name_already_defined_error();
        return;
    }
    auto localiter = EditingTarget->getInsertedPoint()->localVariables.find(nm);
    if (localiter != EditingTarget->getInsertedPoint()->localVariables.end())
    {
        throw scheatll_name_already_defined_error();
        return;
    }
    
    auto inst = new LocalAllocExpr(nm, tp, att);
    EditingTarget->getInsertedPoint()->localVariables[nm] = inst;
    EditingTarget->InsertIR(inst);

    return;
};

void scheatll::MakeFunction(
    scheatll_type *tp, 
    std::string nm, 
    std::vector<scheatll_type *> tps, 
    std::vector<std::string> nms, 
    scheatll_attribute att)
{
    auto iter = EditingTarget->globals.find(nm);
    if (iter != EditingTarget->globals.end())
    {
        throw scheatll_name_already_defined_error();
        return;
    }
    auto inst = new DeclareFuncExpr(nm, tp, tps, att);
    inst->setArgNames(nms);
    EditingTarget->VerifyGlobalFunc(inst);
    EditingTarget->setInsertPoint(inst->body);
    return;
}

Term* scheatll::Constant(int i) {
    return new ConstantInt32Expr(i);
}

Term* scheatll::Constant(const char *s) {
    return new ConstantRawStringExpr(s);
}

Term* scheatll::Constant(double d) {
    return new ConstantDoubleExpr(d);
}

Term* scheatll::Constant(bool b) {
    return new ConstantBoolExpr(b);
}

Term* scheatll::Read(Expr* val)
{
    if (!val->getAttribute().is_readable())
    {
        throw scheatll_readability_error();
    }
    if (!val->Type()->isPointerType())
    {
        // if tried to read non-pointer value, it must be a argument expression
        return new ReferenceExpr(val);
    }
    
    return new ReadExpr(val);
}

extern void scheatll::Assign(Expr *ptr, Expr *val)
{
    if (val->Type()->getPointerTo() != ptr->Type())
    {
        throw scheatll_type_error();
    }
    
    if (!ptr->getAttribute().is_writable())
    {
        throw scheatll_writability_error();
    }
    
    auto inst = new AssignExpr(ptr, val);
    EditingTarget->InsertIR(inst);
}

Term* scheatll::ID(std::string id)
{
    auto iter = EditingTarget->globals.find(id);
    if (iter != EditingTarget->globals.end())
    {
        return new ReferenceExpr(iter->second);
    }
    

    iter = EditingTarget->getInsertedPoint()->localVariables.find(id);
    if (iter != EditingTarget->getInsertedPoint()->localVariables.end())
    {
        return new ReferenceExpr(iter->second);
    }
    
    throw scheatll_name_not_exist_error();
}

void scheatll::End()
{
    EditingTarget->insertPoint.EndEditing();
}

void scheatll::If(Expr *cond)
{
    if (cond == nullptr)
    {
        throw scheatll_expected_value_error();
    }
    if (cond->Type() != Type(Int1))
    {
        throw scheatll_expected_value_error();
    }
    auto thenCodes = new Codes("if");
    auto inst = new IfExpr(cond, thenCodes);
    EditingTarget->InsertIR(inst);
    EditingTarget->setInsertPoint(thenCodes);
}
