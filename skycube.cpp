#include "skycube.h"



using glm::vec4;
using glm::vec2;

skycube::skycube()
{

}

skycube::skycube(float s, PPoint center)
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
            {2,6,7,3},//TOP
            {5,1,3,7},//front
            {1,0,2,3},//LEFT
            {0,4,6,2},//back
            {4,5,7,6},//RIGHT
            {4,0,1,5}//BOTTOM
        };
        texNums={
            0,
            1,
            2,
            3,
            4,
            5
        };
        std::vector<vec2> tp = {
            vec2(0,1),
            vec2(0,0),
            vec2(1,0),
            vec2(1,1),

        };
        texCoords={
            {tp[0],tp[3],tp[2],tp[1]},
            {tp[0],tp[3],tp[2],tp[1]},
            {tp[0],tp[3],tp[2],tp[1]},
            {tp[0],tp[3],tp[2],tp[1]},
            {tp[0],tp[3],tp[2],tp[1]},
            {tp[0],tp[3],tp[2],tp[1]},
        };
}
