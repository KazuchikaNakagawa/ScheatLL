#include "ScheatFuncType.hpp"
#include "../LLVMConverter/LLVMConverter.hpp"
#include "../Global/Globals.hpp"

using namespace scheatll;

scheat_func_type::scheat_func_type(scheatll_type* rt, std::vector<scheatll_type *>& agts)
: scheatll_type(FunctionType)
{
    returnType = rt;
    argumentTypes = agts;
}

scheat_func_type::~scheat_func_type()
{
}

llvm::Type *scheat_func_type::LLVMType()
{
    auto lrt = returnType->LLVMType();
    std::vector<llvm::Type *> lats;
    for (auto &&type : argumentTypes)
    {
        lats.push_back(type->LLVMType());
    }
    return llvm::FunctionType::get(lrt, lats, false);
}

std::string scheat_func_type::typeName()
{
    std::string result = "";
    result += returnType->typeName() + "(";
    int index = 0;
    for (auto &&type : argumentTypes)
    {
        result += type->typeName();
        index++;
        if (index != argumentTypes.size())
        {
            result += ", ";
        }
        
    }
    result += ")";
    return result;
}
