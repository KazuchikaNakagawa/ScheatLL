#if !defined(SCLLDEFAULTTYPES_H)
#define SCLLDEFAULTTYPES_H

namespace scheat
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

    StructType,
    
    // NotDefaultType -- used for representing classes, structures
    NotDefaultType
};

} // namespace scheat


#endif // SCLLDEFAULTTYPES_H
