#include "mylib.h"
#include "Cell.h"
#include "Point.h"
#include <cmath>
#include <algorithm>
#include <iostream>
#include <vector>

extern int nx; 
extern int ny; 
extern double* x2d; 
extern double* y2d; 
extern Cell* cells;
extern double rho; 
extern double gam; 
extern double P; 
extern double maxU; 
extern double minU; 
extern double getRho(int cellIndex); 
extern int iteration;


//std::vector<double>  linfAvec;
//std::vector<double>  linfBvec;
//std::vector<double>  linfCvec;
//std::vector<double>  linfDvec;

// vector of all U velocitie of all cells at one iteration
extern double* ItVec;
//double* Linf  = new double[3300];

extern double maxA; 
extern double maxB; 
extern double maxC; 
extern double maxD;

extern double L2A;
extern double L2B;
extern double L2C;
extern double L2D;
extern double L2Atot;
extern double L2Btot;
extern double L2Ctot;
extern double L2Dtot;


int
iter()
{
	for (int j = 1; j < 50; j++){//was <=49
		for (int i = 1; i < 66; i++){ //was <= 65
			int c = j * 66+ i; 
			Cell& cur   = cells[c];
			Cell& Left  = cells[c-1]; 
			Cell& Down  = cells[c-66]; 	
			Vec4 E      = cur.m_E; 
			Vec4 E_Left = Left.m_E; 
			Vec4 F      = cur.m_F; 
			Vec4 F_Down = Down.m_F; 

			double t    = cur.timeStep; 
			//double t = 1e-12; 
			double Scsi = cur.m_Arf;
			double Scsil = Left.m_Arf; 
			double Setad = Down.m_Atf; 
			double Seta = cur.m_Atf; 
			double volume = cur.m_Vol; 

			// define new Q atfer deltaT time step
			Vec4 Qnew; 

			//Q first component
			//Qnew1 = QA - t
			double QA      = cur.m_Q.getA();
			double EA      = E.getA();
			double FA      = F.getA();
			double EA_Left = E_Left.getA();
			double FA_Down = F_Down.getA();
			//Qnew.setA((QA - t*(Scsi*(EA-EA_Left)+Seta*(FA-FA_Down)))/volume ); 	
			Qnew.setA(QA - (t/volume)*((Scsi*EA-Scsil*EA_Left)+(Seta*FA-Setad*FA_Down))) ; 	
			//double LinfA = (t/volume)*((Scsi*EA-Scsil*EA_Left)+(Seta*FA-Setad*FA_Down))/1.17 ;
			double LinfA = (t/volume)*((Scsi*EA-Scsil*EA_Left)+(Seta*FA-Setad*FA_Down)) ;
	         	if (std::isnan(LinfA)) {
			        LinfA = 1e-14; 
			}	
		        //std::cout<<c<< " linfa = "<<LinfA<<std::endl;
			
			if (LinfA > maxA) {
				maxA = LinfA; 
				//std::cout<<"cell c "<< c << " maxA = "<<maxA<<std::endl; 
			}	

			//Q second component
			double QB      = cur.m_Q.getB();
			double EB      = E.getB();
			double FB      = F.getB();
			double EB_Left = E_Left.getB();
			double FB_Down = F_Down.getB();
			//Qnew.setB((QB - t*(Scsi*(EB-EB_Left)+Seta*(FB-FB_Down)))/volume ); 	
			Qnew.setB(QB - (t/volume)*((Scsi*EB-Scsil*EB_Left)+(Seta*FB-Setad*FB_Down))); 	
			//double LinfB = (t/volume)*((Scsi*EB-Scsil*EB_Left)+(Seta*FB-Setad*FB_Down))/(1.17*694.4);
			double LinfB = (t/volume)*((Scsi*EB-Scsil*EB_Left)+(Seta*FB-Setad*FB_Down));
	         	if (std::isnan(LinfB)) {
			        LinfB = 1e-14; 
			}	
		        //std::cout<<c<< " linfa = "<<LinfA<<std::endl;
			
			if (LinfB > maxB) {
				maxB = LinfB; 
			}	

			//Q third component
			double QC      = cur.m_Q.getC();
			double EC      = E.getC();
			double FC      = F.getC();
			double EC_Left = E_Left.getC();
			double FC_Down = F_Down.getC();
			//Qnew.setC((QC - t*(Scsi*(EC-EC_Left)+Seta*(FC-FC_Down)))/volume ); 	
			Qnew.setC(QC - (t/volume)*((Scsi*EC-Scsil*EC_Left)+(Seta*FC-Setad*FC_Down))); 	
			//double LinfC = (t/volume)*((Scsi*EC-Scsil*EC_Left)+(Seta*FC-Setad*FC_Down))/(1.17*694.4);
			double LinfC = (t/volume)*((Scsi*EC-Scsil*EC_Left)+(Seta*FC-Setad*FC_Down));
	         	if (std::isnan(LinfC)) {
			        LinfC = 1e-14; 
			}	
		        //std::cout<<c<< " linfa = "<<LinfA<<std::endl;
			
			if (LinfC > maxC) {
				maxC = LinfC; 
			}	


			//Q fourth component
			double QD      = cur.m_Q.getD();
			double ED      = E.getD();
			double FD      = F.getD();
			double ED_Left = E_Left.getD();
			double FD_Down = F_Down.getD();
			//Qnew.setD((QD - t/volumet*(Scsi*(ED-ED_Left)+Seta*(FD-FD_Down)))/volume ); 	
			Qnew.setD(QD - (t/volume)*((Scsi*ED-Scsil*ED_Left)+(Seta*FD-Setad*FD_Down))); 	
			//double LinfD = (t/volume)*((Scsi*ED-Scsil*ED_Left)+(Seta*FD-Setad*FD_Down))/(101325/0.4 + 0.5*1.17*694.4*694.4);
			double LinfD = (t/volume)*((Scsi*ED-Scsil*ED_Left)+(Seta*FD-Setad*FD_Down));
	         	if (std::isnan(LinfD)) {
			        LinfD = 1e-14; 
			}	
		        //std::cout<<c<< " linfa = "<<LinfA<<std::endl;
			
			if (LinfD > maxD) {
				maxD = LinfD; 
			}	

			//update Q
			cur.m_Q = Qnew;
			cur.m_UV.setX(getU(c)); 
			cur.m_UV.setY(getV(c)); 
                        
			//L2 norms
			L2A = L2A + LinfA*LinfA; 
                        L2B = L2B + LinfB*LinfB; 
                        L2C = L2C + LinfC*LinfC; 
                        L2D = L2D + LinfD*LinfD; 
		}
	}
	
	L2Atot = std::sqrt(L2A)/(3300*1.17); 
	L2Btot = std::sqrt(L2B)/(3300*1.17*694.4); 
	L2Ctot = std::sqrt(L2C)/(3300*1.17*694.4); 
	L2Dtot = std::sqrt(L2D)/(3300*(101325/0.4 + 0.5*1.17*694.4*694.4));
//
	std::cout<<"L2Atot = "<<L2Atot<<std::endl; 
	std::cout<<"L2Btot = "<<L2Btot<<std::endl; 
	std::cout<<"L2Ctot = "<<L2Ctot<<std::endl; 
	std::cout<<"L2Dtot = "<<L2Dtot<<std::endl; 
	//
	//std::cout<<"maxA = "<<maxA<<std::endl; 
	//std::cout<<"maxB = "<<maxB<<std::endl; 
	//std::cout<<"maxC = "<<maxC<<std::endl; 
	//std::cout<<"maxD = "<<maxD<<std::endl; 
	
	//linfAvec.push_back(maxA);
	//linfBvec.push_back(maxB);
	//linfCvec.push_back(maxC);
	//linfDvec.push_back(maxD);


	//	Normali(nx, ny, x2d, y2d); 
	//	makeItVec(); 
	//find max and min of itVEC
	//	if (iteration % 10 == 0){
	//		PLOTiter( nx, ny,  x2d,  y2d);
	//	}
	return 0; 
}
