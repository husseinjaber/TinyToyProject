#include "Edge.h"

Edge::Edge(Vector2D* v1, Vector2D* v2) {
	v = v1;
	w = v2;
}

bool Edge::operator ==(Edge e) {
	return (*(this->v) == *e.v && *(this->w) == *e.w) || (*(this->v) == *e.w && *(this->w) == *e.v);
}