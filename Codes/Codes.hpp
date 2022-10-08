#if !defined(CODES_HPP)
#define CODES_HPP

#include <string>
#include <vector>
#include <map>

namespace scheat
{

// All scheat code becomes Expr
class Expr;

class scheat_type;

class Codes
{
private:
    std::string label;
    std::vector<Expr *> buf;
    Codes *parent;
    scheat_type *expectedReturnType;
    bool sureToExecute = true;
    bool returnsValue = false;
public:
// simple scope, have a label name
    Codes(std::string s);

    // codes that might not be executed.
    Codes(std::string s, bool);

    // function codes
    Codes(std::string s, scheat_type*);

    // ScheatはStringの形で名前を保管する。Namespaceもろもろを計算してScheatLL上の名前に変換するのが仕事。
    std::map<std::string, Expr*> localVariables;

    // returns string
    std::string getLabel() { return label; };

    // add a code to this.
    void code(Expr *&);

    // Convert all IR into LLVM IR
    void ConvertAll();

    // dump this scope to stderr
    void Dump();

    // TODO: define this
    // called when this scope is returned, or broken. 
    void Exit();

    // for some classes wants to access buf
    std::vector<Expr *>& getBuffer() { return buf; };

    Expr *findLocalVariable(std::string);

    // if this is true, it is sure to return value.
    bool hasReturnValue() { return returnsValue; };

    void verifyReturn(scheat_type*);

    scheat_type* getExpectedReturnType() { return expectedReturnType; };

    ~Codes();
};

} // namespace scheat


#endif // CODES_HPP
