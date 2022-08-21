#ifndef _SCHEATLL_HPP_

#define _SCHEATLL_HPP_

#include "../Exec/ScheatLLExec.hpp"
#include "../Attribute/ScLLAttribute.hpp"
#include "../Type/ScLLType.hpp"
#include "../Nodes/BasicNodes.hpp"
#include "../Codes/Codes.hpp"
#include <string>
#include <vector>

namespace scheatll
{

class ScheatLLExec;
class Expr;
class Term;

class scheatll_type;

// scheatll cannot accept duplicating names even though their kinds are different.
// Name class check those problem. maybe used from scheatll2.0
class scheatll_name;

class scheatll_attribute;

// --defined
// creates a local variable.
// if wants to create a global one, use MakeGlobalVar
extern void MakeVar(scheatll_type *, std::string, scheatll_attribute);

// --defined
// sometime throws error.
// name duplicated, illegal type, ...
extern void MakeGlobalVar(scheatll_type *, std::string, scheatll_attribute);

// creates a global function
// it starts editing generated function. 
extern void MakeFunction(scheatll_type *, std::string, std::vector<scheatll_type *>, std::vector<std::string>, scheatll_attribute);

// translate C++ to Scheatll
extern Term* Constant(int);
extern Term* Constant(const char *);
extern Term* Constant(double);
extern Term* Constant(bool);

// create store instruction
// it does NOT check readability nor writability
// direct input will not happen in scheatll code, but api can cause
// if user wanted to do so.
// it is a 'raw' assign. someday it will be renamed to 'RawAssign'
// and new Assign can convert values and assign. 
extern void Assign(Expr *, Expr *);

// --defined
// it checks readability.
// it may throw two kinds of errors.
// value not readable
extern Term* Read(Expr*);

// !!
// it may throw errors.
// name not exists
extern Term* ID(std::string);

// be careful when calling this function.
// this sometimes generates various instructions.
extern void End();

// simple if-then.
extern void If(Expr *);

// if-then-else
extern void IfElse(Expr *);

extern void While(Expr *);

// --defined
// creates a attribute
extern scheatll_attribute Attribute(ReadAttribute r = readable, WriteAttribute w = writable, AccessAttribute a = _internal);
extern scheatll_attribute FunctionAttribute(AccessAttribute a = _internal);

// !!
// create a name from string.
extern scheatll_name* NewName(std::string);

} // namespace scheatll


#endif