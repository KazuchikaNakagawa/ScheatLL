#if !defined(SCHEATLLEXEC_HPP)
#define SCHEATLLEXEC_HPP

#include "../InsertPoint/InsertPoint.hpp"
#include "../SourceLocation/SourceLocation.h"
#include "Implements/IndentManagerImpl.hpp"
#include "Implements/StructManagerImpl.hpp"
#include <string>
#include <map>
#include <vector>

namespace scheat
{

class Expr;

class Codes;

class InsertPoint;

class Struct;

class DeclareFuncExpr;

// it named 'Exec', but it represents .a(lib) and so on. 
class ScheatLLExec : public IndentManagerImpl, public StructManagerImpl
{
protected:
    // means global{} field. contains global variable and class infos
    Codes *globalScope;

    // itself function. named module name. 
    DeclareFuncExpr *firstScope;

    // exit function. deinitialize global variables
    DeclareFuncExpr *exitScope;

    std::string ModuleName;

    std::vector<Expr *> globalFunctions;

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
    void InsertIRToStart();
    void InsertIRToExit();

    // do not call this even if you want to make a global variable. use MakeGlobalVar in the ScheatLL.hpp
    void VerifyGlobalVariables(Expr *);

    void VerifyGlobalFunc(Expr *);

    // if it was converted into LLVM, dump its Module to stderr
    void LLVMDump();

    // dump source code to stderr
    void Dump();

    Codes *getInsertedPoint() { return insertPoint; };

    InsertPoint insertPoint;

    void setInsertPoint(Codes *c) { insertPoint.StartEditing(c); };

    void ExportObjectFile(bool ll = true, std::string FilePath = "");

    ~ScheatLLExec();
};


} // namespace scheat


#endif // SCHEATLLEXEC_HPP