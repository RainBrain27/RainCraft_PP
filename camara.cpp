#include "camara.h"
#include <cmath>

camara::camara()
{
    BG = skycube(400,glm::vec4(0,0,0,1));
}

camara::~camara()
{

}

void camara::spin(float wa, float wb, float wc)
{
    wx+=wa;
    wy+=wb;
    wz+=wc;
}

void camara::move(float a, float b, float c)
{
    float x1=std::cos(wy*(M_PI/180))*a - std::sin(wy*(M_PI/180))*c; //use glm pi
    float z1=std::sin(wy*(M_PI/180))*a + std::cos(wy*(M_PI/180))*c;
    x+=x1;
    z+=z1;
    BG.move(glm::vec4(-x1,-b,-z1,0));
    y+=b;
}

void camara::set_pos(float Nx, float Ny, float Nz)
{
    x=Nx;
    y=Ny;
    z=Nz;
}

void camara::set_fov(int Nfov)
{
    FOV=Nfov;
}

void camara::set_aspectratio(double Naspectratio)
{
    aspectratio=Naspectratio;
}

void camara::setCamProjection()
{
    //glMatrixMode(GL_PROJECTION);
    //glLoadIdentity();
    //gluPerspective(60, aspectratio,0.5,1000);

    //glRotatef(rotation, 0.0, 1.0, 0.0);
    //use rotation Matrix and rotate everything at once(Laufzeit)
    //glRotatef(wx, 1.0, 0.0, 0.0);
    //glRotatef(wy, 0.0, 1.0, 0.0);
    //glRotatef(wz, 0.0, 0.0, 1.0);

    //glTranslatef(0.0f+x, 0.0f+y, -20.0f+z); // place at cam position
}
