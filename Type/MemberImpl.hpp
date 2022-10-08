#if !defined(SCHEATMEMBERIMPL_HPP)
#define SCHEATMEMBERIMPL_HPP

#include <vector>
#include <string>
#include "../Attribute/ScLLAttribute.hpp"

namespace scheat
{

class Term;
class Expr;
class scheat_type;

class Member
{
public:
    std::string MemberName;
    scheat_type* MemberType;
    uint32_t MemberIndex;
    AccessAttribute MemberOpenState;
};

class MemberImpl
{
protected:
    std::vector<Member> Member_list;
public:
    MemberImpl();
    virtual void AddMember(std::string, scheat_type*, AccessAttribute aa = _public);
    std::vector<scheat_type*> TypeList();
    std::vector<std::string> NameList();
    ~MemberImpl();
};

} // namespace scheat


#endif // SCHEATMEMBERIMPL_HPP
