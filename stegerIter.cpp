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
stegerIter()
{
	for (int j = 1; j < 49; j++){
		for (int i = 1; i < 65; i++){
			int c        = j * 66+ i; 
			Cell& cur    = cells[c];
			int ii       = cur.m_i; 
			int jj       = cur.m_j;
			Point cellPoint(ii,jj); 
			Cell& Left   = cells[c-1]; 
			Cell& Right  = cells[c+1]; 
			Cell& Down   = cells[c-66]; 	
			Cell& Up     = cells[c+66]; 	
			Vec4 Em      = cur.m_E_m; 
			Vec4 Ep      = cur.m_E_p; 
			Vec4 E_Left  = Left.m_E_p; 
			Vec4 E_Right = Right.m_E_m; 
			Vec4 Fm      = cur.m_F_m; 
			Vec4 Fp      = cur.m_F_p; 
			Vec4 F_Down  = Down.m_F_p; 
			Vec4 F_Up    = Up.m_F_m; 

			double t    = cur.timeStep; 
			//double t = 1e-12; 
			double Scsi = cur.m_Arf;
			double Scsil = Left.m_Arf; 
			double Setad = Down.m_Atf; 
			double Seta = cur.m_Atf; 
			double volume = cur.m_Vol; 
			//double dx = getSetaX(cellPoint); 
			double dx = 0.03; 
			//double dy = getScsiY(cellPoint); 

			// define new Q atfer deltaT time step
			Vec4 Qnew; 

			//Q first component
			//Qnew1 = QA - t
			double QA        = cur.m_Q.getA();
			double EAp       = Ep.getA();
			double EAm       = Em.getA(); 
			double FAm       = Fm.getA();
			double FAp       = Fp.getA();
			double EA_Leftp  = E_Left.getA();
			double EA_Rightm = E_Right.getA();
			double FA_Downp  = F_Down.getA();
			double FA_Upm    = F_Up.getA();
			//Qnew.setA((QA - t*(Scsi*(EA-EA_Left)+Seta*(FA-FA_Down)))/volume ); 	
			Qnew.setA(QA - t/dx*((EAp-EA_Leftp)+(EA_Rightm-EAm) + (FAp-FA_Downp)+(FA_Upm-FAm))) ; 	
			//double LinfA = t/dx*((EAp-EA_Leftp)+(EA_Rightm-EAm) + (FAp-FA_Downp)+(FA_Upm-FAm))/1.17 ;
			double LinfA = t/dx*((EAp-EA_Leftp)+(EA_Rightm-EAm) + (FAp-FA_Downp)+(FA_Upm-FAm))/1.17 ;
                        if (std::isnan(LinfA)) {
                                LinfA = 1e-14;
                        }
                        //std::cout<<c<< " linfa = "<<LinfA<<std::endl;

                        if (LinfA > maxA) {
                                maxA = LinfA;
                                //std::cout<<"cell c "<< c << " maxA = "<<maxA<<std::endl;
                        }

				
			//Q second component
			//Qnew1 = QA - t
			double QB        = cur.m_Q.getB();
			double EBp       = Ep.getB();
			double EBm       = Em.getB(); 
			double FBm       = Fm.getB();
			double FBp       = Fp.getB();
			double EB_Leftp  = E_Left.getB();
			double EB_Rightm = E_Right.getB();
			double FB_Downp  = F_Down.getB();
			double FB_Upm    = F_Up.getB();
			//Qnew.setB((QB - t*(Scsi*(EB-EB_Left)+Seta*(FB-FB_Down)))/volume ); 	
			Qnew.setB(QB - t/dx*((EBp-EB_Leftp)+(EB_Rightm-EBm) + (FBp-FB_Downp)+(FB_Upm-FBm))) ;
		        //double LinfB = t/dx*((EAp-EA_Leftp)+(EA_Rightm-EAm) + (FAp-FA_Downp)+(FA_Upm-FAm))/ (1.17*694.4);
		        double LinfB = t/dx*((EBp-EB_Leftp)+(EB_Rightm-EBm) + (FBp-FB_Downp)+(FB_Upm-FBm))/(1.17*694);
                        if (std::isnan(LinfB)) {
                                LinfB = 1e-14;
                        }
                        //std::cout<<c<< " linfB = "<<LinfA<<std::endl;

                        if (LinfB > maxB) {
                                maxB = LinfB;
                                //std::cout<<"cell c "<< c << " maxB = "<<maxA<<std::endl;
                        }
	

			//Q third component
			//Qnew1 = QC - t
			double QC        = cur.m_Q.getC();
			double ECp       = Ep.getC();
			double ECm       = Em.getC(); 
			double FCm       = Fm.getC();
			double FCp       = Fp.getC();
			double EC_Leftp  = E_Left.getC();
			double EC_Rightm = E_Right.getC();
			double FC_Downp  = F_Down.getC();
			double FC_Upm    = F_Up.getC();
			//Qnew.setC((QC - t*(Scsi*(EC-EC_Left)+Seta*(FC-FC_Down)))/volume ); 	
			Qnew.setC(QC - t/dx*((ECp-EC_Leftp)+(EC_Rightm-ECm) + (FCp-FC_Downp)+(FC_Upm-FCm))) ;
		        //double LinfC = t/dx*((EAp-EA_Leftp)+(EA_Rightm-EAm) + (FAp-FA_Downp)+(FA_Upm-FAm))/ (1.17*694.4);
		        double LinfC = t/dx*((ECp-EC_Leftp)+(EC_Rightm-ECm) + (FCp-FC_Downp)+(FC_Upm-FCm))/ (1.17*694.4);
                        if (std::isnan(LinfC)) {
                                LinfC = 1e-14;
                        }
                        //std::cout<<c<< " linfC = "<<LinfA<<std::endl;

                        if (LinfC > maxC) {
                                maxC = LinfC;
                                //std::cout<<"cell c "<< c << " maxC = "<<maxA<<std::endl;
                        }
	

			//Q fourth component
			//Qnew1 = QD - t
			double QD        = cur.m_Q.getD();
			double EDp       = Ep.getD();
			double EDm       = Em.getD(); 
			double FDm       = Fm.getD();
			double FDp       = Fp.getD();
			double ED_Leftp  = E_Left.getD();
			double ED_Rightm = E_Right.getD();
			double FD_Downp  = F_Down.getD();
			double FD_Upm    = F_Up.getD();
			//Qnew.setD((QD - t*(Scsi*(ED-ED_Left)+Seta*(FD-FD_Down)))/volume ); 	
			Qnew.setD(QD - t/dx*((EDp-ED_Leftp)+(ED_Rightm-EDm) + (FDp-FD_Downp)+(FD_Upm-FDm))) ; 
		        //double LinfD = t/dx*((EAp-EA_Leftp)+(EA_Rightm-EAm) + (FAp-FA_Downp)+(FA_Upm-FAm))/ (101325/0.4 + 0.5*1.17*694.4*694.4);
		        double LinfD = t/dx*((EDp-ED_Leftp)+(ED_Rightm-EDm) + (FDp-FD_Downp)+(FD_Upm-FDm))/(101325/0.4 + 0.5*1.17*694.4*694.4);
                        if (std::isnan(LinfD)) {
                                LinfD = 1e-14;
                        }
                        //std::cout<<c<< " linfD = "<<LinfA<<std::endl;

                        if (LinfD > maxD) {
                                maxD = LinfD;
                                //std::cout<<"cell c "<< c << " maxD = "<<maxA<<std::endl;
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
	
	
	//L2Atot = std::sqrt(L2A)/(3300*1.17); 
	//L2Btot = std::sqrt(L2B)/(3300*1.17*694.4); 
	//L2Ctot = std::sqrt(L2C)/(3300*1.17*694.4); 
	//L2Dtot = std::sqrt(L2D)/(3300*(101325/0.4 + 0.5*1.17*694.4*694.4));
	L2Atot = std::sqrt(L2A); 
	L2Btot = std::sqrt(L2B); 
	L2Ctot = std::sqrt(L2C); 
	L2Dtot = std::sqrt(L2D);

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
