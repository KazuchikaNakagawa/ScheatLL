#ifndef SOURCELOCATION_H
#define SOURCELOCATION_H

#include "../String/String.h"

namespace scheat {

struct SourceLocation {
public:
    String fileName = "";
    unsigned line = 1;
    unsigned column = 0;
    String to_string();
    SourceLocation(String _0, unsigned _1, unsigned _2)
    : fileName(_0), line(_1), column(_2) {}
    SourceLocation() {}
    SourceLocation(const SourceLocation &);
};

extern SourceLocation OutOfFile();

} /* scheat */

#endif
