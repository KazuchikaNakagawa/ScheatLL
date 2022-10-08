#if !defined(SCHEATLLPOINTERTYPE_HPP)
#define SCHEATLLPOINTERTYPE_HPP

#include "ScheatLLType.hpp"

namespace scheat
{

class scheat_poiner_type : public scheat_type
{
private:
    scheat_type* elementType;
public:
    scheat_poiner_type(scheat_type*);
    llvm::Type *LLVMType() override;
    std::string typeName() override;
    scheat_type* getElementType() override { return elementType; };
    Term* SizeOf() override;
    ~scheat_poiner_type();
};

} // namespace scheat


#endif // SCHEATLLPOINTERTYPE_HPP
