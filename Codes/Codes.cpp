#include "Codes.hpp"
#include "../Nodes/Nodes.hpp"
#include "../Global/Globals.hpp"
#include "../Exec/ScheatLLExec.hpp"
#include "../ScheatLL/ScheatLL.hpp"
#include "../Error/ScheatLLError.hpp"
#include <iostream>

using namespace scheat;

void Codes::ConvertAll()
{
    for (auto &&ir : buf)
    {
        ir->LLVMEncode();
    }
    
}

Codes::Codes(std::string s)
{
    label = s;
    if (EditingTarget == nullptr)
    {
        // if editing target is not edited, it is a initial scope, so parent will be null
        parent = nullptr;
    }else{
        parent = EditingTarget->getInsertedPoint();
        expectedReturnType = parent->expectedReturnType;
    }
}

Codes::Codes(std::string s, bool ex)
{
    label = s;
    sureToExecute = ex;
    if (EditingTarget == nullptr)
    {
        // if editing target is not edited, it is a initial scope, so parent will be null
        parent = nullptr;
    }else{
        parent = EditingTarget->getInsertedPoint();
        expectedReturnType = parent->expectedReturnType;
    }
}

Codes::Codes(std::string s, scheat_type* expected)
{
    label = s;
    expectedReturnType = expected;
    parent = nullptr;
}

Codes::~Codes()
{
}

void Codes::code(Expr *&code)
{
    buf.push_back(code);
    #ifdef DEBUG
    printf("%s : edited\n", getLabel().c_str());
    #endif
}

void Codes::Dump(){
    for (auto &&ir : buf)
    {
        std::cerr << EditingTarget->getIndent() << ((Expr *)ir)->Decode() << std::endl;
    }
}

Expr *Codes::findLocalVariable(std::string nm)
{

    if (parent != nullptr)
    {
        auto var = parent->findLocalVariable(nm);
        if (var != nullptr)
        {
            return var;
        }
        
    }
    
    auto iter = localVariables.find(nm);
    if (iter == localVariables.end())
    {
        return nullptr;
    }
    return iter->second;
    
}

void Codes::verifyReturn(scheat_type* tp)
{
    if (expectedReturnType == nullptr)
    {
        expectedReturnType = tp;
    }
    
    if (expectedReturnType != tp)
    {
        throw scheat_value_error();
    }
    if (sureToExecute)
    {
        returnsValue = true;
        if (parent != nullptr)
        {
            parent->verifyReturn(tp);
            parent->returnsValue = true;
        }
    }
    
}

void Codes::Exit()
{
    if (this != EditingTarget->insertPoint)
    {
        throw scheat_return_error();
    }
    
    for (auto &&[localk, localv] : localVariables)
    {
        if (localk == "its")
        {
            continue;
        }
        
        auto tp = localv->Type()->getElementType();
        if (tp->isInManaged())
        {
            EditingTarget->insertPoint.StartEditing(this);
            CallVoid(tp->getDeinitializer(), {localv});
            EditingTarget->insertPoint.PauseEditing();
        }
        
    }
    
}
