#include "mylib.h"
#include "Cell.h"
#include "Point.h"
#include <cmath>
#include <iostream>


extern Cell* cells;


double
getRho(int c)
{
	Cell& cell = cells[c]; 
	double Cellrho = cell.m_Q.getA(); 
	return Cellrho; 
}

double
getU(int c)
{
	Cell& cell = cells[c]; 
	double rho = cell.m_Q.getA(); 
	double CellU = rho > 0.0 ? cell.m_Q.getB()/rho : 694.9; 
	return CellU; 
}

double
getV(int c)
{
	Cell& cell = cells[c]; 
	double rho = cell.m_Q.getA();
	double CellV = rho > 0.0 ? cell.m_Q.getC()/rho : 1.0 ; 
	return CellV;
}

double 
getT(int c)
{
	Cell& cell = cells[c]; 
	double rho = getRho(c); 
	double P = getP (c); 
	double T = rho > 0?  P/(rho*287) : 300; 
	return T; 
}
	double 
getE0(int c)
{
	Cell& cell = cells[c]; 
	double rho = getRho(c);
	double E0 = rho > 0.0 ? cell.m_Q.getD()/rho : 900.0 ; 
	return E0; 
}


	double 
getUcsi(int c)
{
	Cell& cell = cells[c];
	double u = getU(c); 
	double v = getV(c); 
	Vec2 UV; UV.setX(u); UV.setY(u); 
	Vec2 nCsi = cell.m_nCsi; 	
	double Ucsi = UV.scal(nCsi); 
	return Ucsi; 
}

	double 
getVeta(int c)
{
	Cell& cell = cells[c];
	double u = getU(c); 
	double v = getV(c); 
	Vec2 UV; UV.setX(u); UV.setY(u); 
	Vec2 nEta = cell.m_nEta; 	
	double Veta = UV.scal(nEta); 
	if (std::isnan(Veta)) {
		std::cout << "error!"; 
	}
	return Veta; 
}

	double 
getB (int c)
{
	Cell& cell = cells[c]; 
	double B = cell.m_E.getB(); 
	return B; 
}

	double 
getP(int c)
{
	Cell& cell   = cells[c]; 
	double rhoet = cell.m_Q.getD(); 
	double rho   = cell.m_Q.getA(); 
	double u     = getU(c); 
	double v     = getV(c); 
	double cellP = 0.4*(rhoet - 0.5 * rho * (u * u + v * v)); 

	//std::cout<<"     cellP =  " << cellP << "for cell : " << c<<std::endl;

	return cellP; 
}
