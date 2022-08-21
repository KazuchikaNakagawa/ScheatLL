#if !defined(SCHEATLLPOINTERTYPE_HPP)
#define SCHEATLLPOINTERTYPE_HPP

#include "ScheatLLType.hpp"

namespace scheatll
{

class scheatll_poiner_type : public scheatll_type
{
private:
    scheatll_type* elementType;
public:
    scheatll_poiner_type(scheatll_type*);
    llvm::Type *LLVMType() override;
    std::string typeName() override;
    scheatll_type* getElementType() override { return elementType; };
    ~scheatll_poiner_type();
};

} // namespace scheatll


#endif // SCHEATLLPOINTERTYPE_HPP
