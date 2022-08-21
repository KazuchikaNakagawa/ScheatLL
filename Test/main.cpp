#include "../API/ScheatLL.hpp"

using namespace scheatll;

int main() {
    ScheatLLExec *exec = new ScheatLLExec("test");
    exec->StartEditing();


    // ------------------
    MakeGlobalVar(Type(Int32), "GlobalTestVar", Attribute());
    MakeVar(Type(Int1), "testbool", Attribute());
    MakeGlobalVar(Type(Int32), "testvar2", Attribute());
    MakeFunction(Type(Int64), "testfunc", { Type(Int32),PointerType(PointerType(Type(Int8))) }, { "argc","argv" }, FunctionAttribute());
        Assign(ID("testvar2"), Constant(20));
    End();

    // ------------------
    Assign(ID("GlobalTestVar"), Constant(150));
    Assign(ID("testvar2"), Read(ID("GlobalTestVar")));
    Assign(ID("testbool"), Constant(true));
    If(Read(ID("testbool")));
        Assign(ID("GlobalTestVar"), Constant(11));
    End();
    exec->ConvertToLLVMIR();
    exec->LLVMDump();
    printf("\n\n\n\n\n\n\n\n");
    exec->Dump();
    return 0;
}
