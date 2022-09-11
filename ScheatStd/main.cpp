
#include "../API/ScheatLL.hpp"

using namespace scheatll;

int main(int argc, char const *argv[])
{
    auto exec = new ScheatLLExec("scheatstd");
    exec->StartEditing();
    External(Type(Int32), "printf", {PointerType(Type(Int8))}, true);
    MakeFunction(Type(Void), "print from(Int)", {Type(Int32)}, {"d"}, FunctionAttribute());
        CallVoid(ID("printf"), {Constant("%d"), ID("d")});
    End();
    exec->ConvertToLLVMIR();
    exec->LLVMDump();
    exec->ExportObjectFile();
    return 0;
}
