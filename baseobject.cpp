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

glm::vec3 BaseObject::Oget_angle(glm::vec4 DP)
{
    center=mzyx*center
}

void BaseObject::Orotate(glm::vec3 deg1, glm::vec3 deg2)
{
    OrotateTo(deg1,deg1+deg2);
}

void BaseObject::OrotateTo(glm::vec3 deg1, glm::vec3 deg2)
{
    Orotate2(deg1);

    //angle+=deg; //use qmat insted of glm?
    glm::mat4 mx = glm::rotate(glm::radians(deg2.x),glm::vec3(1,0,0));
    glm::mat4 mxy = glm::rotate(mx,glm::radians(deg2.y),glm::vec3(0,1,0));       //optimierbar 1. achsen ,2. in einem Zug
    glm::mat4 mxyz = glm::rotate(mxy,glm::radians(deg2.z),glm::vec3(0,0,1));

    for(PPoint &p: points){
        p=mxyz*p;
    }
    center=mxyz*center;
}

void BaseObject::Orotate2(glm::vec3 deg1)
{
    glm::mat4 mz = glm::rotate(glm::radians(-deg1.z),glm::vec3(0,0,1));
    glm::mat4 mzy = glm::rotate(mz,glm::radians(-deg1.y),glm::vec3(0,1,0));       //optimierbar 1. achsen ,2. in einem Zug
    glm::mat4 mzyx = glm::rotate(mzy,glm::radians(-deg1.x),glm::vec3(1,0,0));

    for(PPoint &p: points){
        p=mzyx*p;
    }
    center=mzyx*center;
}

void BaseObject::refreshPolygonPointCounter()
{
    polCount = polygons.size();
    poiCount = 0;
    for(PPolygon &p:polygons){
        poiCount+=p.size();
    }
}
