#include "../API/ScheatLL.hpp"

using namespace scheatll;

int main() {
    ScheatLLExec *exec = new ScheatLLExec("test");
    exec->StartEditing();

    
    // ------------------
    MakeGlobalVar(nullptr, "undefinedTypeVar", Attribute());
    Assign(ID("undefinedTypeVar"), Constant(50));
    exec->ConvertToLLVMIR();
    exec->LLVMDump();
    printf("\n\n\n\n\n\n\n\n");
    exec->Dump();
    exec->ExportObjectFile();
    return 0;
}
