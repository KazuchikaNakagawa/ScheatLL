#if !defined(SCLLDEFAULTTYPES_H)
#define SCLLDEFAULTTYPES_H

namespace scheatll
{

enum DefaultType {
    Int64,
    Int32,
    Int8,
    Int1,
    Double,
    Void,

    Pointer,
    FunctionType,
    
    // NotDefaultType -- used for representing classes, structures
    NotDefaultType
};

} // namespace scheatll


#endif // SCLLDEFAULTTYPES_H
