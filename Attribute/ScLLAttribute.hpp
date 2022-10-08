#if !defined(SCLLATTRIBUTE_HPP)
#define SCLLATTRIBUTE_HPP

#include <string>

namespace scheat
{

enum ReadAttribute {
    readable, // default
    unreadable
};

enum WriteAttribute {
    writable, // default
    unwritable
};

enum AccessAttribute {
    _public,
    _private,
    _internal, // default
};

class scheat_attribute
{
private:
    ReadAttribute r;
    WriteAttribute w;
    AccessAttribute a;
public:
    scheat_attribute(ReadAttribute, WriteAttribute, AccessAttribute);
    bool is_readable() { return r == readable; };
    bool is_writable() { return w == writable; };
    bool is_public() { return a == _public; };
    std::string to_string();
    scheat_attribute(const scheat_attribute &);
    ~scheat_attribute();
};

} // namespace scheat


#endif // SCLLATTRIBUTE_HPP
