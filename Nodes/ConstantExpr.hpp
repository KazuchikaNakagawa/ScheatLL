#if !defined(SCHEATCONSTANTEXPR_HPP)
#define SCHEATCONSTANTEXPR_HPP

#include "BasicNodes.hpp"

namespace scheat {

class ConstantInt32Expr : public Term
{
private:
    int data;
protected: 
    llvm::Value *LLVMConvert() override;
public:
    ConstantInt32Expr(int, scheat::SourceLocation);
    scheat_type* Type() override;
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
    scheat_type* Type() override;
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
    scheat_type* Type() override;
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
    scheat_type* Type() override;
    std::string Decode() override;
    ~ConstantBoolExpr();
};

class ConstantExprNil : public Term
{
private:
    // elementType
    scheat_type* type;
protected:
    llvm::Value *LLVMConvert() override;
public:
    ConstantExprNil(scheat_type*, scheat::SourceLocation);
    scheat_type* Type() override;
    std::string Decode() override;
    ~ConstantExprNil();
};

}

#endif // SCHEATCONSTANTEXPR_HPP
