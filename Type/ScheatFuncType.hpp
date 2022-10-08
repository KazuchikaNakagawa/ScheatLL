#if !defined(SCHEATFUNCTYPE_HPP)
#define SCHEATFUNCTYPE_HPP

#include "ScheatLLType.hpp"

#include <vector>

namespace scheat
{

class Term;

class scheat_func_type : public scheat_type
{
private:
    scheat_type* returnType;
    std::vector<scheat_type*> argumentTypes;
public:
    scheat_func_type(scheat_type*, std::vector<scheat_type *>&);
    llvm::Type *LLVMType() override;
    std::string typeName() override;
    scheat_type* getReturnType() override{ return returnType; };
    Term* SizeOf() override;
    ~scheat_func_type();
};

} // namespace scheat


#endif // SCHEATFUNCTYPE_HPP
