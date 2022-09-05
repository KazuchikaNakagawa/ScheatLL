#include "ScheatLL.hpp"
#include "../Global/Globals.hpp"
#include "../Nodes/Nodes.hpp"
#include "../Codes/Codes.hpp"
#include "../Error/ScheatLLError.hpp"
#include "../Type/ScheatLLType.hpp"
#include "../Type/ScheatFuncType.hpp"
#include <iostream>
#include <cstdlib>
#include <typeinfo>


using namespace scheatll;

void scheatll::MakeGlobalVar(scheatll_type* tp, std::string nm, scheatll_attribute attr, scheat::SourceLocation l) {
    auto iter = EditingTarget->globals.find(nm);
    if (iter != EditingTarget->globals.end())
    {
        throw scheatll_name_already_defined_error();
        return;
    }

    auto inst = new GlobalAllocExpr(nm, tp, attr, l);
    EditingTarget->globals[nm] = inst;
    EditingTarget->VerifyGlobalVariables(inst);

    return;
}

void scheatll::MakeVar(scheatll_type *tp, std::string nm, scheatll_attribute att, scheat::SourceLocation l)
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
    
    auto inst = new LocalAllocExpr(nm, tp, att, l);
    EditingTarget->getInsertedPoint()->localVariables[nm] = inst;
    EditingTarget->InsertIR(inst);

    return;
};

void scheatll::MakeFunction(
    scheatll_type *tp, 
    std::string nm, 
    std::vector<scheatll_type *> tps, 
    std::vector<std::string> nms, 
    scheatll_attribute att,
    scheat::SourceLocation l
)
{
    auto iter = EditingTarget->globals.find(nm);
    if (iter != EditingTarget->globals.end())
    {
        throw scheatll_name_already_defined_error();
        return;
    }
    auto inst = new DeclareFuncExpr(nm, tp, tps, att, l);
    inst->setArgNames(nms);
    EditingTarget->VerifyGlobalFunc(inst);
    EditingTarget->setInsertPoint(inst->body);
    EditingTarget->globals[nm] = inst;
    return;
}

Term* scheatll::Constant(int i, scheat::SourceLocation l) {
    return new ConstantInt32Expr(i, l);
}

Term* scheatll::Constant(const char *s, scheat::SourceLocation l) {
    return new ConstantRawStringExpr(s, l);
}

Term* scheatll::Constant(double d, scheat::SourceLocation l) {
    return new ConstantDoubleExpr(d, l);
}

Term* scheatll::Constant(bool b, scheat::SourceLocation l) {
    return new ConstantBoolExpr(b, l);
}

Term* scheatll::Read(Expr* val, scheat::SourceLocation l)
{
    if (!val->getAttribute().is_readable())
    {
        throw scheatll_readability_error();
    }
    if (val->Type()->isFunctionType())
    {
        throw scheatll_value_error();
    }
    
    if (!val->Type()->isPointerType())
    {
        // if tried to read non-pointer value, it must be a argument expression
        return new ReferenceExpr(val, l);
    }
    
    return new ReadExpr(val, l);
}

extern void scheatll::Assign(Expr *ptr, Expr *val, scheat::SourceLocation l)
{
    if (ptr->Type() == nullptr)
    {
        auto _ptr = dynamic_cast<ReferenceExpr*>(ptr)->getSrc();
        // type-undefined value
        auto nptr1 = dynamic_cast<LocalAllocExpr*>(_ptr);
        if (nptr1 != nullptr)
        {
            nptr1->setType(val->Type());
        }else{
        auto nptr2 = dynamic_cast<GlobalAllocExpr*>(_ptr);
        if (nptr2 != nullptr)
        {
            nptr2->setType(val->Type());
        }
        
        }
    }
    
    if (val->Type()->getPointerTo() != ptr->Type())
    {
        throw scheatll_type_error();
    }
    
    if (!ptr->getAttribute().is_writable())
    {
        throw scheatll_writability_error();
    }
    
    auto inst = new AssignExpr(ptr, val, l);
    EditingTarget->InsertIR(inst);
}

Term* scheatll::ID(std::string id, scheat::SourceLocation l)
{
    auto iter = EditingTarget->globals.find(id);
    if (iter != EditingTarget->globals.end())
    {
        return new ReferenceExpr(iter->second, l);
    }
    

    auto var = EditingTarget->getInsertedPoint()->findLocalVariable(id);
    if (var != nullptr)
    {
        return new ReferenceExpr(var, l);
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

void scheatll::IfElse(Expr *cond)
{
    if (cond == nullptr)
    {
        throw scheatll_expected_value_error();
    }
    if (cond->Type() != Type(Int1))
    {
        throw scheatll_expected_value_error();
    }
    auto thenCodes = new Codes("if", false);
    auto elseCodes = new Codes("else", false);
    auto inst = new IfElseExpr(cond, thenCodes, elseCodes);
    EditingTarget->InsertIR(inst);
    EditingTarget->setInsertPoint(elseCodes);
    EditingTarget->setInsertPoint(thenCodes);
}

void scheatll::While(Expr *cond)
{
    if (cond == nullptr)
    {
        throw scheatll_expected_value_error();
    }
    if (cond->Type() != Type(Int1))
    {
        throw scheatll_expected_value_error();
    }
    auto bodyCodes = new Codes("while.body", false);
    auto inst = new WhileExpr(cond, bodyCodes);
    EditingTarget->InsertIR(inst);
    EditingTarget->setInsertPoint(bodyCodes);
}

void scheatll::Return(Expr *val, scheat::SourceLocation l)
{
    EditingTarget->getInsertedPoint()->verifyReturn(val->Type());
    auto inst = new ReturnExpr(val, l);
    EditingTarget->InsertIR(inst);
    EditingTarget->getInsertedPoint()->Exit();
}

Expr* scheatll::Operate(Expr *L, std::string O, Expr *R, scheat::SourceLocation l)
{
    // Int-Int-Optimization
    if (L->Type() == Type(Int32) && R->Type() == Type(Int32))
    {
        if (O != "+" && O != "-")
        {
            throw scheatll_operator_not_exist_error();
        }
        
        return new IntIntInfixOperatorExpr(L, O, R, l);
    }
    auto oper = L->Type()->FindOperator(O);
    if (oper == nullptr)
    {
        throw scheatll_operator_not_exist_error();
    }

    if (oper->Position != Infix)
    {
        throw scheatll_operator_not_exist_error();
    }

    if (oper->Precedence != Normal)
    {
        throw scheatll_operator_not_exist_error();
    }
    
    // TODO: call linked function
    throw scheatll_unavailable_feature_error();
    return nullptr;
}

PrimaryExpr* scheatll::Operate(PrimaryExpr *L, std::string O, PrimaryExpr *R, scheat::SourceLocation l)
{
    if (L->Type() == Type(Int32) && R->Type() == Type(Int32))
    {
        if (O != "*" && O != "/")
        {
            throw scheatll_operator_not_exist_error();
        }

        return new IntIntInfixPrimaryOperatorExpr(L, O, R, l);
    }
    throw scheatll_unavailable_feature_error();
    return nullptr;
}

Term* scheatll::Operate(Term *L, std::string O, Term *R, scheat::SourceLocation l)
{
    // if (L->Type() == Type(Int32) && R->Type() == Type(Int32))
    // {
    //     if (O != "^")
    //     {
    //         throw scheatll_operator_not_exist_error();
    //     }

    //     return new IntIntInfixTermOperatorExpr(L, O, R, l);
    // }
    throw scheatll_unavailable_feature_error();
    return nullptr;
}

Expr* scheatll::Operate(std::string O, Expr *R, scheat::SourceLocation l)
{
    throw scheatll_unavailable_feature_error();
    return nullptr;
}

PrimaryExpr* scheatll::Operate(std::string O, PrimaryExpr *R, scheat::SourceLocation l)
{
    throw scheatll_unavailable_feature_error();
    return nullptr;
}

Term* scheatll::Operate(std::string O, Term *R, scheat::SourceLocation l)
{
    throw scheatll_unavailable_feature_error();
    return nullptr;
}

Expr* scheatll::Operate(Expr *L, std::string O, scheat::SourceLocation l)
{
    throw scheatll_unavailable_feature_error();
    return nullptr;
}

PrimaryExpr* scheatll::Operate(PrimaryExpr *L, std::string O, scheat::SourceLocation l)
{
    throw scheatll_unavailable_feature_error();
    return nullptr;
}

Term* scheatll::Operate(Term *L, std::string O, scheat::SourceLocation l)
{
    throw scheatll_unavailable_feature_error();
    return nullptr;
}

Expr *scheatll::Call(Expr *f, std::vector<Expr *> as, scheat::SourceLocation l)
{
    if (!f->Type()->isFunctionType())
    {
        throw scheatll_value_error();
    }
    
    auto inst = new CallExpr(f, as, l);
    return inst;
}

void scheatll::CallVoid(Expr *f, std::vector<Expr *> as, scheat::SourceLocation l)
{
    if (!f->Type()->isFunctionType())
    {
        throw scheatll_value_error();
    }
    // non-void function can be used
    // if (dynamic_cast<scheat_func_type*>(f->Type())->getReturnType() != Type(Void))
    // {
        
    // }
    
    
    auto inst = new CallExpr(f, as, l);
    EditingTarget->InsertIR(inst);
}

void scheatll::External(
    scheatll_type* tp, 
    std::string nm, 
    std::vector<scheatll_type *> ats, 
    scheat::SourceLocation l)
{
    auto inst = new ExternalFuncExpr(tp, nm, ats, l);
    EditingTarget->VerifyGlobalFunc(inst);
    EditingTarget->globals[nm] = inst;
}
