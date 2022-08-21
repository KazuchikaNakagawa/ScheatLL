#if !defined(SCLLTYPE_H)
#define SCLLTYPE_H

#include "ScLLDefaultTypes.hpp"
#include <string>
#include <vector>

namespace scheatll
{

class scheatll_type;

// create a type from defaultTypes
extern scheatll_type* Type(DefaultType);

// !!
// create a type from structure name.
extern scheatll_type* Type(std::string);

extern scheatll_type* PointerType(scheatll_type*);

extern scheatll_type* FuncType(scheatll_type*, std::vector<scheatll_type*>&);

} // namespace scheatll


#endif // SCLLTYPE_H
