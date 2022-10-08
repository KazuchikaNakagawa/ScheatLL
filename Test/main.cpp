#include "../ScheatLL/ScheatLL.hpp"

using namespace scheat;

int main() {
    ScheatLLExec *exec = new ScheatLLExec("test");
    exec->StartEditing();

    
    // ------------------
    MakeStruct("teststring");
    AddMember("teststring", "src", PointerType(Type(Int8)));
    AddMember("teststring", "length", Type(Int32));
    MakeGlobalVar(Type("teststring"), "a", Attribute());
    MakeVar(nullptr, "aptr", Attribute());
    Assign(ID("aptr"), Read(ID("a")->AccessTo("length")));
    exec->ConvertToLLVMIR();
    exec->LLVMDump();
    printf("\n\n\n\n\n\n\n\n");
    exec->Dump();
    exec->ExportObjectFile();
    return 0;
}
