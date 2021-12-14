//
// Created by bpiranda on 22/11/2019.
//

#ifndef VECTOR2DD_H
#define VECTOR2DD_H
#include <cmath>
using namespace std;

class Vector2DD {
public :
    float x,y;
    Vector2DD():x(0),y(0) {};
    Vector2DD(const Vector2DD &v) {x=v.x; y=v.y; }
    Vector2DD(float p_x,float p_y):x(p_x),y(p_y) {};
    Vector2DD operator-(const Vector2DD &op2) const {
        return Vector2DD(x - op2.x, y - op2.y);
    }
    Vector2DD operator+(const Vector2DD &op2) const {
        return Vector2DD(x + op2.x, y + op2.y);
    }
    float operator*(const Vector2DD &op2) const {
        return x*op2.x+y*op2.y;
    }
    void set(float p_x,float p_y) {
        x=p_x;
        y=p_y;
    }
    void normalize() {
        float norm=sqrt(x*x+y*y);
        x/=norm;
        y/=norm;
    }
    double norm() {
        return sqrt(x*x+y*y);
    }
    Vector2DD ortho() {
        return Vector2DD(-y,x);
    }
    friend const Vector2DD operator*(float a,const Vector2DD &v)  {
        return Vector2DD(a*v.x,a*v.y);
    }

    friend const Vector2DD operator-(float a,const Vector2DD &v)  {
        return Vector2DD(a-v.x,a-v.y);
    }
    friend const Vector2DD operator+(float a,const Vector2DD &v)  {
        return Vector2DD(a+v.x,a+v.y);
    }
    friend bool operator==(const Vector2DD &u,const Vector2DD &v){
        return (u.x==v.x && u.y==v.y);
    }

};

#endif //VECTOR2D_H
