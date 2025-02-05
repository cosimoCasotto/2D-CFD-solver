#include "Cell.h"
#include <cmath>

// Constructor definitions
Cell::Cell() : m_i(0), m_j(0), m_Alf(0), m_Arf(0), m_Atf(0), m_Abf(0), m_Vol(0), m_Ucsi(0.0), m_Veta(0.0), timeStep(0.0),
	m_Q(), m_E(), m_F()  {
}

Cell::Cell(int ci, int cj) : m_i(ci), m_j(cj), m_Alf(0), m_Arf(0), m_Atf(0), m_Abf(0), m_Vol(0), m_Ucsi(0.0), m_Veta(0.0), timeStep(0.0), 
	m_Q(), m_E(), m_F() {
}


// stampa vettore 2 componenti
	std::ostream&
operator<<(std::ostream& os, const Vec2& v2)
{
	os << "x = " << v2.getX() << ", y = " << v2.getY(); 
	return os; 
}

// stampa vettore 4 componenti
	std::ostream&
operator<<(std::ostream& os, const Vec4& v4)
{
	os << "[" << v4.getA() << "]" << std::endl 
	   << "[" << v4.getB() << "]" << std::endl 
	   << "[" << v4.getC()<< "]" << std::endl 
	   << "[" << v4.getD()<< "]" << std::endl; 
	return os; 
}

//stampa cella
std::ostream&
operator<<(std::ostream& os, const Cell& cell) {
	os << "(" << cell.m_i << ", " << cell.m_j << ")" << std::endl
		//<< "ALF    = " << cell.m_Alf      << std::endl
		//<< "ARF    = " << cell.m_Arf      << std::endl
		//<< "ATF    = " << cell.m_Atf      << std::endl
		//<< "ABF    = " << cell.m_Abf      << std::endl
		//<< "VOL    = " << cell.m_Vol      << std::endl; 
		//<< "UV     = " << cell.m_UV       << std::endl
		//<< "Ucsi   = " << cell.m_Ucsi     << std::endl
		//<< "Veta   = " << cell.m_Veta     << std::endl
		<< "nEta.x = " << cell.m_nEta     << std::endl
		<< "nCsi.x = " << cell.m_nCsi     << std::endl; 
		//<< " Q     = " << cell.m_Q        << std::endl 
		//<< " E     = " << cell.m_E        << std::endl 
		//<< " F     = " << cell.m_F        << std::endl; 
	return os;
}

// normal in the CSI direction
Vec2    getnCsi (const Point& c){
	Vec2 nCsi;
	Point br = getRightPoint(c);
	Point tr = getUpPoint(br);
	Point coordbr = coordinates(br);
	Point coordtr = coordinates(tr);
	double dx = coordbr.x-coordtr.x;
	double dy = coordtr.y-coordbr.y;
	//std::cout << c << "dy = " <<dy<<std::endl; 
	double A  = sqrt(dx*dx + dy*dy);
	//Point nCsi; 
	nCsi.setX(dy/A); 
	nCsi.setY(dx/A); 
	return nCsi; 
}

//normal to the ETA direction
Vec2    getnEta (const Point& c){
	Vec2 nEta; 
	Point tl = getUpPoint(c); 
	Point br = getRightPoint(c);
	Point tr = getUpPoint(br);
	Point coordtl = coordinates(tl);
	Point coordtr = coordinates(tr);
	double dx = coordtr.x-coordtl.x;
	double dy = coordtl.y-coordtr.y;
	double A  = sqrt(dx*dx + dy*dy);
	//Point nEta;
	nEta.setX(dy/A);
	nEta.setY(dx/A);
	return nEta;
}

// direction parallel to FACE
Vec2    getParDir (const Point& c){
        Vec2 ParDir;
        Point tl = getUpPoint(c);
        Point br = getRightPoint(c);
        Point tr = getUpPoint(br);
        Point coordtl = coordinates(tl);
        Point coordtr = coordinates(tr);
        double dx = std::abs(coordtl.x-coordtr.x);
        double dy = (coordtr.y-coordtl.y);
        double A  = sqrt(dx*dx + dy*dy);
        //Point nEta;
        ParDir.setX(dx/A);
        ParDir.setY(dy/A);
        return ParDir;
}

double getSetaX (const Point& c){

	Point tl = getUpPoint(c);
	Point br = getRightPoint(c);
	Point tr = getUpPoint(br);
	Point coordtl = coordinates(tl);
	Point coordtr = coordinates(tr);
	double SetaX = coordtl.y - coordtr.y;
	//std::cout << c << "dx = " <<SetaX<<std::endl; 
        return SetaX; 	
}

double getScsiY (const Point& c){

	Point tl = getUpPoint(c);
	Point br = getRightPoint(c);
	Point tr = getUpPoint(br);
	Point coordbr = coordinates(br);
	Point coordtr = coordinates(tr);
	double ScsiY = std::abs(coordbr.y - coordtr.y);
	//std::cout << c << "dx = " <<SetaX<<std::endl; 
        return ScsiY; 	
}

double getSetaY (const Point& c){

	Point tl = getUpPoint(c);
	Point br = getRightPoint(c);
	Point tr = getUpPoint(br);
	Point coordtl = coordinates(tl);
	Point coordtr = coordinates(tr);
	double SetaY = coordtr.x - coordtl.x;
	//std::cout << c << "dy = " <<SetaY<<std::endl; 
        return SetaY; 	
} 


//FACE AREAS (right face area, left, top, bottom)
//RFA = rigth face area 
double RFA (const Point& c){
	Point br = getRightPoint(c);
	Point tr = getUpPoint(br);
	Point coordbr = coordinates(br);
	Point coordtr = coordinates(tr);
	double dx = std::abs(coordbr.x-coordtr.x);
	double dy = std::abs(coordbr.y-coordtr.y);
	double A  = sqrt(dx*dx + dy*dy);
	return A;
}

//LFA = left face area
double LFA (const Point& c){
	Point tl = getUpPoint(c);
	Point coordtl = coordinates(tl);
	Point coordc = coordinates(c);
	double dx = std::abs(coordc.x-coordtl.x);
	double dy = std::abs(coordc.y-coordtl.y);
	double A  = sqrt(dx*dx + dy*dy);
	return A;
}


//TFA = top face area
double TFA (const Point& c){
	Point tl = getUpPoint(c);
	Point tr = getRightPoint(tl);
	Point coordtl = coordinates(tl);
	Point coordtr = coordinates(tr);
	double dx = std::abs(coordtr.x-coordtl.x);
	double dy = std::abs(coordtr.y-coordtl.y);
	double A  = sqrt(dx*dx + dy*dy);
	return A;
}




//BFA = bottom face area
double BFA (const Point& c){
	Point br = getRightPoint(c);
	Point coordbr = coordinates(br);
	Point coordc = coordinates(c);
	double dx = std::abs(coordc.x-coordbr.x);
	double dy = std::abs(coordc.y-coordbr.y);
	double A  = sqrt(dx*dx + dy*dy);
	return A;
}


// Volume 
double Vol (const Point& c){
	Point br = getRightPoint(c); 
	Point tl = getUpPoint(c); 
	Point tr = getUpPoint(br); 
	Point coordbr = coordinates(br);
	Point coordbl = coordinates(c);
	Point coordtl = coordinates(tl);
	Point coordtr = coordinates(tr);
	double volume = 0.5*((coordtr.x-coordbl.x)*(coordtl.y-coordbr.y) - (coordtl.x-coordbr.x)*(coordtr.y-coordbl.y)); 
	return volume; 	

}
