#if !defined(SCHEATFUNCTYPE_HPP)
#define SCHEATFUNCTYPE_HPP

#include "ScheatLLType.hpp"

#include <vector>

namespace scheatll
{

class scheat_func_type : public scheatll_type
{
private:
    scheatll_type* returnType;
    std::vector<scheatll_type*> argumentTypes;
public:
    scheat_func_type(scheatll_type*, std::vector<scheatll_type *>&);
    llvm::Type *LLVMType() override;
    std::string typeName() override;
    ~scheat_func_type();
};

} // namespace scheatll


#endif // SCHEATFUNCTYPE_HPP
