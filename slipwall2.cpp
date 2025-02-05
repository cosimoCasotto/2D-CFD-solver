#include "mylib.h"
#include "Cell.h"
#include "Point.h"
#include <cmath>

extern Cell* cells;
extern double rho; 
extern double gam; 
extern double p; 

int
slipwall2()
{
	for (int c = 0; c < 66; c++){
		Cell& halo = cells[c]; 
		Cell& aboveCell = cells[c+66]; 
		double u1 = getU(c+66); 
		double v1 = getV(c+66); 
		int i = halo.m_i; 
		int j = halo.m_j; 
		Point cp(i,j);  
		double SetaY = getSetaY(cp); 
		double SetaX = getSetaX(cp);
		//std::cout<<cp<<" Seta X = " << SetaX << ", Seta Y = " << SetaY<<std::endl; 
		//std::cout<<"/////////////////////////////////"<<std::endl; 	

		double Seta_quadro = SetaX *SetaX + SetaY*SetaY; 
		double a =  SetaY * u1 - SetaX * v1; 
		double b = -SetaX * u1 - SetaY * v1; 
		double u0 = 1/Seta_quadro * ( SetaY*(a) + SetaX*(b)); 
		double v0 = 1/Seta_quadro * (-SetaX*(a) + SetaY*(b));

		double rho = getRho(c+66); 
		double P = getP(c+66); 

		halo.m_Q.setA(rho); 
		halo.m_Q.setB(rho*u0);
		halo.m_Q.setC(rho*v0);
		halo.m_Q.setD(P/0.4 + 0.5*rho*(u0*u0 + v0*v0));

		//std::cout<<"halo cell (" << c << ") "<< "u0 = "<<u0 <<" v0 = "<< v0<<std::endl;    
		//std::cout<<"cell above (" << c << ") "<< "u1 = "<<u1 <<" v1 = "<< v1<<std::endl;    
		//std::cout<<"///////////////////////////////////"<<std::endl;    
	}


	for (int c = 3300 - 66; c < 3300 ; c++){
		Cell& halo = cells[c];
		double u1 = getU(c-66);
		double v1 = getV(c-66);
		int i = halo.m_i;
		int j = halo.m_j;
		Point cp(i,j-1);
		double SetaX = getSetaX(cp);
		double SetaY = getSetaY(cp);

		double Seta_quadro = SetaX *SetaX + SetaY*SetaY;
		double a =  SetaY * u1 - SetaX * v1;
		double b = -SetaX * u1 - SetaY * v1;
		double u0 = 1/Seta_quadro * ( SetaY*(a) + SetaX*(b));
		double v0 = 1/Seta_quadro * (-SetaX*(a) + SetaY*(b));

		double rho = getRho(c-66);
		double P = getP(c-66);

		halo.m_Q.setA(rho);
		halo.m_Q.setB(rho*u0);
		halo.m_Q.setC(rho*v0);
		halo.m_Q.setD(P/0.4 + 0.5*rho*(u0*u0 + v0*v0));
		//		//std::cout<<"halo cell (" << c << ") "<< "u0 = "<<u0 <<" v0 = "<< v0<<std::endl;
		//               //std::cout<<"cell below (" << c << ") "<< "u1 = "<<u1 <<" v1 = "<< v1<<std::endl;
		//              //std::cout<<"///////////////////////////////////"<<std::endl;
		//

			}

		return 0; 
}
