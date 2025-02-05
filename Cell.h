#ifndef CELL_H
#define CELL_H
#include <iostream>
#include "Point.h"
//#include "Eigen/Dense"



//2 component vectors
class Vec2 {
	public: 
		Vec2(void): m_x(0.0), m_y(0.0){}
		void setX(double x) {m_x = x; }
		void setY(double y) {m_y = y; }
                double getX (void)    const {return m_x; }
                double getY (void)    const {return m_y; }
		double scal (Vec2& v) const {return m_x*v.m_x + m_y*v.m_y; }
	private : 
		double m_x; 
		double m_y; 

		friend std::ostream& operator<<(std::ostream& os, const Vec2& v);
}; 

//4component vectors
class Vec4 {
	public: 
		Vec4(): m_VecA(0.0), m_VecB(0.0), m_VecC(0.0), m_VecD(0.0){}; 
		void setA(double a) {m_VecA = a; }
		void setB(double b) {m_VecB = b; }
		void setC(double c) {m_VecC = c; }
		void setD(double d) {m_VecD = d; }
                double getA (void)    const {return m_VecA; }
                double getB (void)    const {return m_VecB; }
                double getC (void)    const {return m_VecC; }
                double getD (void)    const {return m_VecD; }
        private: 
		double m_VecA;
		double m_VecB;
		double m_VecC;
		double m_VecD;
}; 

class Cell {
	public:
		Cell();
		Cell(int ci, int cj);

		//cell inidices
		int m_i;
		int m_j;
		// time step of the cell
		double timeStep ; 
		//cell face areas
		double m_Alf;
		double m_Arf;
		double m_Atf;
		double m_Abf;
		//cell volume
		double m_Vol;
                //velocities in cell
		Vec2   m_UV; 		//velocity in x dir U, velocity in y dir V 
		double m_Ucsi;       //uv proiettato su csi 
                double m_Veta; 	   // uv proiettato su eta
		// normal vectors to cell faces
		Vec2 m_nEta; 
		Vec2 m_nCsi; 
		// vectors Q,E,F
		Vec4 m_Q; // Vector Q with components [rho, rho*u, rho*v, rho*et]
	        Vec4 m_E; // E flux vector
		Vec4 m_F; // F flux vector
                
		Vec4 m_E_p; 
		Vec4 m_E_m; 
		Vec4 m_F_p; 
		Vec4 m_F_m; 
			  //Eigen::MatrixXd m_A; 

			  // Forward declaration of operator<< as a friend
		friend std::ostream& operator<<(std::ostream& os, const Cell& Cell);
};

double RFA      (const Point& c);
double LFA      (const Point& c);
double TFA      (const Point& c);
double BFA      (const Point& c);
double Vol      (const Point& c); 
Vec2   getnEta  (const Point& c); 
Vec2   getnCsi  (const Point& c); 
Vec2   getParDir(const Point& c); 
double getSetaX (const Point& c); 
double getSetaY (const Point& c); 
double getScsiY (const Point& c); 

//extra functions
Point
CellCenter(Point bl);
//CellCenter(const Point& bl);

#endif  // CELL_H

