#if !defined(BASICNODES_HPP)
#define BASICNODES_HPP

#include <string>
#include "../SourceLocation/SourceLocation.h"
#include "../Attribute/ScLLAttribute.hpp"

namespace llvm
{

class Value;

} // namespace llvm


namespace scheat
{

class scheat_type;
class Term;

class Expr
{
protected:
    virtual llvm::Value *LLVMConvert(){ return nullptr; };

    // save a current value.
    llvm::Value *LLVMVal = nullptr;

    scheat::SourceLocation location;

public:
    Expr(scheat::SourceLocation);

    Expr() = delete;

    virtual scheat_type* Type();

    // !!
    // scheat as a string
    virtual std::string Decode() { return "ERROR"; };

    // !!
    // make into asm
    std::string Encode() { return ""; };

    // !!
    // convert to LLVM IR
    llvm::Value* LLVMEncode();

    // shows if it has a specific attributes.
    // default: readable, writable, internal
    virtual scheat_attribute getAttribute()
    { return scheat_attribute(readable, writable, _internal); };

    scheat::SourceLocation &Location() { return location; };

    Term* AccessTo(std::string, scheat::SourceLocation l = scheat::OutOfFile());

    virtual ~Expr();
};

class PrimaryExpr : public Expr
{
private:
    
public:
    PrimaryExpr() = delete;
    PrimaryExpr(scheat::SourceLocation loc) : Expr(loc) {};
    virtual ~PrimaryExpr();
};

class Term : public PrimaryExpr
{
private:

public:
    Term() = delete;
    Term(scheat::SourceLocation loc) : PrimaryExpr(loc) {};
    virtual ~Term();
};

// integrated to Expr. now it is not used.
class Attributed
{
public:
    virtual scheat_attribute getAttribute() = 0;
    Attributed();
    ~Attributed();
};

} // namespace scheat


#endif // BASICNODES_HPP
