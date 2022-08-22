#if !defined(SCHEATLLEXEC_HPP)
#define SCHEATLLEXEC_HPP

#include "../InsertPoint/InsertPoint.hpp"
#include <string>
#include <map>
#include <vector>

namespace scheatll
{

class Expr;

class Codes;

class InsertPoint;

// it named 'Exec', but it represents .a(lib) and so on. 
class ScheatLLExec
{
protected:
    // means global{} field. contains global variable and class infos
    Codes *globalScope;

    // itself function. named module name. 
    Expr *firstScope;

    // exit function. deinitialize global variables
    Expr *exitScope;

    std::string ModuleName;

    std::vector<Expr *> globalFunctions;

    unsigned int IndentCount = 0;
public:
    // constructor -- needs module name.
    ScheatLLExec(std::string modName);

    // returns module name. (globalScope->label)
    std::string getModuleName();

    // set a editing object itself
    void StartEditing();

    // !!
    void ConvertToLLVMIR();

    // global variables, functions, and so on.
    std::map<std::string, Expr*> globals;

    void InsertIR(Expr *);

    // do not call this even if you want to make a global variable. use MakeGlobalVar in the ScheatLL.hpp
    void VerifyGlobalVariables(Expr *);

    void VerifyGlobalFunc(Expr *);

    // if it was converted into LLVM, dump its Module to stderr
    void LLVMDump();

    // dump source code to stderr
    void Dump();

    Codes *getInsertedPoint() { return insertPoint; };

    InsertPoint insertPoint;

    std::string getIndent();

    void setInsertPoint(Codes *c) { insertPoint.StartEditing(c); };

    void IncreaseIndent() { IndentCount++; };
    void DecreaseIndent() { IndentCount--; };

    void ExportObjectFile();

    ~ScheatLLExec();
};


} // namespace scheatll


#endif // SCHEATLLEXEC_HPP