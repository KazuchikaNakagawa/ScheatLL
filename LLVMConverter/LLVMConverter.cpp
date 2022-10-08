#include "LLVMConverter.hpp"
#include "../Exec/ScheatLLExec.hpp"
#include "../Global/Globals.hpp"

using namespace scheat;

LLVMConverter::LLVMConverter(ScheatLLExec *exec)
: _Context(), _Builder(_Context)
{
    _Module = new llvm::Module(exec->getModuleName(), _Context);
    if (ScheatllLLVMConverter != nullptr)
    {
        // one thread can edit only one Converter, as well as Exec.
        return;
    }
    ScheatllLLVMConverter = this;
}

LLVMConverter::~LLVMConverter()
{
}

