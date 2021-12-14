#ifndef POLYGON_H
#define POLYGON_H
#include "Vector2D.h"
#include<iostream>
#include <vector>
#include <GL/glut.h>
#include <string>
#include <math.h>
#include "Edge.h"
#include "Gate.h"
#include "car.h"
#include "glutWindow.h"
#include <vector>
using namespace std;
#define M_PI           3.14159265358979323846  /* pi */
class Polygon {
public:
    std::vector<Vector2D*> points;
    string colorName;
    Vector2D* centerOfPolygon;
    std::vector<double> color;
    Vector2D* vertice;
    std::vector<pair<Vector2D*, double>> parkingSpots;
    std::vector<car*> carsList;
    GLuint parking, carTexture;
    int id;
    int numberOfCars;
    double area = 0;
    std::string name;
    bool isOpened;



    void addPoint(Vector2D* p);

    void addCornerPoints(int x0, int y0, int x1, int y1);

    bool isInsidePoints(Vector2D* p);

    Vector2D* findCentroid();

    void sortPointsCounterClockwise();

    bool comparePoints(Vector2D* p1, Vector2D* p2);

    Vector2D* findCentroidParkingSpots();

    void sortParkingSpotsCounterClockwise();

    double getPolygonSurface();

    void setNumberOfCars(double min);

//    bool comparePoints(Vector2D* p1, Vector2D* p2);

    void displayPoints();

    void displayParkingSpots();

    vector<pair<car*, bool>> drawCars(vector<pair<car*, bool>> cars,bool first);

    void dislayPolygon();

    vector<pair<Vector2D*, double>> drawGates(vector<class::Polygon*> polygons, vector<vector<int>> connectionGraph);

    void drawParkings(vector<class::Polygon*> polygons, vector<vector<int>> connectionGraph);
};

#endif //POLYGON_H
