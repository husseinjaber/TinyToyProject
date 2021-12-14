//
// Created by husse on 11/30/2020.
//

#include "mesh.h"
#include "glutWindow.h"
#include <algorithm>

// Constructor for flip on click
Mesh::Mesh(const float p_vert[][2], int p_nvert, const int p_tri[][3],int p_ntri){
    for(int i=0;i<p_nvert;i++){
        vertices.push_back(new Vector2D(p_vert[i][0], p_vert[i][1]));
    }
    for(int i=0;i<p_ntri;i++){
        triangles.push_back(new Triangle(vertices[p_tri[i][0]], vertices[p_tri[i][1]], vertices[p_tri[i][2]]));
        triangles[i]->checkDelauney(vertices);
    }
}

// Constructor for Delaunay
Mesh::Mesh(const float p_vert[][2], int p_nvert) {
    for (int i = 0; i < p_nvert; i++) {
        vertices.push_back(new Vector2D(p_vert[i][0], p_vert[i][1]));
    }
    Delaunay();
    OrientTrianglesClockwise();
//    MoveCars();
}

Mesh::~Mesh(){
    triangles.clear();
    vertices.clear();
}

void Mesh::onStart(){
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//    MoveCars();
}

void Mesh::draw(){
//    cars.clear();
//    changeCoordinates();
//cout << "draw------------"<<endl;
    for (auto t : triangles) {
        t->checkDelauney(vertices);
        t->draw();
    }
    for(auto t:triangles) {
        t->drawCircle();
        t->drawCenter();
    }
    int n=0;
    for(auto p:vertices)
        GlutWindow::drawText(p->x-10,p->y-10,to_string(n++), GlutWindow::ALIGN_CENTER);

    for (auto p : polygons) {
        p->dislayPolygon();
    }
    for (auto p : polygons) {
        connectionGraphWithPositions.push_back(p->drawGates(polygons, connectionGraph));
    }

    if(firstTime){

        for(auto p : polygons){
            for(auto park : p->parkingSpots){
                cars.push_back(make_pair(new car(park.first->x, park.first->y,p->colorName), false));
            }
        }
        random_shuffle(cars.begin(), cars.end());
        firstTime = false;
    }

//    cout<<cars.size()<< "nb of cars"<<endl;
    for(int i=0;i<cars.size();i++){
        cars[i].second = false;
    }

    for(auto p : polygons) {
        cars = p->drawCars(cars,firstt);
    }
    firstt = false;

//    if(TimeCounterForSlowMotion % 100 == 0) {
    // cout
//        changeCoordinates();
//    }
//    door* d = new door();
//    car* cc = new car();
//    cc->curve(d);
//    cc->curvedr();
//    d->draw();
//    cc->draw();
//    cc->go();


//    for(auto c : connectionGraphWithPositions){
//        for(auto c2 : c){
//            cout << c2.first->x << " x " << c2.first->y << " y";
//        }
//        cout<<endl;
//    }
//    cout<<"++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"<<endl;
//    TimeCounterForSlowMotion=TimeCounterForSlowMotion+100;
    if(startMoving&& isDone){
        changeCoordinates();
    }



}

void Mesh::MoveCars(){
    startMoving=true;
}

int Mesh::getIdOfTheCar(car* car){
    for(int i=0; i<cars.size(); i++){
        if(cars[i].first->x == car->x && cars[i].first->y == car->y && cars[i].first->color == car->color)
            return i;
    }
    return -1;
}

int Mesh::findPolygonIdByColor(string color){
    for(int i=0; i< polygons.size(); i++){
        if(polygons[i]->colorName == color)
            return i;
    }
    return -1;
}

void Mesh::changeCoordinates(){
//    polygons[currentPolygonId]->carsList[0]->position;
//    cout << "size of the car list ==============" << polygons[0]->carsList.size()<<endl;
//    polygons[0]->carsList[0]->curve( Vector2DD(500,50));
//    polygons[0]->carsList[0]->curvedr();
//    polygons[0]->carsList[0]->draw();


//    /*
    if(!cars.empty()) {
        if(!isWalking){
            isWalking = true;
            isDone = false;
            oldMovingCarId = currentMovingCarId;
//            polygons[currentPolygonId].push
//            cars[currentMovingCarId].first->x = polygons[currentPolygonId]->;
//            cars[currentMovingCarId].first->y = polygons[currentPolygonId];
            for(int i=0; i<polygons[currentPolygonId]->carsList.size(); i++){
                if(polygons[currentPolygonId]->carsList[i]->color != polygons[currentPolygonId]->colorName){
                    currentMovingCarId = getIdOfTheCar(polygons[currentPolygonId]->carsList[i]);
                    polygons[currentPolygonId]->carsList.erase(polygons[currentPolygonId]->carsList.begin() + i);
                    startMoving = true;
                    cars[oldMovingCarId].first->x = cars[currentMovingCarId].first->x;
                    cars[oldMovingCarId].first->y = cars[currentMovingCarId].first->y;
                    cars[oldMovingCarId].first->angle = cars[currentMovingCarId].first->angle;
                    break;
                }
                startMoving = false;
            }
            curves = new Curves(connectionGraphWithPositions, currentPolygonId, new Vector2D(cars[currentMovingCarId].first->x, cars[currentMovingCarId].first->y));
            curves->dijkstra(connectionGraph, findPolygonIdByColor(cars[currentMovingCarId].first->color));
            cars[currentMovingCarId].first->x = curves->startingPoint->x;
            cars[currentMovingCarId].first->y = curves->startingPoint->y;
            cout<<curves->startingPoint->x << " x " << curves->startingPoint->y << " y" << endl;


            for(int o=0;o<curves->gates.size();o++){
                vector<Vector2DD> PointToPush;
                Vector2DD From;
                Vector2DD To;
                Vector2DD orient;
                if(o==0) {
                    From.x=curves->startingPoint->x;
                    From.y=curves->startingPoint->y;

                    orient.x= polygons[currentPolygonId]->centerOfPolygon->x;
                    orient.y= polygons[currentPolygonId]->centerOfPolygon->y;
                }else{
                    From.x=curves->gates[o-1].first->x;
                    From.y=curves->gates[o-1].first->y;

                    orient.x= polygons[curves->polygonsIds[o-1]]->centerOfPolygon->x;
                    orient.y= polygons[curves->polygonsIds[o-1]]->centerOfPolygon->y;
                }
                To.x=curves->gates[o].first->x;
                To.y=curves->gates[o].first->y;

                cars[currentMovingCarId].first->position = From;

                cout << "polygern id   "<<curves->polygonsIds[o-1] <<"   from" <<From.x << "     " << From.y << "        to"<<To.x << "     " << To.y<<"   orient:   " <<orient.x<<" x , y "<<orient.y<<endl;
//                orient.y=

//                cars[currentMovingCarId].first->curve(To,orient,From);
                PointToPush = cars[currentMovingCarId].first->LinePath(To,orient,From, 2);
//                PointToPush = cars[currentMovingCarId].first->draw();
                curves->NewCurves.push_back(PointToPush);
//                cars[currentMovingCarId].first->curve_points.clear();
                cout <<o<< "       o" <<endl;
            }

            for(int i=0;i<curves->NewCurves.size();i++){

                for(int j=0;j<curves->NewCurves[i].size();j++){
//                    cout<<"blablaaaaaaaaaaaaaaa                  " <<curves->NewCurves[i][j].x<<endl;
                    Vector2D *newCurve= new Vector2D(curves->NewCurves[i][j].x,curves->NewCurves[i][j].y);
                    curves->AllPoints.push_back(newCurve);
                }

//                Vector2D *b1= new Vector2D(curves->gates[i].first->x,curves->gates[i].first->y);
//                curves->AllPoints.push_back(b1);

            }
            cout<<"----------------------------------------------------------------------------------------"<<endl;
            cout<<currentMovingCarId<<endl;

            for(int i=0;i<curves->AllPoints.size();i++)
            {
                cout << i<< ": x="<< curves->AllPoints[i]->x<<" y= "<<curves->AllPoints[i]->y<<endl;
            }

            cout<<"----------------------------------------------------------------------------------------"<<endl;
            isDone=true;
        }
        else{
            if(curves->index < curves->AllPoints.size()){
//                cars[currentMovingCarId].first->curve_points.clear();
//                cars[currentMovingCarId].first->index = 0;
////                cars[currentMovingCarId].first->curve(curves->gates[curves->index]);
//                cars[currentMovingCarId].first->curve( Vector2DD(100,100));
//                cars[currentMovingCarId].first->curvedr();
//                cars[currentMovingCarId].first->draw();
//                cout<<"Hola"<<endl;
                cout << " \\\\\\\\\\\\\\  moving car: " <<currentMovingCarId<< " moving to: x " << curves->AllPoints[curves->index]->x << "   y       " << curves->AllPoints[curves->index]->y<<endl;
                int a=cars[currentMovingCarId].first->x;
                int b=cars[currentMovingCarId].first->y;
                cars[currentMovingCarId].first->x = curves->AllPoints[curves->index]->x;
                cars[currentMovingCarId].first->y = curves->AllPoints[curves->index]->y;
//                cars[currentMovingCarId].first->angle = 180*getClockwiseAngle( new Vector2D(cars[currentMovingCarId].first->x, cars[currentMovingCarId].first->y),new Vector2D(a,b))/M_PI;
//                cout<<curves->gates[curves->index].first->x << " x " << curves->gates[curves->index].first->y << " y" << endl;
                curves->index++;
            }
            else{
                isWalking = false;
                currentPolygonId = findPolygonIdByColor(cars[currentMovingCarId].first->color);
            }
        }
    }
//     */
}



void Mesh::onMouseMove(double cx,double cy){
//    Vector2D v((float )cx,(float)cy);
//    auto it=triangles.begin();
//    while(it!=triangles.end()) {
//        (*it)->onMouseMove(v);
//        it++;
//    }

}

int Mesh::getTriangle(double cx, double cy){
    Vector2D pt = Vector2D(cx, cy);
    int i=0;
    for(Triangle* t : triangles){
        if(t->isInside(pt))
            return i;
        i++;
    }
    return -1;
}

int Mesh::IsTriangleOrientedClockwise(Vector2D* p1, Vector2D* p2, Vector2D* p3)
{
    float determinant = (p2->y - p1->y) * (p3->x - p2->x) - (p2->x - p1->x) * (p3->y - p2->y);

    if (determinant == 0) return 0;  // colinear 

    return (determinant > 0) ? 1 : 2;
}

void Mesh::ChangeOrientation(int i)
{
    Vector2D* temp = triangles[i]->ptr[2];

    triangles[i]->ptr[2] = triangles[i]->ptr[1];

    triangles[i]->ptr[1] = temp;
}

void Mesh::OrientTrianglesClockwise() {
    for (int i = 0; i < triangles.size(); i++)
    {
        Triangle tri = *triangles[i];

        Vector2D* v1 = new Vector2D(tri.ptr[0]->x, tri.ptr[0]->y);
        Vector2D* v2 = new Vector2D(tri.ptr[1]->x, tri.ptr[1]->y);
        Vector2D* v3 = new Vector2D(tri.ptr[2]->x, tri.ptr[2]->y);

        if (IsTriangleOrientedClockwise(v1, v2, v3) != 2) //not counter clockwise
        {
            ChangeOrientation(i);
        }
    }
}

void Mesh::flipEdge(Vector2D *p1, Vector2D* p2, Vector2D* p3, Vector2D *p4, int mainIndex, int i){
    triangles[mainIndex]->updateVertices(p3, p1, p2);
    triangles[i]->updateVertices(p1, p4, p2);
    OrientTrianglesClockwise();
}


void Mesh::onMouseDown(double cx, double cy){
    int mainIndex = getTriangle(cx, cy);
    if(mainIndex == -1)
        return;
    Triangle mainTriangle = *triangles[mainIndex];
    vector<Triangle> neighbors;

    for(int i=0; i<triangles.size(); i++){
        if((mainTriangle.isInside(*triangles[i]->ptr[0]) && mainTriangle.isInside((*triangles[i]->ptr[1]))) && !triangles[i]->checkDelauney(vertices)){
            if(mainTriangle.isInsideCircle(triangles[i]->ptr[2])){
                if(!(mainTriangle.ptr[0] == triangles[i]->ptr[0] ) && !(mainTriangle.ptr[0] == triangles[i]->ptr[1])) {
                    flipEdge(mainTriangle.ptr[0], triangles[i]->ptr[2], triangles[i]->ptr[0], triangles[i]->ptr[1], mainIndex, i);
                }
                else if(!(mainTriangle.ptr[1] == triangles[i]->ptr[0]) && !(mainTriangle.ptr[1] == triangles[i]->ptr[1])) {
                    flipEdge(mainTriangle.ptr[1], triangles[i]->ptr[2], triangles[i]->ptr[0], triangles[i]->ptr[1], mainIndex, i);
                }
                else if(!(mainTriangle.ptr[2] == triangles[i]->ptr[0]) && !(mainTriangle.ptr[2] == triangles[i]->ptr[1])) {
                    flipEdge(mainTriangle.ptr[2], triangles[i]->ptr[2], triangles[i]->ptr[0], triangles[i]->ptr[1], mainIndex, i);
                }
            }
        }
        else if( (mainTriangle.isInside(*triangles[i]->ptr[0]) && mainTriangle.isInside((*triangles[i]->ptr[2]))) && !triangles[i]->checkDelauney(vertices)){
            if(mainTriangle.isInsideCircle(triangles[i]->ptr[1])){
                if(!(mainTriangle.ptr[0] == triangles[i]->ptr[0] ) && !(mainTriangle.ptr[0] == triangles[i]->ptr[2])) {
                    flipEdge(mainTriangle.ptr[0], triangles[i]->ptr[1], triangles[i]->ptr[0], triangles[i]->ptr[2], mainIndex, i);
                }
                else if(!(mainTriangle.ptr[1] == triangles[i]->ptr[0]) && !(mainTriangle.ptr[1] == triangles[i]->ptr[2])) {
                    flipEdge(mainTriangle.ptr[1], triangles[i]->ptr[1], triangles[i]->ptr[0], triangles[i]->ptr[2], mainIndex, i);
                }
                else if(!(mainTriangle.ptr[2] == triangles[i]->ptr[0]) && !(mainTriangle.ptr[2] == triangles[i]->ptr[2])) {
                    flipEdge(mainTriangle.ptr[2], triangles[i]->ptr[1], triangles[i]->ptr[0], triangles[i]->ptr[2], mainIndex, i);
                }
            }
        }
        else if((mainTriangle.isInside(*triangles[i]->ptr[1]) && mainTriangle.isInside((*triangles[i]->ptr[2]))) && !triangles[i]->checkDelauney(vertices)){
            if(mainTriangle.isInsideCircle(triangles[i]->ptr[0])){
                if(!(mainTriangle.ptr[0] == triangles[i]->ptr[1] ) && !(mainTriangle.ptr[0] == triangles[i]->ptr[2])) {
                    flipEdge(mainTriangle.ptr[0], triangles[i]->ptr[0], triangles[i]->ptr[1], triangles[i]->ptr[2], mainIndex, i);
                }
                else if(!(mainTriangle.ptr[1] == triangles[i]->ptr[1]) && !(mainTriangle.ptr[1] == triangles[i]->ptr[2])) {
                    flipEdge(mainTriangle.ptr[1], triangles[i]->ptr[0], triangles[i]->ptr[1], triangles[i]->ptr[2], mainIndex, i);
                }
                else if(!(mainTriangle.ptr[2] == triangles[i]->ptr[1]) && !(mainTriangle.ptr[2] == triangles[i]->ptr[2])) {
                    flipEdge(mainTriangle.ptr[2], triangles[i]->ptr[0], triangles[i]->ptr[1], triangles[i]->ptr[2], mainIndex, i);
                }
            }
        }
    }
    /*for (int i = 0; i < triangles.size(); i++) {
            cout << triangles[i]->ptr[0]->x << " " << triangles[i]->ptr[1]->x << " " << triangles[i]->ptr[2]->x << endl;
        }
     cout << "*************************" << endl;*/

    MoveCars();
    cout<<"Clicked"<<endl;
}

void Mesh::Delaunay() {

    // Determinate the super triangle
    int minX = vertices[0]->x;
    int minY = vertices[0]->y;
    int maxX = minX;
    int maxY = minY;

    for (std::size_t i = 0; i < vertices.size(); ++i)
    {
        if (vertices[i]->x < minX) minX = vertices[i]->x;
        if (vertices[i]->y < minY) minY = vertices[i]->y;
        if (vertices[i]->x > maxX) maxX = vertices[i]->x;
        if (vertices[i]->y > maxY) maxY = vertices[i]->y;
    }

    double dx = maxX - minX;
    double dy = maxY - minY;
    double deltaMax = std::max(dx, dy);
    double midx = (minX + maxX) / 2;
    double midy = (minY + maxY) / 2;

    cout << dx << " " << dy << " " << deltaMax << " " << midx << " " << midy << endl;

    Vector2D* p1 = new Vector2D(midx - 20 * deltaMax, midy - deltaMax);
    Vector2D* p2 = new Vector2D(midx, midy + 20 * deltaMax);
    Vector2D* p3 = new Vector2D(midx + 20 * deltaMax, midy - deltaMax);

    // Create a list of triangles, and add the supertriangle in it
    triangles.push_back(new Triangle(p1, p2, p3));

    for (auto p = begin(vertices); p != end(vertices); p++)
    {
        std::vector<Edge> polygon;

        for (Triangle* t : triangles)
        {
            if (t->isInsideCircle(*p))
            {
                t->isDelaunay = true;
                polygon.push_back(Edge{ t->ptr[0], t->ptr[1] });
                polygon.push_back(Edge{ t->ptr[1], t->ptr[2] });
                polygon.push_back(Edge{ t->ptr[2], t->ptr[0] });
            }
        }

        triangles.erase(std::remove_if(begin(triangles), end(triangles), [](Triangle* t) {
            return t->isDelaunay;
        }), end(triangles));

        for (auto e1 = begin(polygon); e1 != end(polygon); ++e1)
        {
            for (auto e2 = e1 + 1; e2 != end(polygon); ++e2)
            {
                if (almost_equal(*e1, *e2))
                {
                    e1->isBad = true;
                    e2->isBad = true;
                }
            }
        }

        polygon.erase(std::remove_if(begin(polygon), end(polygon), [](Edge e) {
            return e.isBad;
        }), end(polygon));

        for (const auto e : polygon)
            triangles.push_back(new Triangle(e.v, e.w, *p));
    }

    for (int i = 0; i < triangles.size(); i++) {
        if (triangles[i]->isOnePeak(*p1) || triangles[i]->isOnePeak(*p2) || triangles[i]->isOnePeak(*p3)) {
            triangles.erase(triangles.begin() + i);
            i = 0;
        }
    }

    for (const auto t : triangles)
    {
        edges.push_back(new Edge{t->ptr[0], t->ptr[1]});
        edges.push_back(new Edge{t->ptr[1], t->ptr[2]});
        edges.push_back(new Edge{t->ptr[2], t->ptr[0]});
    }
    triangles.erase(triangles.begin());
}

Triangle* leftTriangle(std::vector<Triangle*> T, Vector2D* a) {
    for (auto t : T) {
        Vector2D* b = t->nextEdge(a)->w;
        bool theone = true;
        for (auto t2 : T) {
            if (t2->isInside(*b)) {
                if (t2->nextEdge(b)->w == a) {
                    theone = false;
                }
            }
        }
        if (theone) {
            return t;
        }
    }
    return NULL;
}

Vector2D* rightOrthogonalVector(Edge* E) {
    Vector2D *a = new Vector2D(  E->w->y - E->v->y,   -E->w->x + E->v->x);
    return a;
}

Vector2D* IntersectionWithBorders(Vector2D* a, Vector2D* u, int x0,int y0, int x1, int y1) {
    int k0 = (x0 - a->x) / u->x;
    int k1 = (x1 - a->x) / u->x;
    int k2 = (y0 - a->y) / u->y;
    int k3 = (y1 - a->y) / u->y;
//    cout << " ----- k0 = " << k0 << " --- k1 = " << k1 << " --- k2 = " << k2 << " --- k3 = " << k3 << endl;
//    cout << " ----- x0 = " << x0 << " --- x1 = " << x1 << " --- y0 = " << y0 << " --- y1 = " << y1 << endl;

    int min = std::min(k0, std::min(k1, std::min(k2, k3)));
    if(min<0){
        min = min* (-1);
    }

//    cout << " ----- min = " << min << endl;
    Vector2D* ku = new Vector2D(min * u->x, min * u->y);
//    cout << " ----- kh " << ku->x << " x " << ku->y << " y" <<endl;
    Vector2D* p = *a + *ku;


    double a1 = (a->y - p->y) /(a->x - p->x);
    double b1 = p->y - (p->x * a1);

    if(p->x < x0) {
        p->x = x0;
        p->y = a1 * x0 + b1;
    }

    if(p->x > x1) {
        p->x = x1;
        p->y = a1 * x1 + b1;
    }

    if(p->y < y0) {
        p->y = y0;
        p->x = (y0 - b1) / a1;
    }

    if(p->y > y1) {
        p->y = y1;
        p->x = (y1 - b1) / a1;
    }

    return p;
}

Triangle* first(std::vector < Triangle*> T) {
    return T[0];
}

std::vector<Triangle*> removeTriangle(Triangle* t, std::vector<Triangle*> T) {
    int i=0;
    for(Triangle* t2 : T){
        if(t2 == t) {
            T.erase(T.begin() + i);
            cout<<"removed. size: " <<T.size()<<endl;
        }
        i++;
    }
    return T;
}

Vector2D* Mesh::findCentroid(vector<Triangle*> T){
    int x = 0;
    int y = 0;
    for (auto t : T) {
        x += t->circumCenter.x;
        y += t->circumCenter.y;
    }
    Vector2D* center = new Vector2D(x / T.size(), y / T.size());
    return center;
}

double Mesh::getClockwiseAngle(Vector2D* p, Vector2D* center) {
    double angle = 0.0;
    angle = -1 * atan2(p->x -center->x,  p->y - center->y);
    return angle;
}

bool Mesh::comparePoints(Vector2D* p1, Vector2D* p2, Vector2D* center) {
    if(p1->y < 280 || p2->y < 280)
        return getClockwiseAngle(p1, center) > getClockwiseAngle(p2, center);
    else
        return getClockwiseAngle(p1, center) < getClockwiseAngle(p2, center);
}

void Mesh::Voronoi() {
    vector<vector<double>> colors = {{1.0, 0.0, 0.0}, {1.0, 0.466, 0.0}, {1.0, 1.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 1.0, 1.0}, {0.0, 0.0, 1.0}, {0.466, 0.0, 1.0}, {0.568 ,  0.317, 0.211}, {0.466, 0.466,  0.466}, {1.0, 1.0, 1.0}};
    vector<string> coloNames = {"red", "orange", "yellow", "green", "cyan", "blue", "purple", "brown", "grey", "white"};
    vector<string> names = {"Alpha", "Bravo" , "Charlie", "Delta", "Echo", "Foxtrot", "Golf", "Hotel", "India", "Juliett"};
//    vector<int> numbOfCars = {4, 4, 4, 4, 4, 1, 2, 2, 4, 2}; // it will be calculated !!!
    int index = 0;
    for (Vector2D* vertice : vertices) {
        // new polygon i
        if(index<vertices.size()){
            class::Polygon* polygoni = new class::Polygon();
            // subset of triangles we used isInside bcs they are vertices so either they are one of the corners or they do not belong to the triangle
            vector<Triangle*> T;
            for (Triangle* triangle : triangles) {
                if (triangle->isInside(*vertice)) {
                    T.push_back(triangle);
                }
            }

            Vector2D *center = findCentroid(T);
            for (int i = 0; i < T.size() - 1; i++)
                for (int j = 0; j < T.size() - i - 1; j++) {
//                    if (comparePoints(&T[j]->circumCenter, &T[j + 1]->circumCenter,center)){
                    if (comparePoints(T[j]->nextEdge(vertice)->w, T[j + 1]->nextEdge(vertice)->w,center)){
                        Triangle *temp = T[j];
                        T[j] = T[j + 1];
                        T[j + 1] = temp;
                    }

                }
            // get the left triangle of the triangleSet we got and the current vertice
            Triangle* t = leftTriangle(T, vertice);
            bool isOpened;
            if(t==NULL)
                isOpened = FALSE;
            else
                isOpened = TRUE;
            if(isOpened){
                polygoni->isOpened = true;
                Edge* E = t->nextEdge(vertice);
                Vector2D* H = new Vector2D((E->v->x + E->w->x)/2, (E->v->y + E->w->y)/2);
                Vector2D* u = rightOrthogonalVector(E);
                cout << " ----- a " << E->v->x << " x " << E->v->y << " y" <<endl;
                cout << " ----- b " << E->w->x << " x " << E->w->y << " y" <<endl;
                cout << " ----- u " << u->x << " x " << u->y << " y" <<endl;
                cout << " ----- H " << H->x << " x " << H->y << " y" <<endl;
                Vector2D* Q = IntersectionWithBorders(H, u, 0, 0, 1280,840);
                polygoni->addPoint(Q);
            }
            else {
                polygoni->isOpened = false;
                t = first(T);
            }
            Triangle* tprev;
            while(T.size() > 1){
                polygoni->addPoint(&t->circumCenter);
                tprev = t;
                t = t->rightNeighbour(T, vertice);
                T = removeTriangle(tprev, T);
            }
            polygoni->addPoint(&t->circumCenter);
            if(isOpened){
                Edge* E = t->prevEdge(vertice);
                Vector2D* H = new Vector2D((E->v->x + E->w->x)/2, (E->v->y + E->w->y)/2);
                Vector2D* u = rightOrthogonalVector(E);
                cout << " ----- a " << E->v->x << " x " << E->v->y << " y" <<endl;
                cout << " ----- b " << E->w->x << " x " << E->w->y << " y" <<endl;
                cout << " ----- u " << u->x << " x " << u->y << " y" <<endl;
                cout << " ----- H " << H->x << " x " << H->y << " y" <<endl;
                Vector2D* Q = IntersectionWithBorders(H, u, 0, 0, 1280,840);
                polygoni->addPoint(Q);
            }
            removeTriangle(t, T);
            polygoni->addCornerPoints(0,0,1280,840);
            polygoni->color = colors[index];
            polygoni->colorName = coloNames[index];
            polygoni->name = names[index];
            polygoni->id = index;
            polygoni->centerOfPolygon = vertice;
            polygoni->vertice = vertice;
            index++;
//            polygoni->numberOfCars = numbOfCars[index];
            polygons.push_back(polygoni);
            cout<<"**********************************"<<endl;
        }
    }

    double min = 1075200, tot =0;
    for(auto p : polygons){
        p->sortPointsCounterClockwise();
        double area = p->getPolygonSurface();
        if(area < min)
            min = area;
        tot = tot + area;
    }

    for(auto p : polygons){
        p->setNumberOfCars(min);
    }

//    int i=0;
//    for(auto p : polygons){
//        cout<<"Polygon " <<i<< endl;
//        p->displayPoints();
//        cout<<"++++++++++++++++++++++++++++"<<endl;
//        i++;
//    }

    cout<<"Total Surface " <<tot<<endl;
}