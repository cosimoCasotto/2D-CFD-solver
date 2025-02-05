#include "mylib.h"
#include "Cell.h"
#include "Point.h"
#include <cmath>

extern Cell* cells;
extern double gam;
extern double P;
extern int R;
extern int T;
extern double U;
extern double rho;


	int
timeStep()
{
	double cfl = 0.3; 
	for (int ind = 0; ind < 3300; ind++){
		Cell& cur = cells[ind];
		int iindex = cur.m_i; 
		int jindex = cur.m_j;
	        Point blPoint(iindex,jindex); 
	        Point rigthPoint = getRightPoint(blPoint); 	
	        Point topPoint   = getUpPoint(blPoint); 	
		double deltaX = Xdist (blPoint, rigthPoint); 
		double deltaY = Ydist (blPoint, topPoint); 
		double Cellrho = getRho(ind); 
		double CellP   = getP(ind) ; 
	        double Tcell   = CellP/(287*Cellrho); 	
		//find sound speed of cell
		double c = std::sqrt(1.4*287*Tcell);
		double u = getU(ind); 
		double v = getV(ind); 
		Vec2 UV; UV.setX(u); UV.setY(v); 
		double Ucsi = UV.scal(cur.m_nCsi); 
		double Veta = UV.scal(cur.m_nEta); 
		double specCsi = std::abs(Ucsi) + c;  
		double specEta = std::abs(Veta) + c; 
	       	double ts1 = specCsi > 0.0 ? deltaX/specCsi : 100; 
	       	double ts2 = specEta > 0.0 ? deltaY/specEta : 100; 
		cur.timeStep   = cfl*std::min(ts1, ts2);
	        //std::cout<<"cell "<<ind<<"th"<<"time step = "<<cur.timeStep<<std::endl; 	
	}
	return 0; 
}
