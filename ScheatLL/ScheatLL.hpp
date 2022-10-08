#ifndef _SCHEATLL_HPP_

#define _SCHEATLL_HPP_

#include "../Exec/ScheatLLExec.hpp"
#include "../Attribute/ScLLAttribute.hpp"
#include "../Type/ScLLType.hpp"
#include "../Type/ScheatLLType.hpp"
#include "../Nodes/BasicNodes.hpp"
#include "../Codes/Codes.hpp"
#include <string>
#include <vector>

namespace scheat
{

class ScheatLLExec;
class Expr;
class Term;

class scheat_type;

// scheat cannot accept duplicating names even though their kinds are different.
// Name class check those problem. maybe used from scheat2.0
class scheat_name;

class scheat_attribute;

// --defined
// creates a local variable.
// if wants to create a global one, use MakeGlobalVar
extern void MakeVar(scheat_type *, std::string, scheat_attribute, scheat::SourceLocation l = scheat::OutOfFile());

// --defined
// sometime throws error.
// name duplicated, illegal type, ...
extern void MakeGlobalVar(scheat_type *, std::string, scheat_attribute, scheat::SourceLocation l = scheat::OutOfFile());

// creates a global function
// it starts editing generated function. 
extern void MakeFunction(
    scheat_type *, 
    std::string, 
    std::vector<scheat_type *>, 
    std::vector<std::string>, 
    scheat_attribute, 
    scheat::SourceLocation l = scheat::OutOfFile());

extern void MakeStruct(std::string, scheat::SourceLocation l = scheat::OutOfFile());
extern void AddMember(std::string, std::string, scheat_type*, AccessAttribute aa = _public);
extern void EndStruct(std::string);

extern void External(
    scheat_type*, 
    std::string, 
    std::vector<scheat_type *>, 
    bool varArg = false,
    scheat::SourceLocation l = scheat::OutOfFile());

// creates function calling
// if first argument is not a function, throws error
// if void function was called, returns nullptr. or returns return-value
extern Term* Call(Expr*, std::vector<Expr *>, scheat::SourceLocation l = scheat::OutOfFile());
extern void CallVoid(Expr *, std::vector<Expr *>, scheat::SourceLocation l = scheat::OutOfFile());

// translate C++ to Scheatll
extern Term* Constant(int, scheat::SourceLocation l = scheat::OutOfFile());
extern Term* Constant(const char *, scheat::SourceLocation l = scheat::OutOfFile());
extern Term* Constant(double, scheat::SourceLocation l = scheat::OutOfFile());
extern Term* Constant(bool, scheat::SourceLocation l = scheat::OutOfFile());
extern Term* Nil(scheat_type*, scheat::SourceLocation l = scheat::OutOfFile());

// create store instruction
// it does NOT check readability nor writability
// direct input will not happen in scheat code, but ScheatLL can cause
// if user wanted to do so.
// it is a 'raw' assign. someday it will be renamed to 'RawAssign'
// and new Assign can convert values and assign. 
extern void Assign(Expr *, Expr *, scheat::SourceLocation l = scheat::OutOfFile());

// it is the first and last assign for constant values
extern void ConstAssign(Expr *, Expr *, scheat::SourceLocation l = scheat::OutOfFile());

// --defined
// it checks readability.
// it may throw two kinds of errors.
// value not readable
extern Term* Read(Expr*, scheat::SourceLocation l = scheat::OutOfFile());

// !!
// it may throw errors.
// name not exists
extern Term* ID(std::string, scheat::SourceLocation l = scheat::OutOfFile());

// be careful when calling this function.
// this sometimes generates various instructions.
extern void End();

// simple if-then.
extern void If(Expr *);

// if-then-else
extern void IfElse(Expr *);

extern void While(Expr *);

extern void Return(Expr *, scheat::SourceLocation l = scheat::OutOfFile());

extern Term* Paren(Expr *, scheat::SourceLocation l = scheat::OutOfFile());

// --defined
// creates a attribute
extern scheat_attribute Attribute(ReadAttribute r = readable, WriteAttribute w = writable, AccessAttribute a = _internal);
extern scheat_attribute FunctionAttribute(AccessAttribute a = _internal);

// !!
// create a name from string.
extern scheat_name* NewName(std::string);

// Operate functions
// compiler may detect which to call correctly, but had better specify types(Expr--PrimaryExpr--Term)
// if selected operator is not for expr, occurs an error
// infixes
extern Expr*        Operate(Expr *, std::string, Expr *, scheat::SourceLocation l = scheat::OutOfFile());
extern PrimaryExpr* Operate(PrimaryExpr *, std::string, PrimaryExpr *, scheat::SourceLocation l = scheat::OutOfFile());
extern Term*        Operate(Term *, std::string, Term *, scheat::SourceLocation l = scheat::OutOfFile());

// prefixes
extern Expr*        Operate(std::string, Expr *, scheat::SourceLocation l = scheat::OutOfFile());
extern PrimaryExpr* Operate(std::string, PrimaryExpr *, scheat::SourceLocation l = scheat::OutOfFile());
extern Term*        Operate(std::string, Term *, scheat::SourceLocation l = scheat::OutOfFile());

// postfixes
extern Expr*        Operate(Expr *, std::string, scheat::SourceLocation l = scheat::OutOfFile());
extern PrimaryExpr* Operate(PrimaryExpr *, std::string, scheat::SourceLocation l = scheat::OutOfFile());
extern Term*        Operate(Term *, std::string, scheat::SourceLocation l = scheat::OutOfFile());

} // namespace scheat


#endif