#include "SourceLocation.h"
#include <iostream>
using namespace scheat;


String SourceLocation::to_string(){
    if (line == 0 || column == 0) {
        return "Scheat";
    }
    return fileName + ":" + std::to_string(line) + ":" + std::to_string(column);
}

SourceLocation scheat::OutOfFile(){
    return SourceLocation("", 0, 0);
}

SourceLocation::SourceLocation(const SourceLocation &l)
{
    line = l.line;
    column = l.column;
    fileName = l.fileName;
}
