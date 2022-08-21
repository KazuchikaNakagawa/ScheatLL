#if !defined(INSERTPOINT_H)
#define INSERTPOINT_H

#include <stack>

namespace scheatll
{

// Node receiver. 
class Codes;

class InsertPoint
{
private:
    std::stack<Codes *> pointsStack;
public:
    InsertPoint(Codes *origin);
    InsertPoint() {};

    // set a target to new Codes
    void StartEditing(Codes *);

    // pop a current Codes
    void EndEditing();

    operator Codes*() {
        if (pointsStack.empty())
        {
            return nullptr;
        }
        
        return pointsStack.top();
    }

    ~InsertPoint();
};

} // namespace scheatll


#endif // INSERTPOINT_H
