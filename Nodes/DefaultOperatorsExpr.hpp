#if !defined(SCHEATDEFAULTTYPEOPERATORSEXPR_H)
#define SCHEATDEFAULTTYPEOPERATORSEXPR_H

#include "BasicNodes.hpp"
#include "../String/String.h"

namespace scheatll
{

class IntIntInfixOperatorExpr : public Expr
{
protected:
    Expr *lhs;
    std::string operatorSymbol;
    Expr *rhs;
    llvm::Value *LLVMConvert() override;
public:
    IntIntInfixOperatorExpr(Expr *, std::string, Expr *, scheat::SourceLocation);
    scheatll_type* Type() override;
    std::string Decode() override;
    ~IntIntInfixOperatorExpr();
};

class IntIntInfixPrimaryOperatorExpr : public PrimaryExpr
{
protected:
    PrimaryExpr *lhs;
    std::string operatorSymbol;
    PrimaryExpr *rhs;
    llvm::Value *LLVMConvert() override;
public:
    IntIntInfixPrimaryOperatorExpr(PrimaryExpr *, std::string, PrimaryExpr *, scheat::SourceLocation);
    scheatll_type* Type() override;
    std::string Decode() override;
    ~IntIntInfixPrimaryOperatorExpr();
};

class DoubleDoubleInfixOperatorExpr : public Expr
{
    protected:
    Expr *lhs;
    std::string operatorSymbol;
    Expr *rhs;
    llvm::Value *LLVMConvert() override;
    public:
    DoubleDoubleInfixOperatorExpr(Expr *, std::string, Expr *, scheat::SourceLocation);
    scheatll_type* Type() override;
    std::string Decode() override;
    ~DoubleDoubleInfixOperatorExpr();
};

class DoubleDoubleInfixPrimaryOperatorExpr : public PrimaryExpr
{
    protected:
    Expr *lhs;
    std::string operatorSymbol;
    Expr *rhs;
    llvm::Value *LLVMConvert() override;
    public:
    DoubleDoubleInfixPrimaryOperatorExpr(PrimaryExpr *, std::string, PrimaryExpr *, scheat::SourceLocation);
    scheatll_type* Type() override;
    std::string Decode() override;
    ~DoubleDoubleInfixPrimaryOperatorExpr();
};

} // namespace scheatll


#endif // SCHEATDEFAULTTYPEOPERATORSEXPR_H
