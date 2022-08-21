#include "ScLLType.hpp"
#include "ScheatLLType.hpp"
#include "ScheatFuncType.hpp"
using namespace scheatll;

scheatll_type* scheatll::Type(DefaultType dt)
{
    switch (dt)
    {
    case Int1:
        return scheatll_type::int1_type;
    case Int32:
        return scheatll_type::int_type;
    case Int64:
        return scheatll_type::int64_type;
    case Int8:
        return scheatll_type::int8_type;
    case Double:
        return scheatll_type::float_type;
    case Void:
        return scheatll_type::void_type;
    case NotDefaultType:
        // NotDefaultType is not a specific type
        return nullptr;
    default:
        break;
    }
    return nullptr;
}

scheatll_type* scheatll::Type(std::string)
{
    return nullptr;
}

scheatll_type* scheatll::PointerType(scheatll_type* tp)
{
    if (tp == nullptr)
    {
        return nullptr;
    }

    return tp->getPointerTo();
    
}

scheatll_type* scheatll::FuncType(scheatll_type* rt, std::vector<scheatll_type*>& ats)
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
