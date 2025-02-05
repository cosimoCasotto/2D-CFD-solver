#include "mylib.h"
#include "Cell.h"
#include "Point.h"
#include <cmath>

extern Cell* cells;
extern double rho; 
extern double gam; 
extern double P; 

int
stegerFluxcalc()
{
	for (int c = 0; c < 3300; c++){
		Cell& cur = cells[c]; 

		double u = getU(c);  
		double v = getV(c);
	        double rho = getRho(c); 
	        double T = getT(c); 
	        double ss = std::sqrt(1.4*287*T); 
		double eps = 0.04; 
		        //lamE and lamF	
			Vec4 lamE; lamE.setA(u); lamE.setB(u); lamE.setC(u+ss); lamE.setD(u-ss);    
			Vec4 lamF; lamF.setA(v); lamF.setB(v); lamF.setC(v+ss); lamF.setD(v-ss);
		        	

			Vec4 lamE_p; lamE_p.setA(0.5* u     + 0.5*std::sqrt( u*u          + eps*eps)); 
			             lamE_p.setB(0.5* u     + 0.5*std::sqrt( u*u          + eps*eps)); 
			             lamE_p.setC(0.5*(u+ss) + 0.5*std::sqrt((u+ss)*(u+ss) + eps*eps)); 
			             lamE_p.setD(0.5*(u-ss) + 0.5*std::sqrt((u-ss)*(u-ss) + eps*eps));

			Vec4 lamE_m; lamE_m.setA(0.5* u     - 0.5*std::sqrt( u*u          + eps*eps)); 
			             lamE_m.setB(0.5* u     - 0.5*std::sqrt( u*u          + eps*eps)); 
			             lamE_m.setC(0.5*(u+ss) - 0.5*std::sqrt((u+ss)*(u+ss) + eps*eps)); 
			             lamE_m.setD(0.5*(u-ss) - 0.5*std::sqrt((u-ss)*(u-ss) + eps*eps)); 

			Vec4 lamF_m; lamE_m.setA(0.5* v     - 0.5*std::sqrt( v*v          + eps*eps)); 
			             lamF_m.setB(0.5* v     - 0.5*std::sqrt( v*v          + eps*eps)); 
			             lamF_m.setC(0.5*(v+ss) - 0.5*std::sqrt((v+ss)*(v+ss) + eps*eps)); 
			             lamF_m.setD(0.5*(v-ss) - 0.5*std::sqrt((v-ss)*(v-ss) + eps*eps)); 

			Vec4 lamF_p; lamE_p.setA(0.5* v     + 0.5*std::sqrt( v*v          + eps*eps)); 
			             lamF_p.setB(0.5* v     + 0.5*std::sqrt( v*v          + eps*eps)); 
			             lamF_p.setC(0.5*(v+ss) + 0.5*std::sqrt((v+ss)*(v+ss) + eps*eps)); 
			             lamF_p.setD(0.5*(v-ss) + 0.5*std::sqrt((v-ss)*(v-ss) + eps*eps));

		        double alphap = 2*0.4*lamE_p.getA() + lamE_p.getC() + lamE_p.getD(); 	
		        double alpham = 2*0.4*lamE_m.getA() + lamE_m.getC() + lamE_m.getD(); 	
		        //double alphaEp = 2*0.4*lamE_p.getA() + lamE_p.getC() + lamE_p.getD(); 	
		        //double alphaEm = 2*0.4*lamE_m.getA() + lamE_m.getC() + lamE_m.getD(); 	
		        //double alphaFp = 2*0.4*lamF_p.getA() + lamF_p.getC() + lamF_p.getD(); 	
		        //double alphaFm = 2*0.4*lamF_m.getA() + lamF_m.getC() + lamF_m.getD(); 	


		//calculate E_m    
		cur.m_E_m.setA(0.5*rho/1.4 *  alpham) ; 
		cur.m_E_m.setB(0.5*rho/1.4 * (alpham*u + ss*(lamE_m.getC() + lamE_m.getD()))); 
		cur.m_E_m.setC(0.5*rho/1.4 *  alpham*v); 
		cur.m_E_m.setD(0.5*rho/1.4 * (0.5*alpham*(u*u+v*v) + u*ss*(lamE_m.getC() + lamE_m.getD()) + ss*ss*(lamE_m.getC() + lamE_m.getD())/0.4)) ;

		//calculate E_p    
		cur.m_E_p.setA(0.5*rho/1.4 *  alphap) ; 
		cur.m_E_p.setB(0.5*rho/1.4 * (alphap*u + ss*(lamE_p.getC() + lamE_p.getD()))); 
		cur.m_E_p.setC(0.5*rho/1.4 *  alphap*v); 
		cur.m_E_p.setD(0.5*rho/1.4 * (0.5*alphap*(u*u+v*v) + u*ss*(lamE_p.getC() + lamE_p.getD()) + ss*ss*(lamE_p.getC() + lamE_p.getD())/0.4)) ;
		

		//calculate F_m    
		cur.m_F_m.setA(0.5*rho/1.4 *  alpham) ; 
		cur.m_F_m.setB(0.5*rho/1.4 *  alpham*u); 
		cur.m_F_m.setC(0.5*rho/1.4 * (alpham*v + ss * (lamF_m.getC() - lamF_m.getD()))); 
		cur.m_F_m.setD(0.5*rho/1.4 * (0.5*alpham*(u*u+v*v) + v*ss*(lamF_m.getC() - lamF_m.getD()) + ss*ss*(lamF_m.getC() + lamF_m.getD())/0.4)) ;

		//calculate F_p    
		cur.m_F_p.setA(0.5*rho/1.4 *  alphap); 
		cur.m_F_p.setB(0.5*rho/1.4 *  alphap*u); 
		cur.m_F_p.setC(0.5*rho/1.4 * (alphap*v + ss * (lamF_p.getC() - lamF_p.getD()))); 
		cur.m_F_p.setD(0.5*rho/1.4 * (0.5*alphap*(u*u+v*v) + v*ss*(lamF_p.getC() - lamF_p.getD()) + ss*ss*(lamF_p.getC() + lamF_p.getD())/0.4)) ;
	}
//	std::cout<<"after flux calc: "<<std::endl;
//	std::cout<<cells[0];
//      std::cout<<cells[68];
//      std::cout<<cells[69];
	return 0; 
}
