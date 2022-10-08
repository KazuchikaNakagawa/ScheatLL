#if !defined(SCLLTYPE_H)
#define SCLLTYPE_H

#include "ScLLDefaultTypes.hpp"
#include "ScheatStruct.hpp"
#include <string>
#include <vector>

namespace scheat
{

class scheat_type;

// get a type from defaultTypes
extern scheat_type* Type(DefaultType);

// !!
// get a type from structure name.
// to create a new structure, use MakeStruct
extern scheat_type* Type(std::string);

extern scheat_type* PointerType(scheat_type*);

extern scheat_type* FuncType(scheat_type*, std::vector<scheat_type*>&);

} // namespace scheat


#endif // SCLLTYPE_H
