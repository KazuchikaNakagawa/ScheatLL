#if !defined(SCHEATCONSTANTEXPR_HPP)
#define SCHEATCONSTANTEXPR_HPP

#include "BasicNodes.hpp"

namespace scheatll {

class ConstantInt32Expr : public Term
{
private:
    int data;
protected: 
    llvm::Value *LLVMConvert() override;
public:
    ConstantInt32Expr(int, scheat::SourceLocation);
    scheatll_type* Type() override;
    std::string Decode() override;
    ~ConstantInt32Expr();
};

class ConstantDoubleExpr : public Term
{
private:
    double data;
protected: 
    llvm::Value *LLVMConvert() override;
public:
    ConstantDoubleExpr(double, scheat::SourceLocation);
    scheatll_type* Type() override;
    std::string Decode() override;
    ~ConstantDoubleExpr();
};

class ConstantRawStringExpr : public Term
{
private:
    const char *str;
protected: 
    llvm::Value *LLVMConvert() override;
public:
    ConstantRawStringExpr(const char *, scheat::SourceLocation);
    scheatll_type* Type() override;
    std::string Decode() override;
    ~ConstantRawStringExpr();
};

class ConstantBoolExpr : public Term
{
private:
    bool data;
protected: 
    llvm::Value *LLVMConvert() override;
public:
    ConstantBoolExpr(bool, scheat::SourceLocation);
    scheatll_type* Type() override;
    std::string Decode() override;
    ~ConstantBoolExpr();
};

}

#endif // SCHEATCONSTANTEXPR_HPP
