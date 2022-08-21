#include "InsertPoint.hpp"
#include "../Codes/Codes.hpp"

using namespace scheatll;

void InsertPoint::StartEditing(Codes *nc){
    pointsStack.push(nc);
}

void InsertPoint::EndEditing() {
    (pointsStack).top()->Exit();
    pointsStack.pop();
}

InsertPoint::InsertPoint(Codes *origin)
{
    pointsStack.push(origin);
}

InsertPoint::~InsertPoint()
{
}

