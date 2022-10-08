#if !defined(SCHEATOPERATORIMPL)
#define SCHEATOPERATORIMPL

#include <map>
#include <string>

namespace scheat
{

// How to parse operator Expression in Scheat
// class has a operator table given by OperatorImpl
// Scheat call ScheatLL.Call Function by $RhsTypeName.$OperatorSymbol from(RhsType, LhsType)

class scheat_type;
class DeclareFuncExpr;

enum OperatorPosition
{
    Prefix,
    Infix,
    Postfix
};

enum OperatorPrecedence
{
    Terminal,
    Primary,
    Normal
};

class Operator
{
public:
    OperatorPosition Position;
    OperatorPrecedence Precedence;
    // no longer used. legacy system
    // std::string LinkedFunctionID = "";
};

// feature of managing operators.
class OperatorImpl
{
protected:
    std::map<std::string, Operator> OperatorTable;
public:
    OperatorImpl();
    void AddPrefixOperator(std::string, OperatorPrecedence);
    void AddInfixOperator(std::string, OperatorPrecedence);
    void AddPostfixOperator(std::string, OperatorPrecedence);

    // if not found, returns nullptr
    // no thorwing
    Operator *FindOperator(std::string);

    ~OperatorImpl();
};
    
} // namespace scheat


#endif // SCHEATOPERATORIMPL
