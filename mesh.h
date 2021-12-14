//
// Created by husse on 11/30/2020.
//

#ifndef EX59FINAL_MESH_H
#define EX59FINAL_MESH_H
#include "Triangle.h"
#include "Vector2D.h"
#include "Vector2DD.h"
#include "Edge.h"
#include "car.h"
#include "door.h"
#include "Polygon.h"
#include "Curves.h"
#include <vector>
#include <limits>

class Mesh {
private:
    std::vector<Vector2D*> vertices;
    std::vector<Triangle*> triangles;
    std::vector<Edge*> edges;
    std::vector<class::Polygon*> polygons;
    std::vector<pair<car*, bool>> cars;
    int TimeCounterForSlowMotion = 50;
    bool startMoving = false;
    bool firstTime = true, firstt = true;
    int currentPolygonId = 0;
    int currentPolygonIdCarOn = 0;
    int currentMovingCarId = 0, oldMovingCarId = 0;
    vector<pair<Vector2D*, double>> endingPoint;
    Curves* curves;
    bool isWalking = false;
    bool isDone = true  ;
    std::vector<std::vector<int>> connectionGraph = {
            {0,0,0,0,1,0,0,0,0,0}, //okay
            {1,0,0,1,0,0,0,0,0,0}, //okay
            {0,1,0,0,0,0,0,0,1,0}, //okay
            {0,1,0,0,0,0,0,1,0,0}, //okay
            {0,0,0,1,0,1,0,0,0,0}, //okay
            {0,0,0,0,1,0,1,0,0,0}, //okay
            {0,0,0,0,0,1,0,1,0,0}, //okay
            {0,0,1,0,0,0,1,0,0,0}, //okay
            {0,0,1,0,0,0,0,0,0,1}, //okay
            {0,0,0,0,0,0,0,0,1,0} //okay
    };
    vector<vector<pair<Vector2D*, double>>> connectionGraphWithPositions;
public:
    void onMouseDown(double cx,double cy);
    Mesh(const float p_vert[][2], int p_nvert, const int p_tri[][3], int p_ntri);

    Mesh(const float p_vert[][2], int p_nvert);

    ~Mesh();

    void onStart();

    void draw();

    void MoveCars();

    void onMouseMove(double cx, double cy);

    int getTriangle(double cx, double cy);

    void ChangeOrientation(int i);

    int IsTriangleOrientedClockwise(Vector2D* p1, Vector2D* p2, Vector2D* p3);

    void OrientTrianglesClockwise();

    void flipEdge(Vector2D *p1, Vector2D* p2, Vector2D* p3, Vector2D *p4, int mainIndex, int i);

//    void onMouseDown(double cx, double cy);

    void Delaunay();

    Vector2D* findCentroid(std::vector<Triangle*> T);

    bool comparePoints(Vector2D* p1, Vector2D* p2, Vector2D* center);

    double getClockwiseAngle(Vector2D* p, Vector2D* center);

    void  Voronoi();

    int findPolygonIdByColor(string color);

    int getIdOfTheCar(car* car);

    void  changeCoordinates();

//    void VoronoiEdges();

    bool almost_equal(Edge e1, Edge e2)
    {
        return	(almost_equal(*e1.v, *e2.v) && almost_equal(*e1.w, *e2.w)) || (almost_equal(*e1.v, *e2.w) && almost_equal(*e1.w, *e2.v));
    }

    bool almost_equal(const Vector2D v1, const Vector2D v2)
    {
        return almost_equal(v1.x, v2.x) && almost_equal(v1.y, v2.y);
    }

    bool almost_equal(double x, double y, int ulp = 2)
    {
        return fabsf(x - y) <= std::numeric_limits<float>::epsilon() * fabsf(x + y) * static_cast<float>(ulp) || fabsf(x - y) < std::numeric_limits<float>::min();
    }
};
#endif //EX59FINAL_MESH_H
