#include "../API/ScheatLL.hpp"

using namespace scheatll;

int main() {
    ScheatLLExec *exec = new ScheatLLExec("test");
    exec->StartEditing();

    
    // ------------------
    MakeGlobalVar(nullptr, "undefinedTypeVar", Attribute(readable, unwritable));
    External(Type(Void), "exit", {Type(Int32)});
    MakeFunction(Type(Void), "abcde", {Type(Int32)}, {"dd"}, FunctionAttribute());
    If(Constant(true));
        Assign(ID("undefinedTypeVar"), Constant(50));
    End();
    End();
    CallVoid(ID("abcde"), {});
    Assign(ID("undefinedTypeVar"), Constant(50));
    exec->ConvertToLLVMIR();
    exec->LLVMDump();
    printf("\n\n\n\n\n\n\n\n");
    exec->Dump();
    exec->ExportObjectFile();
    return 0;
}
