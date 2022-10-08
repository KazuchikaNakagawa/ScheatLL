#include "MemberImpl.hpp"
using namespace scheat;

MemberImpl::MemberImpl()
{
}

MemberImpl::~MemberImpl()
{
}

void MemberImpl::AddMember(std::string nm, scheat_type* tp, AccessAttribute aa)
{
    Member m;
    m.MemberName = nm;
    m.MemberType = tp;
    m.MemberIndex = Member_list.size();
    Member_list.push_back(m);
}

std::vector<scheat_type*> MemberImpl::TypeList()
{
    std::vector<scheat_type*> result;
    for (auto &&member : Member_list)
    {
        result.push_back(member.MemberType);
    }
    return result;
}

std::vector<std::string> MemberImpl::NameList()
{
    std::vector<std::string> result;
    for (auto &&member : Member_list)
    {
        result.push_back(member.MemberName);
    }
    return result;
}
