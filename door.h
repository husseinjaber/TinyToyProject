//
// Created by kniku on 09/01/2021.
//

#ifndef TINYCARS_DOOR_H
#define TINYCARS_DOOR_H
#include "Vector2DD.h"
#include "glutWindow.h"
#include "constants.h"
#include <iostream>

class door {
public:
    GLuint texture;
    int x,y;
    Vector2DD position;
    Vector2DD orientation;
    double rot;

    door(int a,int b){
        texture=0;
        x=a;
        y=b;
        position.x=a;
        position.y=b;
    }

    door(){
        texture=0;
        x=500;
        y=500;
        rot=30;
        position.x=x;
        position.y=y;

        orientation.x=x+50;
        orientation.y=y+50;
    }

    void draw(){

        int lx,ly;
        texture = GlutWindow::loadTGATexture("../Textures/carstop.tga",lx,ly);
        assert(texture!=0);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D,texture);
        glPushMatrix();
        glTranslatef(position.x, position.y, 1.0);
        double angle = atan2(orientation.y - position.y, orientation.x - position.x) * 180 / PI;

        glRotatef(angle, 0, 0, 1);
        glBegin(GL_QUADS);
        glTexCoord2f(0.0, 0.0);
        glVertex2f(0.0, 0.0);

        glTexCoord2f(1.0, 0.0);
        glVertex2f(parkwidth * 2, 0.0);

        glTexCoord2f(1.0, 1.0);
        glVertex2f(parkwidth * 2, parkheight * 2);

        glTexCoord2f(0.0, 1.0);
        glVertex2f(0.0, parkheight * 2);
        glEnd();
        glPopMatrix();
        glDisable(GL_TEXTURE_2D);

    }

    virtual ~door() {

    }
};


#endif //TINYCARS_DOOR_H
