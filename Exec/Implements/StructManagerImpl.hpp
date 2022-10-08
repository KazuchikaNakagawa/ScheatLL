#if !defined(STRUCTMANAGERIMPL)
#define STRUCTMANAGERIMPL

#include <vector>
#include <string>
#include "../../SourceLocation/SourceLocation.h"

namespace scheat
{

class Struct;

class StructManagerImpl
{
private:
    std::vector<Struct *> globalStructures;
public:
    StructManagerImpl();
    Struct *getStruct(std::string);
    void addStruct(std::string, scheat::SourceLocation);
    ~StructManagerImpl();
};

} // namespace scheat


#endif // STRUCTMANAGERIMPL
