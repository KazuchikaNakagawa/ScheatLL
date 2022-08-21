#include "../API/ScheatLL.hpp"
#include "ScLLAttribute.hpp"

using namespace scheatll;

scheatll_attribute scheatll::Attribute(ReadAttribute r, WriteAttribute w, AccessAttribute a)
{
    return scheatll_attribute(r, w, a);
}

scheatll_attribute scheatll::FunctionAttribute(AccessAttribute a)
{
    return scheatll_attribute(readable, unwritable, a);
}

std::string scheatll_attribute::to_string() {
    std::string result = "";
    if (r == readable)
    {
        result += "read, ";
    }else{
        result += "unreadable, ";
    }
    
    if (w == writable)
    {
        result += "write, ";
    }else{
        result += "unwritable, ";
    }
    
    if (a == _public)
    {
        result += "public";
    }else if (a == _private){
        result += "private";
    }else{
        result += "internal";
    }
    return result;
}


scheatll_attribute::scheatll_attribute(ReadAttribute r, WriteAttribute w, AccessAttribute a)
{
    this->r = r;
    this->w = w;
    this->a = a;
}

scheatll_attribute::~scheatll_attribute()
{
}
