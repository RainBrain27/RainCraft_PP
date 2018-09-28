#ifndef BASEOBJECT_H
#define BASEOBJECT_H

#include <glm.hpp>
#include <vector>
#include <c++/cstddef>

typedef glm::vec4 PPoint;
typedef std::vector<PPoint> PointList;

typedef std::vector<size_t> PPolygon;
typedef std::vector<PPolygon> PolygonList;

typedef glm::vec2 TexCoord;
typedef std::vector<TexCoord> TTexCoord;
typedef std::vector<TTexCoord> TexCoordList;

typedef std::vector<int> TexNumList;

class BaseObject
{
public:
    BaseObject();

    void move(glm::vec4 dirvec);
    void moveTo(glm::vec4 destvec);

protected:
    void Orotate(glm::vec3 deg1, glm::vec3 deg2); //solve with vec4
    void OrotateTo(glm::vec3 deg1, glm::vec3 deg2);
    void Orotate2(glm::vec3 deg1);
    glm::vec3 Oget_angle(glm::vec4 DP);


public:
    void setPointList(PointList l)
        {points = l;}
    void setPolygonList(PolygonList l,TexCoordList t)
        {polygons = l;texCoords=t;}
    void setTexNumList(TexNumList t)
        {texNums=t;}
    void setCoordList(TexCoordList t)
        {texCoords=t;}
    void setColor(glm::vec4 c)
        {color = c;}
    void setColor(float r, float g, float b, float a = 1)
        {color = glm::vec4(r,g,b,a);}
    void setCenter(glm::vec4 c)
        {center = c;}
    void refreshPolygonPointCounter();

public:
    const PointList       *getPointList()      const {return &points;}
    const PolygonList     *getPolygonList()    const {return &polygons;}
    const TexNumList      *getTexNumList()     const {return &texNums;}
    const TexCoordList    *getTexCoordList()   const {return &texCoords;}
    const glm::vec4       *getColor()          const {return &color;}
    const glm::vec4       *getCenter()         const {return &center;}
    size_t                 getPolygonCount()   const {return polCount;}
    size_t                 getPointCount()     const {return poiCount;}
protected:
    PointList points;
    PolygonList polygons;
    TexNumList texNums;
    TexCoordList texCoords;
    bool visible = true;
    glm::vec4 color = glm::vec4(1,1,1,1);
    PPoint center = glm::vec4(0,0,0,1);
    glm::vec3 angle;
    size_t polCount=0, poiCount=0;
};

#endif // BASEOBJECT_H
