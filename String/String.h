#ifndef STRING_H
#define STRING_H

#include <stddef.h>
#include <string>
#include <map>

namespace scheat {

class String : public std::string {
private:
    std::map<String, int> Table;
public:
    String (){};
    String(const char *s) : std::string(s) {};
    String(std::string &&s) : std::string(s) {};
    String(const String &);
    String(const std::string &);
    String(value_type c) : std::string()
    {
        this->push_back(c);
    };
    String stripPath();
    String stripExtension();
    bool endsWith(String);
    bool startsWith(String);
    String indexed();
    virtual ~String (){};
};

} /* scheat */

#endif
