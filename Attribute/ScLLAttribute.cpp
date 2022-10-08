#include "../ScheatLL/ScheatLL.hpp"
#include "ScLLAttribute.hpp"

using namespace scheat;

scheat_attribute scheat::Attribute(ReadAttribute r, WriteAttribute w, AccessAttribute a)
{
    return scheat_attribute(r, w, a);
}

scheat_attribute::scheat_attribute(const scheat_attribute &attr)
: scheat_attribute(attr.r, attr.w, attr.a)
{
}

scheat_attribute scheat::FunctionAttribute(AccessAttribute a)
{
    return scheat_attribute(readable, unwritable, a);
}

std::string scheat_attribute::to_string() {
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


scheat_attribute::scheat_attribute(ReadAttribute r, WriteAttribute w, AccessAttribute a)
{
    this->r = r;
    this->w = w;
    this->a = a;
}

scheat_attribute::~scheat_attribute()
{
}
