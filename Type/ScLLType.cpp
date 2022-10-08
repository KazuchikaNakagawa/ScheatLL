#include "ScLLType.hpp"
#include "ScheatLLType.hpp"
#include "ScheatFuncType.hpp"
#include "../Global/Globals.hpp"
#include "../Exec/ScheatLLExec.hpp"
using namespace scheat;

scheat_type* scheat::Type(DefaultType dt)
{
    switch (dt)
    {
    case Int1:
        return scheat_type::int1_type;
    case Int32:
        return scheat_type::int_type;
    case Int64:
        return scheat_type::int64_type;
    case Int8:
        return scheat_type::int8_type;
    case Double:
        return scheat_type::float_type;
    case Void:
        return scheat_type::void_type;
    case NotDefaultType:
        // NotDefaultType is not a specific type
        return nullptr;
    default:
        break;
    }
    return nullptr;
}

scheat_type* scheat::Type(std::string nm)
{
    return EditingTarget->getStruct(nm);
}

scheat_type* scheat::PointerType(scheat_type* tp)
{
    if (tp == nullptr)
    {
        return nullptr;
    }

    return tp->getPointerTo();
    
}

scheat_type* scheat::FuncType(scheat_type* rt, std::vector<scheat_type*>& ats)
{
    std::string result;
    int index = 0;
    for (auto &&type : ats)
    {
        result += type->typeName();
        index++;
        if (index != ats.size())
        {
            result += ", ";
        }
        
    }
    if (rt->funcTypeTable.find(result) == rt->funcTypeTable.end())
    {
        auto fty = new scheat_func_type(rt, ats);
        rt->funcTypeTable[result] = fty;
        return fty;
    }
    return rt->funcTypeTable[result];
}
