#if !defined(BASICNODES_HPP)
#define BASICNODES_HPP

#include <string>
#include "../SourceLocation/SourceLocation.h"
#include "../Attribute/ScLLAttribute.hpp"

namespace llvm
{

class Value;

} // namespace llvm


namespace scheatll
{

class scheatll_type;

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

    virtual scheatll_type* Type();

    // !!
    // scheatll as a string
    virtual std::string Decode() { return "ERROR"; };

    // !!
    // make into asm
    std::string Encode() { return ""; };

    // !!
    // convert to LLVM IR
    llvm::Value* LLVMEncode();

    // shows if it has a specific attributes.
    // default: readable, writable, internal
    virtual scheatll_attribute getAttribute()
    { return scheatll_attribute(readable, writable, _internal); };

    scheat::SourceLocation &Location() { return location; };

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
    virtual scheatll_attribute getAttribute() = 0;
    Attributed();
    ~Attributed();
};

} // namespace scheatll


#endif // BASICNODES_HPP
