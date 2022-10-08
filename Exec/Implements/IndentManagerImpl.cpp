#include "IndentManagerImpl.hpp"
using namespace scheat;


IndentManagerImpl::IndentManagerImpl()
{
}

IndentManagerImpl::~IndentManagerImpl()
{
}

std::string IndentManagerImpl::getIndent()
{
    std::string res;
    for (size_t i = 0; i < IndentCount; i++)
    {
        res += "    ";
    }
    return res;
}

