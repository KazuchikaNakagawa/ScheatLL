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


using namespace scheat;

void scheat::MakeGlobalVar(scheat_type* tp, std::string nm, scheat_attribute attr, scheat::SourceLocation l) {
    auto iter = EditingTarget->globals.find(nm);
    if (iter != EditingTarget->globals.end())
    {
        throw scheat_name_already_defined_error();
        return;
    }

    auto inst = new GlobalAllocExpr(nm, tp, attr, l);
    EditingTarget->globals[nm] = inst;
    EditingTarget->VerifyGlobalVariables(inst);
    return;
}

void scheat::MakeVar(scheat_type *tp, std::string nm, scheat_attribute att, scheat::SourceLocation l)
{
    auto iter = EditingTarget->globals.find(nm);
    if (iter != EditingTarget->globals.end())
    {
        throw scheat_name_already_defined_error();
        return;
    }
    auto localiter = EditingTarget->getInsertedPoint()->localVariables.find(nm);
    if (localiter != EditingTarget->getInsertedPoint()->localVariables.end())
    {
        throw scheat_name_already_defined_error();
        return;
    }
    
    auto inst = new LocalAllocExpr(nm, tp, att, l);
    EditingTarget->getInsertedPoint()->localVariables[nm] = inst;
    EditingTarget->InsertIR(inst);

    return;
};

void scheat::MakeFunction(
    scheat_type *tp, 
    std::string nm, 
    std::vector<scheat_type *> tps, 
    std::vector<std::string> nms, 
    scheat_attribute att,
    scheat::SourceLocation l
)
{
    auto iter = EditingTarget->globals.find(nm);
    if (iter != EditingTarget->globals.end())
    {
        throw scheat_name_already_defined_error();
        return;
    }
    auto inst = new DeclareFuncExpr(nm, tp, tps, att, l);
    inst->setArgNames(nms);
    EditingTarget->VerifyGlobalFunc(inst);
    EditingTarget->setInsertPoint(inst->body);
    EditingTarget->globals[nm] = inst;
    return;
}

Term* scheat::Constant(int i, scheat::SourceLocation l) {
    return new ConstantInt32Expr(i, l);
}

Term* scheat::Constant(const char *s, scheat::SourceLocation l) {
    return new ConstantRawStringExpr(s, l);
}

Term* scheat::Constant(double d, scheat::SourceLocation l) {
    return new ConstantDoubleExpr(d, l);
}

Term* scheat::Constant(bool b, scheat::SourceLocation l) {
    return new ConstantBoolExpr(b, l);
}

Term* scheat::Read(Expr* val, scheat::SourceLocation l)
{
    if (!val->getAttribute().is_readable())
    {
        throw scheat_readability_error();
    }
    if (val->Type()->isFunctionType())
    {
        throw scheat_value_error();
    }
    
    if (!val->Type()->isPointerType())
    {
        // if tried to read non-pointer value, it must be a argument expression
        return new ReferenceExpr(val, l);
    }
    
    return new ReadExpr(val, l);
}

extern void scheat::Assign(Expr *ptr, Expr *val, scheat::SourceLocation l)
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
        throw scheat_type_error();
    }
    
    if (!ptr->getAttribute().is_writable())
    {
        throw scheat_writability_error();
    }
    
    auto inst = new AssignExpr(ptr, val, l);
    EditingTarget->InsertIR(inst);
}

void scheat::ConstAssign(Expr *ptr, Expr *val, scheat::SourceLocation l)
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
        throw scheat_type_error();
    }

    auto inst = new AssignExpr(ptr, val, l);
    EditingTarget->InsertIR(inst);
}

Term* scheat::ID(std::string id, scheat::SourceLocation l)
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
    
    throw scheat_name_not_exist_error();
}

void scheat::End()
{
    if (EditingTarget->getInsertedPoint()->hasReturnValue())
    {
        EditingTarget->insertPoint.PauseEditing();
        return;
    }
    
    EditingTarget->insertPoint.EndEditing();
}

void scheat::If(Expr *cond)
{
    if (cond == nullptr)
    {
        throw scheat_expected_value_error();
    }
    if (cond->Type() != Type(Int1))
    {
        throw scheat_expected_value_error();
    }
    auto thenCodes = new Codes("if");
    auto inst = new IfExpr(cond, thenCodes);
    EditingTarget->InsertIR(inst);
    EditingTarget->setInsertPoint(thenCodes);
}

void scheat::IfElse(Expr *cond)
{
    if (cond == nullptr)
    {
        throw scheat_expected_value_error();
    }
    if (cond->Type() != Type(Int1))
    {
        throw scheat_expected_value_error();
    }
    
    auto thenCodes = new Codes("if", false);
    auto elseCodes = new Codes("else", false);
    auto inst = new IfElseExpr(cond, thenCodes, elseCodes);
    EditingTarget->InsertIR(inst);
    EditingTarget->setInsertPoint(elseCodes);
    EditingTarget->setInsertPoint(thenCodes);
}

void scheat::While(Expr *cond)
{
    if (cond == nullptr)
    {
        throw scheat_expected_value_error();
    }
    if (cond->Type() != Type(Int1))
    {
        throw scheat_expected_value_error();
    }
    auto bodyCodes = new Codes("while.body", false);
    auto inst = new WhileExpr(cond, bodyCodes);
    EditingTarget->InsertIR(inst);
    EditingTarget->setInsertPoint(bodyCodes);
}

void scheat::Return(Expr *val, scheat::SourceLocation l)
{
    EditingTarget->getInsertedPoint()->verifyReturn(val->Type());
    auto inst = new ReturnExpr(val, l);
    EditingTarget->getInsertedPoint()->Exit();
    EditingTarget->InsertIR(inst);
}

Expr* scheat::Operate(Expr *L, std::string O, Expr *R, scheat::SourceLocation l)
{
    // Int-Int-Optimization
    if (L->Type() == Type(Int32) && R->Type() == Type(Int32))
    {
        if (
            O != "+" 
            && O != "-" 
            && O != "<"
            && O != ">"
            && O != "<="
            && O != ">="
            && O != "==")
        {
            throw scheat_operator_not_exist_error();
        }
        
        return new IntIntInfixOperatorExpr(L, O, R, l);
    }
    // Double-Double Optimization
    if (L->Type() == Type(Double) && R->Type() == Type(Double))
    {
        if (
            O != "+" 
            && O != "-" 
            && O != "<"
            && O != ">"
            && O != "<="
            && O != ">="
            && O != "==")
        {
            throw scheat_operator_not_exist_error();
        }
        
        return new DoubleDoubleInfixOperatorExpr(L, O, R, l);
    }
    auto oper = L->Type()->FindOperator(O);
    if (oper == nullptr)
    {
        throw scheat_operator_not_exist_error();
    }

    if (oper->Position != Infix)
    {
        throw scheat_operator_not_exist_error();
    }

    if (oper->Precedence != Normal)
    {
        throw scheat_operator_not_exist_error();
    }
    
    // TODO: call linked function
    throw scheat_unavailable_feature_error();
    return nullptr;
}

PrimaryExpr* scheat::Operate(PrimaryExpr *L, std::string O, PrimaryExpr *R, scheat::SourceLocation l)
{
    if (L->Type() == Type(Int32) && R->Type() == Type(Int32))
    {
        if (O != "*" && O != "/")
        {
            throw scheat_operator_not_exist_error();
        }

        return new IntIntInfixPrimaryOperatorExpr(L, O, R, l);
    }
    if (L->Type() == Type(Double) && R->Type() == Type(Double))
    {
        if (O != "*" && O != "/")
        {
            throw scheat_operator_not_exist_error();
        }

        return new DoubleDoubleInfixPrimaryOperatorExpr(L, O, R, l);
    }
    throw scheat_unavailable_feature_error();
    return nullptr;
}

Term* scheat::Operate(Term *L, std::string O, Term *R, scheat::SourceLocation l)
{
    // if (L->Type() == Type(Int32) && R->Type() == Type(Int32))
    // {
    //     if (O != "^")
    //     {
    //         throw scheat_operator_not_exist_error();
    //     }

    //     return new IntIntInfixTermOperatorExpr(L, O, R, l);
    // }
    throw scheat_unavailable_feature_error();
    return nullptr;
}

Expr* scheat::Operate(std::string O, Expr *R, scheat::SourceLocation l)
{
    throw scheat_unavailable_feature_error();
    return nullptr;
}

PrimaryExpr* scheat::Operate(std::string O, PrimaryExpr *R, scheat::SourceLocation l)
{
    throw scheat_unavailable_feature_error();
    return nullptr;
}

Term* scheat::Operate(std::string O, Term *R, scheat::SourceLocation l)
{
    throw scheat_unavailable_feature_error();
    return nullptr;
}

Expr* scheat::Operate(Expr *L, std::string O, scheat::SourceLocation l)
{
    throw scheat_unavailable_feature_error();
    return nullptr;
}

PrimaryExpr* scheat::Operate(PrimaryExpr *L, std::string O, scheat::SourceLocation l)
{
    throw scheat_unavailable_feature_error();
    return nullptr;
}

Term* scheat::Operate(Term *L, std::string O, scheat::SourceLocation l)
{
    throw scheat_unavailable_feature_error();
    return nullptr;
}

Term *scheat::Call(Expr *f, std::vector<Expr *> as, scheat::SourceLocation l)
{
    if (!f->Type()->isFunctionType())
    {
        throw scheat_value_error();
    }
    
    auto inst = new CallExpr(f, as, l);
    if (inst->Type() == scheat::Type(Void))
    {
        EditingTarget->InsertIR(inst);
    }
    
    return inst;
}

void scheat::CallVoid(Expr *f, std::vector<Expr *> as, scheat::SourceLocation l)
{
    if (!f->Type()->isFunctionType())
    {
        throw scheat_value_error();
    }
    // non-void function can be used
    // if (dynamic_cast<scheat_func_type*>(f->Type())->getReturnType() != Type(Void))
    // {
        
    // }
    
    
    auto inst = new CallExpr(f, as, l);
    EditingTarget->InsertIR(inst);
}

Term* scheat::Paren(Expr* expr, scheat::SourceLocation l)
{
    return new ParenExpr(expr, l);
}

void scheat::External(
    scheat_type* tp, 
    std::string nm, 
    std::vector<scheat_type *> ats, 
    bool varArg,
    scheat::SourceLocation l)
{
    auto inst = new ExternalFuncExpr(tp, nm, ats, varArg, l);
    EditingTarget->VerifyGlobalFunc(inst);
    EditingTarget->globals[nm] = inst;
}

void scheat::MakeStruct(std::string nm, scheat::SourceLocation l)
{
    EditingTarget->addStruct(nm, l);
}

void scheat::AddMember(std::string strName, std::string memName, scheat_type* tp, AccessAttribute aa)
{
    auto structure = EditingTarget->getStruct(strName);
    structure->AddMember(memName, tp, aa);
}

void scheat::EndStruct(std::string nm)
{
    
}

Term* scheat::Nil(scheat_type* tp, scheat::SourceLocation l)
{
    return new ConstantExprNil(tp->getElementType(), l);
}
