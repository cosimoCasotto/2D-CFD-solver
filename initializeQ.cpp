#include "mylib.h"
#include "Cell.h"
#include "Point.h"
#include <cmath>

extern Cell* cells;
double gam = 1.4; 
double   P = 101325; 
int      R = 287;
int      T = 300; 
double   U0 = 694.4; 
double rho = P/(R*T); 
	int
initializeQ()
{
	for (int c = 0; c < 3300; c++){
                Cell& cur = cells[c];

		cur.m_UV.setX(U0); 
		int u = cur.m_UV.getX(); 

		cur.m_UV.setY(0.0); 
		int v = cur.m_UV.getY(); 
                
		double volume = cur.m_Vol;  
		//Q    
		cur.m_Q.setA(rho); 
		cur.m_Q.setB(rho*694.4); 
		cur.m_Q.setC(rho*0); 
		cur.m_Q.setD(P/0.4 + 0.5*rho*U0*U0);

		double ht  = cur.m_Q.getD()/rho + P/rho;

		Vec2 UV; UV.setX(u); UV.setY(v);
		double Ucsi = UV.scal(cur.m_nCsi);
		cur.m_E.setA(rho * Ucsi );
		cur.m_E.setB(u * rho * Ucsi +  cur.m_nCsi.getX() * P);
		cur.m_E.setC(v * rho * Ucsi +  cur.m_nCsi.getY() * P);
		cur.m_E.setD(rho*ht*Ucsi);

		//calculate F    
		double Veta = UV.scal(cur.m_nEta);
		cur.m_F.setA(rho * Veta);
		cur.m_F.setB(u * rho * Veta +  cur.m_nCsi.getX() * P);
		cur.m_F.setC(u * rho * Veta +  cur.m_nCsi.getY() * P);
		cur.m_F.setD(rho*ht*Veta);





	}
	//	for (int c = 0; c < 300; c++){
	//		std::cout<< c <<cells[c]<<std::endl;
	//	}
	return 0; 
}
