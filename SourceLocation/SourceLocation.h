#ifndef SOURCELOCATION_H
#define SOURCELOCATION_H

#include <string>

namespace scheat {

struct SourceLocation {
public:
    std::string fileName = "";
    unsigned line = 1;
    unsigned column = 0;
    std::string to_string();
    SourceLocation(std::string _0, unsigned _1, unsigned _2)
    : fileName(_0), line(_1), column(_2) {}
    SourceLocation() {}
};

extern SourceLocation OutOfFile();

} /* scheat */

#endif
