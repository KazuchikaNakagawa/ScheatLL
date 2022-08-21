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
