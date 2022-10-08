#include "ScheatStruct.hpp"
#include "../Nodes/Nodes.hpp"
#include "../ScheatLL/ScheatLL.hpp"
#include "../Error/ScheatLLError.hpp"
#include "../Global/Globals.hpp"
#include "../LLVMConverter/LLVMConverter.hpp"
#include "../String/String.h"

using namespace scheat;
using namespace scheat;

Struct::Struct(std::string nm, scheat::SourceLocation l)
: scheat_type(StructType)
{
    StructName = nm;
    location = l;
    Initializer = new DeclareFuncExpr(
        StructName + " init from(" + StructName + "*)", 
        scheat::Type(Void),
        {PointerType(this)},
        FunctionAttribute(),
        location
    );
    std::vector<std::string> list = {"its"};
    Initializer->setArgNames(list);
    // TODO: Coding initializer
    EditingTarget->VerifyGlobalFunc(Initializer);
    Deinitializer = new DeclareFuncExpr(
        StructName + " deinit from(" + StructName + "*)", 
        scheat::Type(Void),
        {PointerType(this)},
        FunctionAttribute(),
        location
    );
    Deinitializer->setArgNames(list);
    EditingTarget->VerifyGlobalFunc(Deinitializer);

    auto constructor = new DeclareFuncExpr(
        StructName + " from()",
        this,
        {},
        FunctionAttribute(),
        location
    );
    EditingTarget->globals[StructName + " from()"] = constructor;
    EditingTarget->VerifyGlobalFunc(constructor);
    EditingTarget->insertPoint.StartEditing(constructor->body);
    MakeVar(this, ".alloca", Attribute(), location);
    Return(Read(ID(".alloca"), location));
    End();
}

DeclareFuncExpr* Struct::getInitializer()
{
    return Initializer;
}

DeclareFuncExpr* Struct::getDeinitializer()
{
    return Deinitializer;
}

Term* Struct::Access(Expr* lhs, std::string rhs, scheat::SourceLocation loc)
{
    for (auto &&member : Member_list)
    {
        if (member.MemberName == rhs)
        {
            return new GetElementExpr(lhs, member.MemberIndex, member.MemberType, loc);
        }
        
    }
    throw scheat_name_not_exist_error();
}

llvm::Type *Struct::LLVMType()
{
    if (_LLVMType == nullptr) _LLVMType = llvm::StructType::create(ScheatllLLVMConverter->Context(), StructName);
    std::vector<llvm::Type*> tps;
    for (auto &&tp : TypeList())
    {
        tps.push_back(tp->LLVMType());
    }
    
    _LLVMType->setBody(tps);
    return _LLVMType;
}

static String getDemangled(std::string base, std::vector<scheat_type*>& types)
{
    String result = base + " from(";
    for (auto &&tp : types)
    {
        result += tp->typeName() + ", ";
    }
    if (!types.empty())
    {
        result.pop_back(); result.pop_back();
    }
    result += ")";
    return result;
}

// struct cannot have a virtual method
Term* Struct::Access(Expr *lhs, std::string rhs, std::vector<scheat_type*> rhsSub, scheat::SourceLocation loc)
{
    auto expectedName = getDemangled(this->StructName + " " + rhs, rhsSub);
    return ID(expectedName);
};

void Struct::AddMember(std::string s, scheat_type* tp, AccessAttribute aa)
{
    MemberImpl::AddMember(s, tp, aa);
    EditingTarget->insertPoint.StartEditing(Initializer->body);
    if (tp->isInManaged())
    {
        CallVoid(tp->getDeinitializer(), {ID("its")});
    }
    else{
        Assign(ID("its")->AccessTo(s), tp->DefaultValue());
    }
    EditingTarget->insertPoint.PauseEditing();
}
