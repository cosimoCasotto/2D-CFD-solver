
#include <iostream> 
#ifndef POINT_H
#define POINT_H

class Point {
public:
    Point();
    Point(double x, double y);
    double getX() const;
    double getY() const;
    void setX(double x);
    void setY(double y);
    double x;
    double y;



// Friend function declaration
    friend std::ostream& operator<<(std::ostream& os, const Point& point);


//private:
  //  double x;
  //  double y;

};

    Point getRightPoint(Point p);
    	Point getRRPoint(Point p); 
    
    Point getUpPoint(Point p);
    	Point getUUPoint(Point p); 	
    
    Point getDownPoint(Point p);
   	Point getDDPoint(Point);  
    
    Point getLeftPoint(Point p);
   	Point getLLPoint(Point p); 


Point gridToFlow (Point p); 
Point flowToImage (Point p); 

Point coordinates(Point p);

double Xdist(Point p1, Point p2);
double Ydist(Point p1, Point p2);

Point faceCTR (Point a, Point b); 
#endif // POINT_H

