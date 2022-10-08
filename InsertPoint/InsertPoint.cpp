#include "InsertPoint.hpp"
#include "../Codes/Codes.hpp"

using namespace scheat;

void InsertPoint::StartEditing(Codes *nc){
    #ifdef DEBUG
    printf("start editing %s\n", nc->getLabel().c_str());
    #endif
    pointsStack.push(nc);
}

void InsertPoint::EndEditing() {
    (pointsStack).top()->Exit();
    #ifdef DEBUG
    printf("end editing %s\n", pointsStack.top()->getLabel().c_str());
    #endif
    pointsStack.pop();
}

InsertPoint::InsertPoint(Codes *origin)
{
    pointsStack.push(origin);
}

InsertPoint::~InsertPoint()
{
}

void InsertPoint::PauseEditing()
{
    #ifdef DEBUG
    printf("end editing %s\n", pointsStack.top()->getLabel().c_str());
    #endif
    pointsStack.pop();
}
