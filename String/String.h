#ifndef STRING_H
#define STRING_H

#include <stddef.h>
#include <string>

namespace scheat {

class String : public std::string {
public:
    String (){};
    String(const char *s) : std::string(s) {};
    String(std::string &&s) : std::string(s) {};
    String(value_type c) : std::string("")
    {
        this->push_back(c);
    };
    String stripPath();
    virtual ~String (){};
};

} /* scheat */

#endif
