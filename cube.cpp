#include "cube.h"
#include <vector>

using glm::vec4;
using glm::vec2;

cube::cube()
{

}
//use simple creator!!!
cube::cube(float s, PPoint Ncenter)
{
    points={
        vec4(-0.5,-0.5,-0.5,1)*s,
        vec4(-0.5,-0.5,0.5,1)*s,
        vec4(-0.5,0.5,-0.5,1)*s,
        vec4(-0.5,0.5,0.5,1)*s,
        vec4(0.5,-0.5,-0.5,1)*s,
        vec4(0.5,-0.5,0.5,1)*s,
        vec4(0.5,0.5,-0.5,1)*s,
        vec4(0.5,0.5,0.5,1)*s
    };
    polygons={
        {2,3,7,6},//TOP
        {5,7,3,1},//front
        {4,6,7,5},//RIGHT
        {0,2,6,4},//back
        {1,3,2,0},//LEFT
        {4,5,1,0}//BOTTOM
    };
    texNums={
        6,
        7,
        8,
        7,
        8,
        9
    };
    std::vector<vec2> tp = {
        vec2(1,1),
        vec2(1,0),
        vec2(0,0),
        vec2(0,1),

    };
    texCoords={
        {tp[0],tp[1],tp[2],tp[3]},
        {tp[0],tp[1],tp[2],tp[3]},
        {tp[0],tp[1],tp[2],tp[3]},
        {tp[0],tp[1],tp[2],tp[3]},
        {tp[0],tp[1],tp[2],tp[3]},
        {tp[0],tp[1],tp[2],tp[3]},
    };
    moveTo(Ncenter);
}
