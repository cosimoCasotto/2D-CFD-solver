#include "Point.h"

extern int sx,sy; 
extern double* x2d; 
extern double* y2d; 
extern int nx;  
extern int ny; 
// class constuctors
Point::Point() : x(0), y(0) {}

Point::Point(double x, double y) : x(x), y(y) {}

double Point::getX() const {
	return x;
}

double Point::getY() const {
	return y;
}

void Point::setX(double x) {
	this->x = x;
}

void Point::setY(double y) {
	this->y = y;
}

// to print a Point
// Definition of operator<< for Point class
std::ostream& operator<<(std::ostream& os, const Point& Point) {
	os << "(" << Point.x << ", " << Point.y << ")";
	return os;
}


// helper functions
// coordinates returns x2d and y2d values of a given cell (x,y) = (i,j)
	Point 
coordinates (Point p)
{
	Point r;
	int index = (p.y)*(nx+2)+p.x;
	r.x = x2d[index];
	r.y = y2d[index];
	return r;
}

// grit to flow is identical to coordinates but is used in different contexts
	Point
gridToFlow(Point p)
{
	return coordinates(p); 
}


//scales and translates point to place them in image  
	Point
flowToImage(Point p)
{
	Point r;
	r.x =  p.x*400 + 300-40;
	//r.x =  p.x*400 + 300;
	r.y = -p.y*400 + 950;
	return r;
}


Point getNext (Point p, int i, int j){
	Point n; 
	n.x = p.x + i; 
	n.y = p.y + j; 
	return n; 
}


Point getLeftPoint  (Point p){Point n = getNext(p, -1,  0); return n;}
Point getLLPoint    (Point p){Point n = getNext(p, -2,  0); return n;}

Point getRightPoint (Point p){Point n = getNext(p,  1,  0); return n;}
Point getRRPoint    (Point p){Point n = getNext(p,  2,  0); return n;}

Point getUpPoint    (Point p){Point n = getNext(p,  0,  1); return n;}
Point getUUPoint    (Point p){Point n = getNext(p,  0,  2); return n;}

Point getDownPoint  (Point p){Point n = getNext(p,  0, -1); return n;}
Point getDDPoint    (Point p){Point n = getNext(p,  0, -2); return n;}


// find location of cell center 
Point 
CellCenter(Point bl){
	// location of the 4 points that make up the cell:
	Point br = getRightPoint(bl);
	Point tr = getUpPoint(br);
	Point tl = getUpPoint(bl);
	Point coordbr = coordinates(br);
	Point coordbl = coordinates(bl);
	Point coordtr = coordinates(tr);
	Point coordtl = coordinates(tl);
	Point center;
	center.x = (coordbr.x + coordbl.x + coordtl.x + coordtr.x)/4;
	center.y = (coordbr.y + coordbl.y + coordtl.y + coordtr.y)/4;
	return center;
}


// calculate distance between 2 points in the x direction 
double Xdist (Point p, Point s){
	Point Point1 = coordinates(p);
	Point Point2 = coordinates(s);

	double dist = std::abs(Point1.x-Point2.x);
	return dist;
}

// calculate distance between 2 points in the y direction 
double Ydist (Point p, Point s){
	Point Point1 = coordinates(p);
	Point Point2 = coordinates(s);

	double dist = std::abs(Point1.y-Point2.y);
	return dist;
}

Point faceCTR (Point a, Point b){
	Point CTR; 
	CTR.x = (a.x+b.x)/2; 
	CTR.y = (a.y+b.y)/2; 
	return CTR; 
}

