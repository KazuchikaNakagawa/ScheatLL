#if !defined(SCLLATTRIBUTE_HPP)
#define SCLLATTRIBUTE_HPP

#include <string>

namespace scheatll
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

class scheatll_attribute
{
private:
    ReadAttribute r;
    WriteAttribute w;
    AccessAttribute a;
public:
    scheatll_attribute(ReadAttribute, WriteAttribute, AccessAttribute);
    bool is_readable() { return r == readable; };
    bool is_writable() { return w == writable; };
    bool is_public() { return a == _public; };
    std::string to_string();
    scheatll_attribute(const scheatll_attribute &);
    ~scheatll_attribute();
};

} // namespace scheatll


#endif // SCLLATTRIBUTE_HPP
