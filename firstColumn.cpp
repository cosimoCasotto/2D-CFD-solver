#include "mylib.h"
#include "Cell.h"
#include "Point.h"
#include <cmath>

extern Cell* cells;
extern double gam; 
extern double   P; 
extern int      R;
extern int      T; 
extern double   U0; 
extern double rho; 
	int
firstColumn()
{
	for (int j = 0; j < 50; j++){
                int c = 66*j; 
                Cell& cur = cells[c];

		cur.m_UV.setX(U0); 
		int u = cur.m_UV.getX(); 

		cur.m_UV.setY(0.0); 
		int v = cur.m_UV.getY(); 
                
		double volume = cur.m_Vol;  
		//Q    
		cur.m_Q.setA(rho); 
		cur.m_Q.setB(rho*u); 
		cur.m_Q.setC(rho*v); 
		cur.m_Q.setD(P/0.4 + 0.5*rho*u*u);

		//calculate E
                cur.m_E.setA(rho * U0 ); ////ask dad how to solve
                cur.m_E.setB(u * rho * U0 + cur.m_nCsi.getX() * P); ////ask dad how to solve
                cur.m_E.setC(0); ////ask dad how to solve
                cur.m_E.setD((P/0.4 + 0.5*rho*(U0*U0)+ P) * getUcsi(c));

                //calculate F
                cur.m_F.setA(0); ////ask dad how to solve
                cur.m_F.setB(cur.m_nCsi.getX() * P); ////ask dad how to solve
                cur.m_F.setC(cur.m_nCsi.getY() * P); ////ask dad how to solve
                cur.m_F.setD(0);



	}
#ifdef CIAO
	for (int i = 0; i < 66; i++){
		int c = 3299-i;
		Cell& cur = cells[c];
		Cell& under = cells[c-66]; 
		double u1 = getU(c-66); 
		double v1 = getV(c-66); 
		cur.m_Q.setA(under.m_Q.getA());   
		cur.m_Q.setB(under.m_Q.getB());   
		cur.m_Q.setC(under.m_Q.getC());   
		cur.m_Q.setD(under.m_Q.getD());   
		
		cur.m_F.setA(under.m_F.getA());   
		cur.m_F.setA(under.m_F.getA());   
		cur.m_F.setB(under.m_F.getB());   
		cur.m_F.setC(under.m_F.getC());   

		cur.m_E.setD(under.m_E.getD());   
		cur.m_E.setB(under.m_E.getB());   
		cur.m_E.setC(under.m_E.getC());   
		cur.m_E.setD(under.m_E.getD());   
	}
#endif
	//	for (int c = 0; c < 300; c++){
	//		std::cout<< c <<cells[c]<<std::endl;
	//	}
	return 0; 
}
