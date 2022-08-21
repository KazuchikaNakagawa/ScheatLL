#include "SourceLocation.h"
#include <iostream>
using namespace scheat;


std::string SourceLocation::to_string(){
    if (line == 0 || column == 0) {
        return "User";
    }
    return fileName + ":" + std::to_string(line) + ":" + std::to_string(column);
}

SourceLocation scheat::OutOfFile(){
    return SourceLocation("", 0, 0);
}
