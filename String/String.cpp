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
