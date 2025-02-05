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
stegerinitializeQ()
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
		cur.m_Q.setD(P/0.4 + 0.5*rho*694.4*694.4);

		double ss = std::sqrt(1.4*287*300);
		double eps = 0.04;
		//lamE and lamF
		Vec4 lamE; lamE.setA(694.4); lamE.setB(694.4); lamE.setC(694.4+ss); lamE.setD(694.4-ss);
		Vec4 lamF; lamF.setA(0); lamF.setB(0); lamF.setC(0+ss); lamF.setD(0-ss);


		Vec4 lamE_p; lamE_p.setA(0.5* 694.4     + 0.5*std::sqrt( 694.4    * 694.4     + eps*eps));
		             lamE_p.setB(0.5* 694.4     + 0.5*std::sqrt( 694.4    * 694.4     + eps*eps));
		             lamE_p.setC(0.5*(694.4+ss) + 0.5*std::sqrt((694.4+ss)*(694.4+ss) + eps*eps));
		             lamE_p.setD(0.5*(694.4-ss) + 0.5*std::sqrt((694.4-ss)*(694.4-ss) + eps*eps));

		Vec4 lamE_m; lamE_m.setA(0.5* 694.4     - 0.5*std::sqrt( 694.4    * 694.4     + eps*eps));
		             lamE_m.setB(0.5* 694.4     - 0.5*std::sqrt( 694.4    * 694.4     + eps*eps));
		             lamE_m.setC(0.5*(694.4+ss) - 0.5*std::sqrt((694.4+ss)*(694.4+ss) + eps*eps));
		             lamE_m.setD(0.5*(694.4-ss) - 0.5*std::sqrt((694.4-ss)*(694.4-ss) + eps*eps));

		Vec4 lamF_m; lamE_m.setA(0.5* 0     - 0.5*std::sqrt( 0*0          + eps*eps));
		             lamF_m.setB(0.5* 0     - 0.5*std::sqrt( 0*0          + eps*eps));
		             lamF_m.setC(0.5*(0+ss) - 0.5*std::sqrt((0+ss)*(0+ss) + eps*eps));
		             lamF_m.setD(0.5*(0-ss) - 0.5*std::sqrt((0-ss)*(0-ss) + eps*eps));

		Vec4 lamF_p; lamE_p.setA(0.5* 0     + 0.5*std::sqrt( 0*0          + eps*eps));
		             lamF_p.setB(0.5* 0     + 0.5*std::sqrt( 0*0          + eps*eps));
		             lamF_p.setC(0.5*(0+ss) + 0.5*std::sqrt((0+ss)*(0+ss) + eps*eps));
		             lamF_p.setD(0.5*(0-ss) + 0.5*std::sqrt((0-ss)*(0-ss) + eps*eps));

		double alphap = 2*0.4*lamE_p.getA() + lamE_p.getC() + lamE_p.getD();
		double alpham = 2*0.4*lamE_m.getA() + lamE_m.getC() + lamE_m.getD();
		//double alphaEp = 2*0.4*lamE_p.getA() + lamE_p.getC() + lamE_p.getD();
		//double alphaEm = 2*0.4*lamE_m.getA() + lamE_m.getC() + lamE_m.getD();
		//double alphaFp = 2*0.4*lamF_p.getA() + lamF_p.getC() + lamF_p.getD();
		//double alphaFm = 2*0.4*lamF_m.getA() + lamF_m.getC() + lamF_m.getD();

		//calculate E_m    
		cur.m_E_m.setA(0.5*rho/1.4 *  alpham) ;
		cur.m_E_m.setB(0.5*rho/1.4 * (alpham*694.4 + ss*(lamE_m.getC() + lamE_m.getD())));
		cur.m_E_m.setC(0.5*rho/1.4 *  alpham*0);
		cur.m_E_m.setD(0.5*rho/1.4 * (0.5*alpham*(694.4*694.4+0*0) + 694.4*ss*(lamE_m.getC() + lamE_m.getD()) + ss*ss*(lamE_m.getC() + lamE_m.getD())/0.4)) ;

		//calculate E_p    
		cur.m_E_p.setA(0.5*rho/1.4 *  alphap) ;
		cur.m_E_p.setB(0.5*rho/1.4 * (alphap*694.4 + ss*(lamE_p.getC() + lamE_p.getD())));
		cur.m_E_p.setC(0.5*rho/1.4 *  alphap*0);
		cur.m_E_p.setD(0.5*rho/1.4 * (0.5*alphap*(694.4*694.4+0*0) + 694.4*ss*(lamE_p.getC() + lamE_p.getD()) + ss*ss*(lamE_p.getC() + lamE_p.getD())/0.4)) ;


		//calculate F_m    
		cur.m_F_m.setA(0.5*rho/1.4 *  alpham) ;
		cur.m_F_m.setB(0.5*rho/1.4 *  alpham*694.4);
		cur.m_F_m.setC(0.5*rho/1.4 * (alpham*0 + ss * (lamF_m.getC() - lamF_m.getD())));
		cur.m_F_m.setD(0.5*rho/1.4 * (0.5*alpham*(694.4*694.4+0*0) + 0*ss*(lamF_m.getC() - lamF_m.getD()) + ss*ss*(lamF_m.getC() + lamF_m.getD())/0.4)) ;

		//calculate F_p    
		cur.m_F_p.setA(0.5*rho/1.4 * alphap) ;
		cur.m_F_p.setB(0.5*rho/1.4 * alphap*694.4);
		cur.m_F_p.setC(0.5*rho/1.4 * (alphap*0 + ss * (lamF_p.getC() - lamF_p.getD())));
		cur.m_F_p.setD(0.5*rho/1.4 * (0.5*alphap*(694.4*694.4+0*0) + 0*ss*(lamF_p.getC() - lamF_p.getD()) + ss*ss*(lamF_p.getC() + lamF_p.getD())/0.4)) ;






	}
	//	for (int c = 0; c < 300; c++){
	//		std::cout<< c <<cells[c]<<std::endl;
	//	}
	return 0; 
}
