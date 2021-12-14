//
// Created by husse on 1/18/2021.
//

#ifndef EX56_GATE_H
#define EX56_GATE_H

#include "Vector2D.h"
#include <vector>
#include "glutWindow.h"
using namespace std;


class Gate {
    int gateWidth = 45;
    int gateHeight = 15;
    vector<Vector2D*> verts;
    Vector2D* startingPoint;

public:
    Gate(bool xPlus, Vector2D* startingPoint){
        this->startingPoint = startingPoint;
        for(int i=0; i < 47; i++){
            verts.push_back(new Vector2D(-1, -1));
        }
        if(xPlus){
            verts[37]->x = startingPoint->x - gateWidth ;
            verts[37]->y = startingPoint->y;
            verts[38]->x = startingPoint->x;
            verts[38]->y = startingPoint->y + gateHeight;
            verts[39]->x = startingPoint->x;
            verts[39]->y = startingPoint->y + (gateHeight / 2);
            verts[40]->x = startingPoint->x - (gateWidth / 4);
            verts[40]->y = startingPoint->y;
            verts[41]->x = startingPoint->x - (gateWidth / 2);
            verts[41]->y = startingPoint->y + (gateHeight / 2);
            verts[42]->x = startingPoint->x - (3 * gateWidth / 4);
            verts[42]->y = startingPoint->y;
            verts[43]->x = startingPoint->x - (gateWidth / 4);
            verts[43]->y = startingPoint->y + gateHeight;
            verts[44]->x = startingPoint->x - (gateWidth / 2);
            verts[44]->y = startingPoint->y + (gateHeight / 2);
            verts[45]->x = startingPoint->x - (3 * gateWidth / 4);
            verts[45]->y = startingPoint->y + gateHeight;
            verts[46]->x = startingPoint->x - gateWidth;
            verts[46]->y = startingPoint->y + (gateHeight / 2);

            verts[0]->x = startingPoint->x;
            verts[0]->y = startingPoint->y;
            verts[1]->x = startingPoint->x - gateWidth;
            verts[1]->y = startingPoint->y + gateHeight;
            verts[2]->x = startingPoint->x - (gateWidth / 4);
            verts[2]->y = startingPoint->y + (gateHeight / 2);
            verts[3]->x = startingPoint->x - (gateWidth / 2);
            verts[3]->y = startingPoint->y;
            verts[4]->x = startingPoint->x - (3 * gateWidth / 4);
            verts[4]->y = startingPoint->y + (gateHeight / 2);
            verts[5]->x = startingPoint->x - (gateWidth / 4);
            verts[5]->y = startingPoint->y + (gateHeight / 2);
            verts[6]->x = startingPoint->x - (gateWidth / 2);
            verts[6]->y = startingPoint->y + gateHeight;
            verts[7]->x = startingPoint->x - (3 * gateWidth / 4);
            verts[7]->y = startingPoint->y + (gateHeight / 2);
            verts[8]->x = startingPoint->x - gateWidth;
            verts[8]->y = startingPoint->y + gateHeight;

            verts[9]->x = startingPoint->x;
            verts[9]->y = startingPoint->y + gateHeight;
            verts[10]->x = startingPoint->x;
            verts[10]->y = startingPoint->y + gateHeight + 10;
            verts[11]->x = startingPoint->x - gateWidth; // -1
            verts[11]->y = startingPoint->y + gateHeight;
            verts[12]->x = startingPoint->x - gateWidth; // -1
            verts[12]->y = startingPoint->y + gateHeight + 10;

            verts[13]->x = startingPoint->x;
            verts[13]->y = startingPoint->y + gateHeight + 20;
            verts[14]->x = startingPoint->x;
            verts[14]->y = startingPoint->y + gateHeight + 30;
            verts[15]->x = startingPoint->x - gateWidth;
            verts[15]->y = startingPoint->y + gateHeight + 20;
            verts[16]->x = startingPoint->x - gateWidth;
            verts[16]->y = startingPoint->y + gateHeight + 30;

            verts[17]->x = startingPoint->x;
            verts[17]->y = startingPoint->y + gateHeight + 40;
            verts[18]->x = startingPoint->x;
            verts[18]->y = startingPoint->y + gateHeight + 50;
            verts[19]->x = startingPoint->x - gateWidth;
            verts[19]->y = startingPoint->y + gateHeight + 40;
            verts[20]->x = startingPoint->x - gateWidth;
            verts[20]->y = startingPoint->y + gateHeight + 50;

            verts[21]->x = startingPoint->x;
            verts[21]->y = startingPoint->y + gateHeight + 60;
            verts[22]->x = startingPoint->x;
            verts[22]->y = startingPoint->y + gateHeight + 70;
            verts[23]->x = startingPoint->x - gateWidth;
            verts[23]->y = startingPoint->y + gateHeight + 60;
            verts[24]->x = startingPoint->x - gateWidth;
            verts[24]->y = startingPoint->y + gateHeight + 70;

            verts[25]->x = startingPoint->x;
            verts[25]->y = startingPoint->y + gateHeight + 10;
            verts[26]->x = startingPoint->x;
            verts[26]->y = startingPoint->y + gateHeight + 20;
            verts[27]->x = startingPoint->x - gateWidth;
            verts[27]->y = startingPoint->y + gateHeight + 10;
            verts[28]->x = startingPoint->x - gateWidth;
            verts[28]->y = startingPoint->y + gateHeight + 20;

            verts[29]->x = startingPoint->x;
            verts[29]->y = startingPoint->y + gateHeight + 30;
            verts[30]->x = startingPoint->x;
            verts[30]->y = startingPoint->y + gateHeight + 40;
            verts[31]->x = startingPoint->x - gateWidth;
            verts[31]->y = startingPoint->y + gateHeight + 30;
            verts[32]->x = startingPoint->x - gateWidth;
            verts[32]->y = startingPoint->y + gateHeight + 40;

            verts[33]->x = startingPoint->x;
            verts[33]->y = startingPoint->y + gateHeight + 50;
            verts[34]->x = startingPoint->x;
            verts[34]->y = startingPoint->y + gateHeight + 60;
            verts[35]->x = startingPoint->x - gateWidth;
            verts[35]->y = startingPoint->y + gateHeight + 50;
            verts[36]->x = startingPoint->x - gateWidth;
            verts[36]->y = startingPoint->y + gateHeight + 60;
        }
        else{

            verts[37]->x = startingPoint->x + gateWidth ;
            verts[37]->y = startingPoint->y;
            verts[38]->x = startingPoint->x;
            verts[38]->y = startingPoint->y - gateHeight;
            verts[39]->x = startingPoint->x;
            verts[39]->y = startingPoint->y - (gateHeight / 2);
            verts[40]->x = startingPoint->x + (gateWidth / 4);
            verts[40]->y = startingPoint->y;
            verts[41]->x = startingPoint->x + (gateWidth / 2);
            verts[41]->y = startingPoint->y - (gateHeight / 2);
            verts[42]->x = startingPoint->x + (3 * gateWidth / 4);
            verts[42]->y = startingPoint->y;
            verts[43]->x = startingPoint->x + (gateWidth / 4);
            verts[43]->y = startingPoint->y - gateHeight;
            verts[44]->x = startingPoint->x + (gateWidth / 2);
            verts[44]->y = startingPoint->y - (gateHeight / 2);
            verts[45]->x = startingPoint->x + (3 * gateWidth / 4);
            verts[45]->y = startingPoint->y - gateHeight;
            verts[46]->x = startingPoint->x + gateWidth;
            verts[46]->y = startingPoint->y - (gateHeight / 2);

            verts[0]->x = startingPoint->x;
            verts[0]->y = startingPoint->y;
            verts[1]->x = startingPoint->x + gateWidth;
            verts[1]->y = startingPoint->y - gateHeight;
            verts[2]->x = startingPoint->x + (gateWidth / 4);
            verts[2]->y = startingPoint->y - (gateHeight / 2);
            verts[3]->x = startingPoint->x + (gateWidth / 2);
            verts[3]->y = startingPoint->y;
            verts[4]->x = startingPoint->x + (3 * gateWidth / 4);
            verts[4]->y = startingPoint->y - (gateHeight / 2);
            verts[5]->x = startingPoint->x + (gateWidth / 4);
            verts[5]->y = startingPoint->y - (gateHeight / 2);
            verts[6]->x = startingPoint->x + (gateWidth / 2);
            verts[6]->y = startingPoint->y - gateHeight;
            verts[7]->x = startingPoint->x + (3 * gateWidth / 4);
            verts[7]->y = startingPoint->y - (gateHeight / 2);
            verts[8]->x = startingPoint->x + gateWidth;
            verts[8]->y = startingPoint->y - gateHeight;

            verts[9]->x = startingPoint->x;
            verts[9]->y = startingPoint->y - gateHeight;
            verts[10]->x = startingPoint->x;
            verts[10]->y = startingPoint->y - gateHeight - 10;
            verts[11]->x = startingPoint->x + gateWidth; // -1
            verts[11]->y = startingPoint->y - gateHeight;
            verts[12]->x = startingPoint->x + gateWidth; // -1
            verts[12]->y = startingPoint->y - gateHeight - 10;

            verts[13]->x = startingPoint->x;
            verts[13]->y = startingPoint->y - gateHeight - 20;
            verts[14]->x = startingPoint->x;
            verts[14]->y = startingPoint->y - gateHeight - 30;
            verts[15]->x = startingPoint->x + gateWidth;
            verts[15]->y = startingPoint->y - gateHeight - 20;
            verts[16]->x = startingPoint->x + gateWidth;
            verts[16]->y = startingPoint->y - gateHeight - 30;

            verts[17]->x = startingPoint->x;
            verts[17]->y = startingPoint->y - gateHeight - 40;
            verts[18]->x = startingPoint->x;
            verts[18]->y = startingPoint->y - gateHeight - 50;
            verts[19]->x = startingPoint->x + gateWidth;
            verts[19]->y = startingPoint->y - gateHeight - 40;
            verts[20]->x = startingPoint->x + gateWidth;
            verts[20]->y = startingPoint->y - gateHeight - 50;

            verts[21]->x = startingPoint->x;
            verts[21]->y = startingPoint->y - gateHeight - 60;
            verts[22]->x = startingPoint->x;
            verts[22]->y = startingPoint->y - gateHeight - 70;
            verts[23]->x = startingPoint->x + gateWidth;
            verts[23]->y = startingPoint->y - gateHeight - 60;
            verts[24]->x = startingPoint->x + gateWidth;
            verts[24]->y = startingPoint->y - gateHeight - 70;

            verts[25]->x = startingPoint->x;
            verts[25]->y = startingPoint->y - gateHeight - 10;
            verts[26]->x = startingPoint->x;
            verts[26]->y = startingPoint->y - gateHeight - 20;
            verts[27]->x = startingPoint->x + gateWidth;
            verts[27]->y = startingPoint->y - gateHeight - 10;
            verts[28]->x = startingPoint->x + gateWidth;
            verts[28]->y = startingPoint->y - gateHeight - 20;

            verts[29]->x = startingPoint->x;
            verts[29]->y = startingPoint->y - gateHeight - 30;
            verts[30]->x = startingPoint->x;
            verts[30]->y = startingPoint->y - gateHeight - 40;
            verts[31]->x = startingPoint->x + gateWidth;
            verts[31]->y = startingPoint->y - gateHeight - 30;
            verts[32]->x = startingPoint->x + gateWidth;
            verts[32]->y = startingPoint->y - gateHeight - 40;

            verts[33]->x = startingPoint->x;
            verts[33]->y = startingPoint->y - gateHeight - 50;
            verts[34]->x = startingPoint->x;
            verts[34]->y = startingPoint->y - gateHeight - 60;
            verts[35]->x = startingPoint->x + gateWidth;
            verts[35]->y = startingPoint->y - gateHeight - 50;
            verts[36]->x = startingPoint->x + gateWidth;
            verts[36]->y = startingPoint->y - gateHeight - 60;
        }
    }

    void drawGate(){
        glColor3f(1.0, 1.0, 1.0);

        glBegin(GL_POLYGON);
        glVertex2d(verts[0]->x, verts[0]->y);
        glVertex2d(verts[37]->x, verts[37]->y);
        glVertex2d(verts[1]->x, verts[1]->y);
        glVertex2d(verts[38]->x, verts[38]->y);
        glEnd();

        glColor3f(0.0, 0.0, 0.0);

        glBegin(GL_POLYGON);
        glVertex2d(verts[0]->x, verts[0]->y); // 0
        glVertex2d(verts[39]->x, verts[39]->y);
        glVertex2d(verts[2]->x, verts[2]->y); // 2
        glVertex2d(verts[40]->x, verts[40]->y);
        glEnd();

        glBegin(GL_POLYGON);
        glVertex2d(verts[3]->x, verts[3]->y); // 3
        glVertex2d(verts[41]->x, verts[41]->y);
        glVertex2d(verts[4]->x, verts[4]->y); // 4
        glVertex2d(verts[42]->x, verts[42]->y);
        glEnd();

        glBegin(GL_POLYGON);
        glVertex2d(verts[5]->x, verts[5]->y); // 5
        glVertex2d(verts[43]->x, verts[43]->y);
        glVertex2d(verts[6]->x, verts[6]->y); // 6
        glVertex2d(verts[44]->x, verts[44]->y);
        glEnd();

        glBegin(GL_POLYGON);
        glVertex2d(verts[7]->x, verts[7]->y); // 7
        glVertex2d(verts[45]->x, verts[45]->y);
        glVertex2d(verts[8]->x, verts[8]->y); // 8
        glVertex2d(verts[46]->x, verts[46]->y);
        glEnd();

        glBegin(GL_LINES);
        glLineWidth(10.0);
        glVertex2d(verts[9]->x, verts[9]->y);
        glVertex2d(verts[10]->x, verts[10]->y);
        glEnd();
        glBegin(GL_LINES);
        glLineWidth(10.0);
        glVertex2d(verts[11]->x, verts[11]->y);
        glVertex2d(verts[12]->x, verts[12]->y);
        glEnd();

        glBegin(GL_LINES);
        glLineWidth(10.0);
        glVertex2d(verts[13]->x, verts[13]->y);
        glVertex2d(verts[14]->x, verts[14]->y);
        glEnd();
        glBegin(GL_LINES);
        glLineWidth(10.0);
        glVertex2d(verts[15]->x, verts[15]->y);
        glVertex2d(verts[16]->x, verts[16]->y);
        glEnd();

        glBegin(GL_LINES);
        glLineWidth(10.0);
        glVertex2d(verts[17]->x, verts[17]->y);
        glVertex2d(verts[18]->x, verts[18]->y);
        glEnd();
        glBegin(GL_LINES);
        glLineWidth(10.0);
        glVertex2d(verts[19]->x, verts[19]->y);
        glVertex2d(verts[20]->x, verts[20]->y);
        glEnd();

        glBegin(GL_LINES);
        glLineWidth(10.0);
        glVertex2d(verts[21]->x, verts[21]->y);
        glVertex2d(verts[22]->x, verts[22]->y);
        glEnd();
        glBegin(GL_LINES);
        glLineWidth(10.0);
        glVertex2d(verts[23]->x, verts[23]->y);
        glVertex2d(verts[24]->x, verts[24]->y);
        glEnd();


        glColor3f(1.0, 1.0, 1.0);

        glBegin(GL_LINES);
        glLineWidth(10.0);
        glVertex2d(verts[25]->x, verts[25]->y);
        glVertex2d(verts[26]->x, verts[26]->y);
        glEnd();
        glBegin(GL_LINES);
        glLineWidth(10.0);
        glVertex2d(verts[27]->x, verts[27]->y);
        glVertex2d(verts[28]->x, verts[28]->y);
        glEnd();

        glBegin(GL_LINES);
        glLineWidth(10.0);
        glVertex2d(verts[29]->x, verts[29]->y);
        glVertex2d(verts[30]->x, verts[30]->y);
        glEnd();
        glBegin(GL_LINES);
        glLineWidth(10.0);
        glVertex2d(verts[31]->x, verts[31]->y);
        glVertex2d(verts[32]->x, verts[32]->y);
        glEnd();

        glBegin(GL_LINES);
        glLineWidth(10.0);
        glVertex2d(verts[33]->x, verts[33]->y);
        glVertex2d(verts[34]->x, verts[34]->y);
        glEnd();
        glBegin(GL_LINES);
        glLineWidth(10.0);
        glVertex2d(verts[35]->x, verts[35]->y);
        glVertex2d(verts[36]->x, verts[36]->y);
        glEnd();
    }

    void rotation(GLdouble theta) {
        vector<Vector2D*> vertsRot;
        for(int i=0; i < verts.size(); i++){
            vertsRot.push_back(new Vector2D(-1, -1));
        }
        GLint k;
        for (k = 0; k < verts.size(); k++) {
            vertsRot[k]->x = startingPoint->x + (verts[k]->x - startingPoint->x) * cos(theta) - (verts[k]->y - startingPoint->y) * sin(theta);
            vertsRot[k]->y = startingPoint->y + (verts[k]->x - startingPoint->x) * sin(theta) + (verts[k]->y - startingPoint->y) * cos(theta);
            verts[k] = vertsRot[k];
        }
        drawGate();
    }
};


#endif //EX56_GATE_H
