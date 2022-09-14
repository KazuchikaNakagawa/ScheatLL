#include "String.h"
using namespace scheat;

String String::stripPath()
{
    auto pos = this->rfind("/");
    if (pos == std::string::npos)
    {
        return *this;
    }
    
    return this->substr(pos + 1, this->size());
}

String::String(const String &s)
: std::string(s)
{
}

String::String(const std::string &s)
: std::string(s)
{
}

bool String::endsWith(String subs)
{
    auto pos = this->find(subs);
    if (pos == std::string::npos)
    {
        return false;
    }
    if (pos + subs.size() == this->size()){
        return true;
    }else{
        return false;
    }
}

bool String::startsWith(String subs)
{
    auto pos = this->find(subs);
    if (pos == std::string::npos)
    {
        return false;
    }
    if (pos == 0){
        return true;
    }else{
        return false;
    }
}

String String::stripExtension()
{
    auto pos = this->rfind(".");
    if (pos == std::string::npos)
    {
        return *this;
    }
    return this->substr(0, pos);
}

String String::indexed()
{
    return *this + "." + std::to_string(Table[*this]++);
}
