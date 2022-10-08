
#include "../ScheatLL/ScheatLL.hpp"

using namespace scheat;

int main(int argc, char const *argv[])
{
    auto exec = new ScheatLLExec("scheatstd");
    exec->StartEditing();
    External(Type(Int32), "printf", {PointerType(Type(Int8))}, true);
    MakeFunction(Type(Void), "print from(Int)", {Type(Int32)}, {"d"}, FunctionAttribute());
        CallVoid(ID("printf"), {Constant("%d"), ID("d")});
    End();
    MakeFunction(Type(Void), "print from(Double)", {Type(Int32)}, {"d"}, FunctionAttribute());
        CallVoid(ID("printf"), {Constant("%llf"), ID("d")});
    End();
    exec->ConvertToLLVMIR();
    exec->LLVMDump();
    exec->ExportObjectFile();
    return 0;
}
