//
// Created by kniku on 04/01/2021.
//

#ifndef TINYCARS_CAR_H
#define TINYCARS_CAR_H
#include "Vector2DD.h"
#include "glutWindow.h"
#include <iostream>

#include "door.h"
#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include "vector"

using namespace std;



class car {

public:
    GLuint texture;
    Vector2DD position;
    Vector2DD orientation;
    int x=100;int y=100;
    Vector2DD p1;
    Vector2DD v1;
    Vector2DD from;
    string color;
    double angle;

    double t;
    double epsilon=0.01;
    vector<Vector2DD> curve_points;
    vector<Vector2DD> LinePath_points;
    vector<Vector2DD> curve_orientations;
    bool toDraw=true;
    int timeHere = 100;
    int index = 0;

    car(int a,int b){
        texture=0;
        x=a;
        y=b;
        position.x=a;
        position.y=b;

    }

    car(int a,int b,string color){
        texture=0;
        x=a;
        y=b;
        position.x=a;
        position.y=b;
        this->color = color;
    }

    car(){
        texture=0;
        x=900;y=500;
        position.x=x;position.y=y;
        orientation.x=x+0;orientation.y=y+0;
    }

    Vector2DD traj(float  t){
        Vector2DD a=2*(from-p1)+orientation+v1;
        Vector2DD b=3*(p1-from)-2*orientation-v1;
        Vector2DD c=orientation;
        Vector2DD d=from;
        cout <<"in traj -------------- x: " << ((t*(3*t*a+2*b))+c).x << "or y: "<<  ((t*(3*t*a+2*b))+c).y <<endl;
        orientation=((t*(3*t*a+2*b))+c);
        curve_orientations.push_back((t*(3*t*a+2*b))+c);
        return t*((t*(t*a+b))+c)+d;
    }


    vector<Vector2DD> drwcurve(){
        cout << "click1" <<endl;
        move(10,10);
        return curve_points;
    }

    void  move( double  dt ,  float  velocity ){

        Vector2DD Pi= traj(t),Pj ;
        curve_points.push_back( Vector2DD(Pi.x,Pi.y));

        double d=dt*velocity ;
        while  (d>0.0 && t<1.0){
            t+=epsilon ;
            Pj = traj(t) ;
            d-=( Pj-Pi ).norm() ;
            Pi=Pj ;
            cout <<"pos x: " << Pi.x << "pos y: "<<  Pi.y <<endl;

            curve_points.push_back( Vector2DD(Pi.x,Pi.y));
        }

    }

    void curve(Vector2DD d,Vector2DD orien,Vector2DD From){
        curve_points.clear();
        p1=d;
        v1 = orien;
        from = From;
        move(10,1000);
    }

    vector<Vector2DD> LinePath(Vector2DD d,Vector2DD midPoint,Vector2DD From, int count){
        count = count+1;
        LinePath_points.clear();
//        LinePath_points.push_back(Vector2DD(From.x,From.y));
////        LinePath_points.push_back(Vector2DD(midPoint.x,midPoint.y));
//        LinePath_points.push_back(Vector2DD(d.x,d.y));

        //from mid
        double dd = sqrt((From.x - midPoint.x) * (From.x - midPoint.x) + (From.y- midPoint.y) * (From.y - midPoint.y)) / count;
        double fi = atan2(midPoint.y - From.y, midPoint.x - From.x);

        for (int i = 0; i <= count; ++i)
            LinePath_points.push_back(Vector2DD(From.x + i * dd * cos(fi), From.y + i * dd * sin(fi)));

        // mid from
        double dd2 = sqrt((midPoint.x - d.x) * (midPoint.x - d.x) + (midPoint.y- d.y) * (midPoint.y - d.y)) / count;
        double fi2 = atan2(d.y - midPoint.y, d.x - midPoint.x);

        for (int i = 0; i <= count; ++i)
            LinePath_points.push_back(Vector2DD(midPoint.x + i * dd2 * cos(fi2), midPoint.y + i * dd2 * sin(fi2)));

       return LinePath_points;
    }



    void curvedr(){
        glBegin(GL_LINE_STRIP);
        auto current = curve_points.begin();
        while (current != curve_points.end()){
            glVertex2f(current->x,current->y);
            current++;
        }
        glEnd();
    }

    void go(){

        /*   auto current = curve_points.begin();
            auto current_orienration=curve_orientations.begin();
            while (current != curve_points.end()){

                x=current->x;y=current->y;
                position.x=current->x;position.y=current->y;
                orientation.x=current_orienration->x;orientation.y=current_orienration->y;
                //sleep(1)
                //cout << (orientation-position).norm() <<endl;
                //switch_draw();
               // draw();
                current++;
                current_orienration++;
            }*/

        //    for(int i = 0; i< curve_points.size();i++){
        if(index<curve_points.size()){
            cout <<index << "  x:" << curve_points[index].x << "   y: "<<curve_points[index].y <<endl;
            position.x=curve_points[index].x;
            position.y=curve_points[index].y;
            //  orientation.x=curve_orientations[index].x;orientation.y=curve_orientations[index].y;
            cout<< " pos x " <<position.x << " pos x "  << position.y <<  " or x "
                << orientation.x<< " or y "  <<orientation.y <<endl;


            //     sleep(0.1);
            //draww();

            index = index +1;
        }
    }


//    void switch_draw(){
//       // while (1){
//            sleep(2);
//            toDraw=!toDraw;
//      //  }
//    }

    void draw(){
        //sleep(1);

        if(timeHere % 100 == 0) {
            // cout
            go();
        }
//        int lx, ly;
//        texture = GlutWindow::loadTGATexture("../Textures/orangecar.tga", lx, ly);
//        assert(texture != 0);
//
//
//        glEnable(GL_BLEND);
//        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//        glEnable(GL_TEXTURE_2D);
//
//        glBindTexture(GL_TEXTURE_2D, texture);
//        glPushMatrix();
//        glTranslatef(position.x, position.y, 1.0);
//        double angle = atan2(orientation.y - position.y, orientation.x - position.x) * 180 / PI;
//
//        glRotatef(angle, 0, 0, 1);
//        glBegin(GL_QUADS);
//
//        glTexCoord2f(0.0, 0.0);
//        glVertex2f(0.0, 0.0);
//
//        glTexCoord2f(1.0, 0.0);
//        glVertex2f(carwidth * 2, 0.0);
//
//        glTexCoord2f(1.0, 1.0);
//        glVertex2f(carwidth * 2, carheight * 2);
//
//        glTexCoord2f(0.0, 1.0);
//        glVertex2f(0.0, carheight * 2);
//
//        glEnd();
//        glPopMatrix();
//        glDisable(GL_TEXTURE_2D);


        if(index<curve_points.size()){
            timeHere = timeHere +100;
        }

    }

    virtual ~car() {

    }


};


#endif //TINYCARS_CAR_H
