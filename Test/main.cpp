#include "../API/ScheatLL.hpp"

using namespace scheatll;

int main() {
    ScheatLLExec *exec = new ScheatLLExec("test");
    exec->StartEditing();

    
    // ------------------
    MakeGlobalVar(Type(Int32), "GlobalTestVar", Attribute());
    
    MakeVar(Type(Int1), "testbool", Attribute());
    MakeGlobalVar(Type(Int32), "testvar2", Attribute());
    
    MakeFunction(Type(Int32), "testfunc", { Type(Int32),PointerType(PointerType(Type(Int8))) }, { "argc","argv" }, FunctionAttribute());
        Assign(ID("testvar2"), Constant(20));
        Return(Read(ID("testvar2")));
    End();
    
    // ------------------
    Assign(ID("GlobalTestVar"), Constant(150));
    // Assign(ID("testvar2"), Read(ID("GlobalTestVar")));
    Assign(ID("testbool"), Constant(true));
    
    IfElse(Read(ID("testbool")));
        Assign(ID("GlobalTestVar"), Constant(11));
    End();
        Assign(ID("GlobalTestVar"), Constant(190));
    End();
    //End();
    exec->ConvertToLLVMIR();
    exec->LLVMDump();
    printf("\n\n\n\n\n\n\n\n");
    exec->Dump();
    exec->ExportObjectFile();
    return 0;
}
