#include "mylib.h"
#include "Cell.h"
#include "Point.h"
#include <cmath>

extern Cell* cells;
//extern double rho; 
extern double gam; 
//extern double P; 

int
Fluxcalc()
{
	for (int c = 0; c < 3300; c++){
		Cell& cur = cells[c]; 

                double rho = cur.m_Q.getA();  
		double u   = cur.m_Q.getB() / cur.m_Q.getA();  
		double v   = cur.m_Q.getC() / cur.m_Q.getA();  
	        double P   = 0.4 * (cur.m_Q.getD() - 0.5 * rho * (u*u + v*v)); 	
                double ht  = cur.m_Q.getD()/rho + P/rho; 
		//calculate E
		Vec2 UV; UV.setX(u); UV.setY(v);     
		double Ucsi = getUcsi(c); 
		cur.m_E.setA(rho * Ucsi ); 
		cur.m_E.setB(u * rho * Ucsi +  cur.m_nCsi.getX() * P);  
		cur.m_E.setC(v * rho * Ucsi +  cur.m_nCsi.getY() * P);  
		cur.m_E.setD(rho*ht*Ucsi);

		//calculate F    
		double Veta = getVeta(c);
		cur.m_F.setA(rho * Veta); 
		cur.m_F.setB(u * rho * Veta +  cur.m_nEta.getX() * P);  
		cur.m_F.setC(v * rho * Veta +  cur.m_nEta.getY() * P);  
		cur.m_F.setD(rho*ht*Veta);


	}
//	std::cout<<"after flux calc: "<<std::endl;
//	std::cout<<cells[0];
//      std::cout<<cells[68];
//      std::cout<<cells[69];
	return 0; 
}
