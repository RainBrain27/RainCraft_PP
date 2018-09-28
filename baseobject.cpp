#include "baseobject.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <gtx/transform.hpp>

BaseObject::BaseObject()
{

}

void BaseObject::move(glm::vec4 dirvec)
{
    if(dirvec.w==0){
        for(PPoint &pt:points){
            pt+=dirvec;
        }
        center+=dirvec;
    }
}

void BaseObject::moveTo(glm::vec4 destvec)
{
    move(destvec-center);
}

void BaseObject::rotate(glm::vec3 deg1, glm::vec3 deg2 ,glm::vec4 DP) //deg=pitch/yaw/roll DP=Drehpunkt
{
    rotate2();

    angle+=deg; //use qmat insted of glm?
    glm::mat4 mx = glm::rotate(glm::radians(angle.x),glm::vec3(1,0,0));
    glm::mat4 mxy = glm::rotate(mx,glm::radians(angle.y),glm::vec3(0,1,0));       //optimierbar 1. achsen ,2. in einem Zug
    glm::mat4 mxyz = glm::rotate(mxy,glm::radians(angle.z),glm::vec3(0,0,1));

    for(PPoint &p: points){
        p=mxyz*p;
    }
    center=mxyz*center;
}

void BaseObject::rotate2()
{
    glm::mat4 mz = glm::rotate(glm::radians(-angle.z),glm::vec3(0,0,1));
    glm::mat4 mzy = glm::rotate(mz,glm::radians(-angle.y),glm::vec3(0,1,0));       //optimierbar 1. achsen ,2. in einem Zug
    glm::mat4 mzyx = glm::rotate(mzy,glm::radians(-angle.x),glm::vec3(1,0,0));

    for(PPoint &p: points){
        p=mzyx*p;
    }
    center=mzyx*center;
}

void BaseObject::spin(glm::vec3 deg)
{
    glm::vec4 center_save = center;
    moveTo(glm::vec4(0,0,0,1));


    moveTo()
}

void BaseObject::refreshPolygonPointCounter()
{
    polCount = polygons.size();
    poiCount = 0;
    for(PPolygon &p:polygons){
        poiCount+=p.size();
    }
}
