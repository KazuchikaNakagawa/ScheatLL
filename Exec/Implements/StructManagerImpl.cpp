#include "./StructManagerImpl.hpp"
#include "../../Type/ScLLType.hpp"
#include "../../Error/ScheatLLError.hpp"

using namespace scheat;


StructManagerImpl::StructManagerImpl()
{
}

StructManagerImpl::~StructManagerImpl()
{
}

Struct* StructManagerImpl::getStruct(std::string key)
{
    for (auto &&structInfo : globalStructures)
    {
        if (structInfo->StructName == key)
        {
            return structInfo;
        }
        
    }
    throw scheat_name_not_exist_error();
    
}

void StructManagerImpl::addStruct(std::string nm, scheat::SourceLocation l)
{
    auto structure = new Struct(nm, l);
    this->globalStructures.push_back(structure);
}
