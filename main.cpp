#include <iostream>
#include <cstdlib>
#include <vector>
#include <array>
#include "glutWindow.h"
#include "Triangle.h"
#include "mesh.h"

using namespace std;
//car c;
//door d;

class PolygonDraw: public GlutWindow {
private:
    Mesh *mesh;
public:

    PolygonDraw(const string &title,int argc,char **argv):GlutWindow(argc,argv,title,1280,840,FIXED) {

    };

    void onStart() override;
    void onDraw() override;
    void onQuit() override;
    void onMouseMove(double cx,double cy) override;
    void onMouseDown(int button,double cx,double cy) override;
    void onKeyPressed(unsigned char c,double x,double y) override;
};

void PolygonDraw::onStart() {
    glClearColor(1.0,1.0,1.0,1.0); // background color
//    float tabVect[][2]={{280,740},{700,750},{500,700},{900,720},{50,410},{340,400},
//                        {650,390},{950,300},{400,200},{550,190},{200,50},{800,100}};
//    int tabTri[][3]={{0,2,1},{0,4,2},{1,6,3},{2,5,8},{2,6,1},{2,8,6},{3,6,11},{3,11,7},
//                     {4,5,2},{4,8,5},{4,10,8},{6,8,9},{6,9,11},{8,10,9},{9,10,11}};
    float tabVect[][2]={{110,450},{400,700},{1100,720},{510,470},{370,120},{680,40},
                        {670,230},{900,280},{1140,350},{970,80}};
    // do this for the flip on click
//    mesh = new Mesh(tabVect,12,tabTri,15);

    // do this for Delaunay Mesh 
    mesh = new Mesh(tabVect, 10);
    mesh->Voronoi();
//    int i = 0;
//    for(auto p : polygons){
//        cout << "Polygon " << i << endl;
//        p->displayPoints();
//    }
//    cout << "----------------------------------" << endl;
}

void PolygonDraw::onDraw() {
    // draw the referential
    glPushMatrix();
    glTranslatef(10,10,0);
    glColor3fv(RED);
    glBegin(GL_QUADS);
    glVertex2f(0.0,-2.0);
    glVertex2f(100.0,-2.0);
    glVertex2f(100.0,2.0);
    glVertex2f(0.0,2.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex2f(110.0,0.0);
    glVertex2f(90.0,-10.0);
    glVertex2f(90.0,10.0);
    glEnd();
    glColor3fv(GREEN);
    glBegin(GL_QUADS);
    glVertex2f(-2.0,0.0);
    glVertex2f(2.0,0.0);
    glVertex2f(2.0,100.0);
    glVertex2f(-2.0,100.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex2f(0.0,110.0);
    glVertex2f(-10.0,90.0);
    glVertex2f(10.0,90.0);
    glEnd();
    glPopMatrix();

    mesh->draw();

//    c.curve(d);
//    c.curvedr();
//
//    d.draw();
//    c.draw();
}

void PolygonDraw::onQuit() {

}

void PolygonDraw::onMouseMove(double cx, double cy) {
    mesh->onMouseMove(cx,cy);
}

void PolygonDraw::onMouseDown(int button, double cx, double cy) {
    mesh->onMouseDown(cx, cy);
}

void PolygonDraw::onKeyPressed(unsigned char c, double x, double y) {
}

int main(int argc,char **argv) {
    PolygonDraw win("Triangulation", argc,argv);
    win.start();

    return 0;
}

//Vector2D operator*(float a, const Vector2D &v){
//    return Vector2D(a*v.x, a*v.y);
//}

//bool operator==(const Vector2D &u, const Vector2D &v){
//    return (u.x==v.x && u.y==v.y);
//}