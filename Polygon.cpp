#include <algorithm>
#include "Polygon.h"

Vector2D* center;

void Polygon::addPoint(Vector2D* p) {
	points.push_back(p);
}

void Polygon::addCornerPoints(int x0, int y0, int x1, int y1) {
    std::cout<<"Hi "<<std::endl;
	for (int i = 0; i < points.size(); i++) {
	    int next = i + 1;
	    if(i == points.size()-1)
            next = 0;
        std::cout<<i<<std::endl;
		if (points[i]->x == x0 && points[next]->y == y0) {
		    std::cout<<"if1"<<std::endl;
            Vector2D *a = new Vector2D(x0, y0);
		    std::cout<<a->x<<" x, "<<a->y<<" y is inserted"<<std::endl;
			points.insert(points.begin() + next, a);
			i++;
		}
		if (points[i]->y == y0 && points[next]->x == x1) {
            std::cout<<"if2"<<std::endl;
            Vector2D *a = new Vector2D(x1, y0);
            std::cout<<a->x<<" x, "<<a->y<<" y is inserted"<<std::endl;
			points.insert(points.begin() + next, a);
            i++;
		}
		if (points[i]->x == x1 && points[next]->y == y1) {
            std::cout<<"if3"<<std::endl;
            Vector2D *a = new Vector2D(x1, y1);
            std::cout<<a->x<<" x, "<<a->y<<" y is inserted"<<std::endl;
			points.insert(points.begin() + next, a);
            i++;
		}
		if (points[i]->y == y1 && points[next]->x == x0) {
            std::cout<<"if4"<<std::endl;
            Vector2D *a = new Vector2D(x0, y1);
            std::cout<<a->x<<" x, "<<a->y<<" y is inserted"<<std::endl;
			points.insert(points.begin() + next, a);
            i++;
		}
        std::cout << points[i]->x << "x, " << points[i]->y << " y   i " << std::endl;
        std::cout << points[next]->x << "x, " << points[next]->y << " y   next" << std::endl;
	}
    std::cout<<"Bye "<<std::endl;
}

Vector2D* Polygon::findCentroid(){
    int x = 0;
    int y = 0;
    for (auto p : points) {
        x += p->x;
        y += p->y;
    }
    Vector2D* center = new Vector2D(x / points.size(), y / points.size());
    return center;
}

bool Polygon::isInsidePoints(Vector2D* pp){
    if(pp==NULL)
        return false;
    for(auto p : points){
        if(p->x == pp->x && p->y == pp->y)
            return true;
    }
    return false;
}

bool comparePoints(Vector2D* p1, Vector2D* p2){
    std::cout<<"Hey";
    double a1 = (int) ((atan2(p1->x - center->x, p1->y - center->y) * (180.0/3.141592653589793238463)) + 360) % 360;
    double a2 = (int) ((atan2(p2->x - center->x, p2->y - center->y) * (180.0/3.141592653589793238463)) + 360) % 360;
    std::cout<<"hola";
    return (int) (a2 - a1);
}


double getClockwiseAngle(Vector2D* p) {
    double angle = 0.0;
    angle = -1 * atan2(p->x -center->x,  p->y - center->y);
    return angle;
}

bool comparePoints2(Vector2D* p1, Vector2D* p2) {
    return getClockwiseAngle(p1) < getClockwiseAngle(p2);
}


void Polygon::sortPointsCounterClockwise() {

    center = findCentroid();
    std::sort(points.begin(), points.end() , comparePoints2);

}

Vector2D* Polygon::findCentroidParkingSpots(){
    int x = 0;
    int y = 0;
    for (auto p : parkingSpots) {
        x += p.first->x;
        y += p.first->y;
    }
    Vector2D* center = new Vector2D(x / parkingSpots.size(), y / parkingSpots.size());
    return center;
}

bool Polygon::comparePoints(Vector2D* p1, Vector2D* p2) {
    if(p1->y < 280 || p2->y < 280)
        return getClockwiseAngle(p1) > getClockwiseAngle(p2);
    else
        return getClockwiseAngle(p1) < getClockwiseAngle(p2);
}

void Polygon::sortParkingSpotsCounterClockwise() {

    center = findCentroidParkingSpots();
    for (int i = 0; i < parkingSpots.size() - 1; i++)
        for (int j = 0; j < parkingSpots.size() - i - 1; j++) {
            if (comparePoints(parkingSpots[j].first, parkingSpots[j + 1].first)){
                Vector2D *temp = parkingSpots[j].first;
                parkingSpots[j].first = parkingSpots[j + 1].first;
                parkingSpots[j + 1].first = temp;
            }
        }
}

double Polygon::getPolygonSurface(){
    int j = points.size() - 1;
    for (int i = 0; i < points.size(); i++)
    {
        area += (points[j]->x + points[i]->x) * (points[j]->y - points[i]->y);
        j = i;
    }
    area = abs(area / 2.0);
    return area;
}

void Polygon::setNumberOfCars(double min){
    numberOfCars = (4.0 / 3.0) * area / min;
    if(numberOfCars>4)
        numberOfCars = 4;
}

void Polygon::displayPoints(){
    for(auto p : points){
        std::cout << p->x << "x, " << p->y << " y ++++++++++++++++++++++++" << std::endl;
    }
    std::cout << "numberOfCars " <<  this->numberOfCars <<std::endl;
}

void Polygon::displayParkingSpots(){
    for(auto p : parkingSpots){
        std::cout << p.first->x << "x, " << p.first->y << " y " << p.second << " angle" << std::endl;
    }
    std::cout << "numberOfCars " <<  this->numberOfCars <<std::endl;
}

void Polygon::dislayPolygon(){
    //drawing polygon
    glColor3f(color[0],color[1],color[2]);
    glBegin(GL_POLYGON);
    for(auto p : points){
        glVertex2d(p->x,p->y);
    }
    glEnd();

    // drawing the borders of the polygon
    glColor3f(0.0,0.0,0.0);
    glLineWidth(	2.7);
    glBegin(GL_LINE_LOOP);
    for(auto p : points){
        glVertex2d(p->x,p->y);
    }
    glEnd();

    // drawing the vertice
    float i = 0.0f, r = 3.5;
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(vertice->x, vertice->y); // Center
    for(i = 0.0f; i <= 360; i++)
        glVertex2f(r*cos(M_PI * i / 180.0) + vertice->x, r*sin(M_PI * i / 180.0) + vertice->y);
    glEnd();

    int x = vertice->x, y = vertice->y + 30;
    //drawing the rect for the text
    glColor3f(1.0,1.0,1.0);
    glRectd(x - 35, y -15, x + 35, y + 15);

    // drawing the rect border
    glColor3f(0.0,0.0,0.0);
    glLineWidth(	1.5);
    glBegin(GL_LINE_LOOP);
    glVertex2d(x - 35,y - 15);
    glVertex2d(x + 35,y - 15);
    glVertex2d(x + 35,y + 15);
    glVertex2d(x - 35,y + 15);
    glEnd();

    // drawing the name
    glColor3f(0.0,0.0,0.0);
    glRasterPos2f(x - 30, y - 5);
    glutBitmapString(GLUT_BITMAP_8_BY_13, reinterpret_cast<const unsigned char *>(name.c_str()));
}

vector<pair<Vector2D*, double>> Polygon::drawGates(vector<class::Polygon*> polygons, vector<vector<int>> connectionGraph){
    int next;
    vector<pair<Vector2D*, double>> positions;
    bool aa=true;
    bool bb=true;
    for(int i=0; i<connectionGraph[id].size(); i++){
        if(connectionGraph[id][i] != 0){
            for(int k=0; k<points.size(); k++){
                next = k+1;
                if(k == points.size()-1)
                    next = 0;
                if(polygons[i]->isInsidePoints(points[k]) && polygons[i]->isInsidePoints(points[next])){
                    Vector2D* H = new Vector2D((points[k]->x + points[next]->x)/2, (points[k]->y + points[next]->y)/2);

                    Gate* g;
                    GLdouble theta;
                    bool toDraw = comparePoints2(points[k], points[next]);
                    if(id==7){
                        if(aa){
                            toDraw = !comparePoints2(points[k], points[next]);
                            aa=false;
                        }
                    }
                    if(id==8){
                        if(!bb)
                            toDraw = !comparePoints2(points[k], points[next]);
                        bb=false;
                    }
                    if(id==9)
                            toDraw = !comparePoints2(points[k], points[next]);

                    if(toDraw) { // angle(k) < angle(next)
                        g = new Gate(false, H);
                        float dx21 = (H->x + 60)- H->x;
                        float dx31 = points[k]->x  - H->x;
                        float dy21 = (H->y - 20) - H->y;
                        float dy31 = points[k]->y - H->y;
                        float m12 = sqrt( dx21*dx21 + dy21*dy21 );
                        float m13 = sqrt( dx31*dx31 + dy31*dy31 );
                        theta = acos( (dx21*dx31 + dy21*dy31) / (m12 * m13) );
                    }
                    else{  // angle(k) > angle(next)
                        g = new Gate(true, H);
                        float dx21 = (H->x - 60)- H->x;
                        float dx31 = points[k]->x  - H->x;
                        float dy21 = (H->y + 20) - H->y;
                        float dy31 = points[k]->y - H->y;
                        float m12 = sqrt( dx21*dx21 + dy21*dy21 );
                        float m13 = sqrt( dx31*dx31 + dy31*dy31 );
                        theta = acos( (dx21*dx31 + dy21*dy31) / (m12 * m13) );
                    }
                    g->rotation(theta - 0.349066);
                    positions.push_back(make_pair(H, theta - 0.349066));
                }
            }
        }
        else
            positions.push_back(make_pair(new Vector2D(-1, -1), 0));
    }
    drawParkings(polygons, connectionGraph);
    return positions;
}

void rotation(vector<Vector2D*> verts, Vector2D* startingPoint, double theta) {
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
}

void Polygon::drawParkings(vector<class::Polygon*> polygons, vector<vector<int>> connectionGraph){

    Vector2D* H;
    Edge* E;
    E = new Edge(new Vector2D(-1, -1), new Vector2D(-1, -1));
    int next;

    for( int k = 0; k < points.size(); k++) {
        bool used = false;
        next = k + 1;
        if (k == points.size() - 1)
            next = 0;
        for (int i=0; i<connectionGraph[id].size(); i++) {
            if (polygons[i]->isInsidePoints(points[k]) && polygons[i]->isInsidePoints(points[next]) && connectionGraph[id][i] != 0) {
                used = true;
                break;
            }
        }
        if(!used){
            double dist1 = sqrt(pow(points[next]->x - points[k]->x, 2) + pow(points[next]->y - points[k]->y, 2) * 1.0);
            double dist2 = sqrt(pow(E->w->x - E->v->x, 2) + pow(E->w->y - E->v->y, 2) * 1.0);
            if(dist1 > dist2)
                E = new Edge(points[k], points[next]);
        }
    }

    H = new Vector2D((E->v->x + E->w->x)/2, (E->v->y + E->w->y)/2);

    float i = 0.0f, r = 3.5;
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(H->x, H->y); // Center
    for(i = 0.0f; i <= 360; i++)
        glVertex2f(r*cos(M_PI * i / 180.0) + H->x, r*sin(M_PI * i / 180.0) + H->y);
    glEnd();

    int lx, ly;
    int x = 80, y = 40;
    double a1 = (H->y - E->v->y) /(H->x - E->v->x);
    double b1 = H->y - (H->x * a1);
    numberOfCars = polygons[id]->numberOfCars;
    Vector2D* H2;
    if (H->x > 0 && H->x < 1280 && H->y > 0 && H->y < 840){
        if( id == 6)
            H2 = new Vector2D(H->x - x / 2 + 7, a1 * (H->x - x / 2 + 7) + b1);
        else if(id == 7)
            H2 = new Vector2D(H->x - x / 2 + 29, a1 * (H->x - x / 2 + 29) + b1);
        else
            H2 = new Vector2D(H->x + x / 2 - 7, a1 * (H->x + x / 2 - 7) + b1);
    }
    else if(H->x == 0)
        H2 = new Vector2D(H->x, (H->y - y));
    else if(H->x == 1280)
        H2 = new Vector2D(H->x, (H->y + y + y/2));
    else if(H->y == 840) {
        H->x = H->x - x/2;
        H2 = new Vector2D(H->x + x / 2, H->y);
    }
    else if(H->y == 0 )
        H2 = new Vector2D(H->x + x/2, H->y );

    parkingSpots.clear();

//    cout<<"Number of Cars ---" <<numberOfCars<<endl;
    for(int i=0;i<numberOfCars; i++) {
        parking = GlutWindow::loadTGATexture("../Textures/carpark.tga", lx, ly);
        assert(parking != 0);
        if(id == 3 || id == 6)
            x = 67;
        if(numberOfCars%2 == 0 && i == numberOfCars/2){
            H = H2;
        }
        if(numberOfCars%2 != 0 && i == 0){
            if(H->x == 0 || H->x == 1280){
                H->y = H->y + y/2;
            }
            if(H->y == 0 || H->y == 840){
                H->x = H->x + x/4;
            }
        }
        if(numberOfCars%2 != 0 && i == numberOfCars/2 + 1){
            H = H2;
        }
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_TEXTURE_2D);

        glBindTexture(GL_TEXTURE_2D, parking);
        glPushMatrix();
        double angle = 0;
        if(H->y == 0)
            angle = -54.975 * 180 / M_PI;

        if(H->y == 840)
            angle = 54.975 * 180 / M_PI;

        if(H->x == 1280)
            angle = 109.95 * 180 / M_PI;

        if( H->x < 1280 && H->y <840 && H->y >0 && H->x > 700)
            angle = -40.55 * 180 / M_PI;

        if( H->x < 700 && H->y <840 && H->y >0 && H->x > 0){
            if(comparePoints2(E->v, E->w))
                angle = 30.45 * 180 / M_PI;
            else
                angle = -10.42 * 180 / M_PI;
        }

        glTranslatef(H->x, H->y, 1.0);
//        cout<<"Poly " << id << " H " << H->x << " x, " << H->y << " y"<<endl;
        glRotatef(angle, 0, 0, 1);

        parkingSpots.push_back(make_pair(new Vector2D(H->x, H->y), angle));

        if(numberOfCars%2 == 0 && i < numberOfCars/2){
            glBegin(GL_QUADS);

            glTexCoord2f(0.0, 0.0);
            glVertex2f(0.0, 0.0);

            glTexCoord2f(1.0, 0.0);
            glVertex2f(80, 0.0);

            glTexCoord2f(1.0, 1.0);
            glVertex2f(80, 40);

            glTexCoord2f(0.0, 1.0);
            glVertex2f(0.0, 40);
            glEnd();
            if(y == 840)
                H->x = H->x - x;
            else if(H->x >0 && H->x < 1280) {
                H->x = H->x - x / 2;
                H->y = a1 * H->x + b1;
            }
            else{
                H->y = H->y + y;
            }
        }

        if(numberOfCars%2 == 0 && i >= numberOfCars/2){
            glBegin(GL_QUADS);

            glTexCoord2f(0.0, 0.0);
            glVertex2f(0.0, 0.0);

            glTexCoord2f(1.0, 0.0);
            glVertex2f(80, 0.0);

            glTexCoord2f(1.0, 1.0);
            glVertex2f(80, 40);

            glTexCoord2f(0.0, 1.0);
            glVertex2f(0.0, 40);
            glEnd();
            if(y == 840)
                H->x = H->x + x;
            else if(H->x >0 && H->x < 1280) {
                H->x = H->x + x / 2;
                H->y = a1 * H->x + b1;
            }
            else{
                H->y = H->y - y;
            }
        }

        if(numberOfCars%2 != 0 && i <= numberOfCars/2){
            glBegin(GL_QUADS);

            glTexCoord2f(0.0, 0.0);
            glVertex2f(0.0, 0.0);

            glTexCoord2f(1.0, 0.0);
            glVertex2f(80, 0.0);

            glTexCoord2f(1.0, 1.0);
            glVertex2f(80, 40);

            glTexCoord2f(0.0, 1.0);
            glVertex2f(0.0, 40);
            glEnd();

            if(H->x == 0 || H->x == 1280) {
                H->y = H->y - y;
            }
            else if(H->y >0 && H->y < 840) {
                H->x = H->x - x/2;
                H->y = a1 * H->x + b1;
            }
            else
                H->x = H->x - x;
        }

        if(numberOfCars%2 != 0 && i > numberOfCars/2){
            glBegin(GL_QUADS);

            glTexCoord2f(0.0, 0.0);
            glVertex2f(0.0, 0.0);

            glTexCoord2f(1.0, 0.0);
            glVertex2f(80, 0.0);

            glTexCoord2f(1.0, 1.0);
            glVertex2f(80, 40);

            glTexCoord2f(0.0, 1.0);
            glVertex2f(0.0, 40);
            glEnd();

            if(H->x == 0 || H->x == 1280) {
                H->y = H->y + y;
            }
            else if(H->y >0 && H->y < 840) {
                H->x = H->x + x/2;
                H->y = a1 * H->x + b1;
            }
            else
                H->x = H->x + x;
        }

        glPopMatrix();
        glDisable(GL_TEXTURE_2D);
        x = 80;
    }
}

vector<pair<car*, bool>> Polygon::drawCars(vector<pair<car*, bool>> cars,bool first) {

    int numOfAddedCars = 0;
//    cout<< " Number of cars in this poygon " << numberOfCars <<endl;
    for(int i=0; i<cars.size(); i++) {
//        cout << cars[i].first->color << " car color " << colorName << " POLYGONE COLOR" <<endl;
        if (cars[i].first->color != colorName && numOfAddedCars < numberOfCars) {
            if (!cars[i].second) {
//                cout<<"Car drawn "<< c.first->color << " color " << numOfAddedCars <<" nb added cars"  << endl;
                 if(first){
                    cars[i].first->x=parkingSpots[numOfAddedCars].first->x;
                    cars[i].first->y=parkingSpots[numOfAddedCars].first->y;
                    cars[i].first->angle=parkingSpots[numOfAddedCars].second;
                    carsList.push_back(cars[i].first);
                   }
                int lx, ly;
                carTexture = GlutWindow::loadTGATexture("../Textures/" + cars[i].first->color + "car.tga", lx, ly);
                assert(carTexture != 0);
                cars[i].second = true;

//                cout << cars[0].first->position.x << "xx  the first fukcing carrr   yy" << cars[0].first->position.y << endl;

                glEnable(GL_BLEND);
                glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
                glEnable(GL_TEXTURE_2D);

                glBindTexture(GL_TEXTURE_2D, carTexture);
                glPushMatrix();
                glTranslatef(cars[i].first->x, cars[i].first->y, 1.0);

                glRotatef(cars[i].first->angle, 0, 0, 1);

                glBegin(GL_QUADS);

                glTexCoord2f(0.0, 0.0);
                glVertex2f(0.0, 0.0);

                glTexCoord2f(1.0, 0.0);
                glVertex2f(80, 0.0);

                glTexCoord2f(1.0, 1.0);
                glVertex2f(80, 40);

                glTexCoord2f(0.0, 1.0);
                glVertex2f(0.0, 40);
                glEnd();

                glPopMatrix();
                glDisable(GL_TEXTURE_2D);

                numOfAddedCars++;
            }
        }
    }
//    TimeCounterForSlowMotion=TimeCounterForSlowMotion+10;
    return cars;
}

