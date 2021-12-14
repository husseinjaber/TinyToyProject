#ifndef EDGE_H
#define EDGE_H
#include "Vector2D.h"
#include <vector>
#include <GL/glut.h>
#include <string>

class Edge {
public:
    Vector2D* v;
    Vector2D* w;
    bool isBad = false;

    Edge(Vector2D* v1, Vector2D* v2);

    bool operator ==(Edge e);

    //std::string std::ostream& operator <<(std::string str, Edge* e);
};

#endif //EDGE_H
