#if !defined(CODES_HPP)
#define CODES_HPP

#include <string>
#include <vector>
#include <map>

namespace scheatll
{

// All scheatll code becomes Expr
class Expr;

class Codes
{
private:
    std::string label;
    std::vector<Expr *> buf;
    Codes *parent;
public:
    Codes(std::string s);

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
    void Exit() {};

    // for some classes wants to access buf
    std::vector<Expr *>& getBuffer() { return buf; };

    Expr *findLocalVariable(std::string);

    ~Codes();
};

} // namespace scheatll


#endif // CODES_HPP
