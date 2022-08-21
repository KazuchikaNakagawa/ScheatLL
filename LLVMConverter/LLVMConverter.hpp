#if !defined(LLVMCONVERTER_H)
#define LLVMCONVERTER_H

#include "llvm/ADT/APFloat.h"
#include "llvm/ADT/Optional.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/Comdat.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/Verifier.h"
#include "llvm/Support/FileSystem.h"
#include "llvm/Support/Host.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/MC/TargetRegistry.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Target/TargetMachine.h"
#include "llvm/Target/TargetOptions.h"

namespace scheatll
{

class ScheatLLExec;

class LLVMConverter
{
private:
    llvm::LLVMContext _Context;
    llvm::IRBuilder<> _Builder;
    llvm::Module*     _Module;
public:
    LLVMConverter(ScheatLLExec *);
    llvm::LLVMContext &Context() { return _Context; };
    llvm::IRBuilder<> &Builder() { return _Builder; };
    llvm::Module*      Module() { return _Module; };
    ~LLVMConverter();
};


} // namespace scheatll


#endif // LLVMCONVERTER_H
