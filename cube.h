#ifndef CUBE_H
#define CUBE_H

#include "baseobject.h"

class cube: public BaseObject
{
public:
    cube();
    cube(float s, PPoint center);
};

#endif // CUBE_H
