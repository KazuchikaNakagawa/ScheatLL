#include "Codes.hpp"
#include "../Nodes/Nodes.hpp"
#include "../Global/Globals.hpp"
#include "../Exec/ScheatLLExec.hpp"
#include <iostream>

using namespace scheatll;

void Codes::ConvertAll()
{
    for (auto &&ir : buf)
    {
        ((Expr *)ir)->LLVMEncode();
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
    }
}

Codes::~Codes()
{
}

void Codes::code(Expr *&code)
{
    buf.push_back(code);
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
