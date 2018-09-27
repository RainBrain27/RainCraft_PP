#ifndef CAMARA_H
#define CAMARA_H

#include <skycube.h>

class camara
{
public:
    camara();
    ~camara();

    void spin(float wa,float wb,float wc);
    void move(float a,float b,float c);
    void set_pos(float Nx,float Ny,float Nz);
    void set_fov(int Nfov);
    void set_aspectratio(double Naspectratio);
    void setCamProjection();

    float get_wx(){return wx;}
    float get_wy(){return wy;}
    float get_wz(){return wz;}

    float get_cf(){return clipping_front;}
    float get_cb(){return clipping_back;}

    float get_aspectratio(){return aspectratio;}
    int get_FOV(){return FOV;}

    float get_x(){return x;}
    float get_y(){return y;}
    float get_z(){return z;}

    BaseObject *get_BG(){return &BG;}

private:
    int FOV=60;
    float aspectratio=1;
    float clipping_front=0.5;
    float clipping_back=10000;

    float wx=0;
    float wy=0; //pitch/yaw/roll
    float wz=0;

    float x=0;
    float y=0;
    float z=-15;

    skycube BG;

};

#endif // CAMARA_H
