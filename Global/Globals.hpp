#if !defined(GLOBALS_HPP)
#define GLOBALS_HPP

namespace scheat
{

class ScheatLLExec;
class LLVMConverter;

class Struct;

// Builder's property
extern ScheatLLExec* EditingTarget;

// ConverterImpl property
extern LLVMConverter* ScheatllLLVMConverter;

// StructEditor property
extern Struct* EditingStructure;

} // namespace scheat


#endif // GLOBALS_HPP
