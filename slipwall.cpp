#include "mylib.h"
#include "Cell.h"
#include "Point.h"
#include <cmath>

extern Cell* cells;
extern double rho; 
extern double gam; 
extern double p; 


	
	
int
slipwall()
{
	for (int c = 17; c <= 33; c++){
		//get halo cell c
		Cell& cur = cells[c];

		//point cellPoint to use to find ParDir
		Point cp(c, 0); 
		//find parallel direction to halo cell top face
		Vec2 Par = getParDir(cp); 

                double volume = cur.m_Vol; 
		//get cell on top of halo cell	
		Cell& cellONtop = cells[c + 66];

		// U parallel
		double Ucsi_par = volume*cellONtop.m_UV.scal(Par);	
		//Velocity peropendicular to cell face
		double Vperp    = volume*cellONtop.m_UV.scal(cur.m_nEta); 
                double alpha = atan(Vperp/Ucsi_par); 
		double Ucell = getU(c)*volume;
		double Vcell = getV(c)*volume;
                double moduloUV = sqrt(Ucell*Ucell + Vcell*Vcell); 
		//set UV of halo: U is equal to UcsiPAR, V is oppposite of V of top cell
		cur.m_UV.setX ( moduloUV*cos(alpha + (10 * M_PI/180.0))); 
		cur.m_UV.setY ( moduloUV*sin(alpha + (10 + M_PI/180.0)));
	        //cellONtop.m_UV.setX(Ucsi_par); 
	        //cellONtop.m_UV.setY(Vperp); 
	        //Q    
                cur.m_Q.setA((getRho(c))*volume);
                cur.m_Q.setB(getRho(c) * Ucell);
                cur.m_Q.setC(getRho(c) * Vcell);
                cur.m_Q.setD((getP(c)/(gam - 1.0) + 0.5*getRho(c)*( cur.m_UV.getX() * cur.m_UV.getX() + cur.m_UV.getY() * cur.m_UV.getY() ))*volume);
	

	}

for (int c = 33; c <= 49; c++){
                //get halo cell c
                Cell& cur = cells[c];

                //point cellPoint to use to find ParDir
                Point cp(c, 0);
                //find parallel direction to halo cell top face
                Vec2 Par = getParDir(cp);

                double volume = cur.m_Vol;
                //get cell on top of halo cell  
                Cell& cellONtop = cells[c + 66];

                // U parallel
                double Ucsi_par = volume*cellONtop.m_UV.scal(Par);
                //Velocity peropendicular to cell face
                double Vperp    = volume*cellONtop.m_UV.scal(cur.m_nEta);
                double alpha = atan(Vperp/Ucsi_par);
                double Ucell = getU(c);
                double moduloUV = sqrt(getU(c)*getU(c) + getV(c)*getV(c));
                //set UV of halo: U is equal to UcsiPAR, V is oppposite of V of top cell
                cur.m_UV.setX ( moduloUV*cos(alpha + (10 * M_PI/180.0)));
                cur.m_UV.setY (- moduloUV*sin(alpha + (10 + M_PI/180.0)));
                //cellONtop.m_UV.setX(Ucsi_par); 
                //cellONtop.m_UV.setY(Vperp); 

	        //Q    
                cur.m_Q.setA((getRho(c))*volume);
                cur.m_Q.setB(getRho(c) * cur.m_UV.getX());
                cur.m_Q.setC(getRho(c) * cur.m_UV.getY());
                cur.m_Q.setD((getP(c)/(gam - 1.0) + 0.5*getRho(c)*( cur.m_UV.getX() * cur.m_UV.getX() + cur.m_UV.getY() * cur.m_UV.getY() ))*volume);

        }
for (int c = 0; c <= 16; c++){
                //get halo cell c
                Cell& cur = cells[c];

                //point cellPoint to use to find ParDir
                Point cp(c, 0);
                //find parallel direction to halo cell top face
                Vec2 Par = getParDir(cp);

                double volume = cur.m_Vol;
                //get cell on top of halo cell  
                Cell& cellONtop = cells[c + 66];

                // U parallel
                double Ucsi_par = volume*cellONtop.m_UV.scal(Par);
                //Velocity peropendicular to cell face
                double Vperp    = volume*cellONtop.m_UV.scal(cur.m_nEta);
                double alpha = atan(Vperp/Ucsi_par);
                double Ucell = getU(c);
                double moduloUV = sqrt(getU(c)*getU(c) + getV(c)*getV(c));
                //set UV of halo: U is equal to UcsiPAR, V is oppposite of V of top cell
                cur.m_UV.setX ( moduloUV*cos(alpha + (0 * M_PI/180.0)));
                cur.m_UV.setY ( moduloUV*sin(alpha + (0 + M_PI/180.0)));
                //cellONtop.m_UV.setX(Ucsi_par); 
                //cellONtop.m_UV.setY(Vperp); 

	        //Q    
                cur.m_Q.setA((getRho(c))*volume);
                cur.m_Q.setB(getRho(c) * cur.m_UV.getX());
                cur.m_Q.setC(getRho(c) * cur.m_UV.getY());
                cur.m_Q.setD((getP(c)/(gam - 1.0) + 0.5*getRho(c)*( cur.m_UV.getX() * cur.m_UV.getX() + cur.m_UV.getY() * cur.m_UV.getY() ))*volume);

        }

for (int c = 50; c <= 65; c++){
                //get halo cell c
                Cell& cur = cells[c];

                //point cellPoint to use to find ParDir
                Point cp(c, 0);
                //find parallel direction to halo cell top face
                Vec2 Par = getParDir(cp);

                double volume = cur.m_Vol;
                //get cell on top of halo cell
                Cell& cellONtop = cells[c + 66];

                // U parallel
                double Ucsi_par = volume*cellONtop.m_UV.scal(Par);
                //Velocity peropendicular to cell face
                double Vperp    = volume*cellONtop.m_UV.scal(cur.m_nEta);
                double alpha = atan(Vperp/Ucsi_par);
                double Ucell = getU(c);
                double moduloUV = sqrt(getU(c)*getU(c) + getV(c)*getV(c));
                //set UV of halo: U is equal to UcsiPAR, V is oppposite of V of top cell
                cur.m_UV.setX ( moduloUV*cos(alpha + (0 * M_PI/180.0)));
                cur.m_UV.setY ( moduloUV*sin(alpha + (0 + M_PI/180.0)));
                //cellONtop.m_UV.setX(Ucsi_par);
                //cellONtop.m_UV.setY(Vperp);

	        //Q    
                cur.m_Q.setA((getRho(c))*volume);
                cur.m_Q.setB(getRho(c) * cur.m_UV.getX());
                cur.m_Q.setC(getRho(c) * cur.m_UV.getY());
                cur.m_Q.setD((getP(c)/(gam - 1.0) + 0.5*getRho(c)*( cur.m_UV.getX() * cur.m_UV.getX() + cur.m_UV.getY() * cur.m_UV.getY() ))*volume);

        }

for (int c = 3300 - 66; c < 3300; c++){
                //get halo cell c
                Cell& cur = cells[c];

                //point cellPoint to use to find ParDir
                Point cp(c, 0);
                //find parallel direction to halo cell top face
                Vec2 Par = getParDir(cp);

                double volume = cur.m_Vol;
                //get cell on top of halo cell  
                Cell& cellUNDERtop = cells[c - 66];

                // U parallel
                double Ucsi_par = volume*cellUNDERtop.m_UV.scal(Par);
                //Velocity peropendicular to cell face
                double Vperp    = volume*cellUNDERtop.m_UV.scal(cur.m_nEta);
                double alpha = atan(Vperp/Ucsi_par);
                double Ucell = getU(c);
                double moduloUV = sqrt(getU(c)*getU(c) + getV(c)*getV(c));
                //set UV of halo: U is equal to UcsiPAR, V is oppposite of V of top cell
                cur.m_UV.setX ( moduloUV*cos(alpha + (0 * M_PI/180.0)));
                cur.m_UV.setY ( moduloUV*sin(alpha + (0 + M_PI/180.0)));
                //cellONtop.m_UV.setX(Ucsi_par); 
                //cellONtop.m_UV.setY(Vperp); 


	        //Q    
                cur.m_Q.setA((getRho(c))*volume);
                cur.m_Q.setB(getRho(c) * cur.m_UV.getX());
                cur.m_Q.setC(getRho(c) * cur.m_UV.getY());
                cur.m_Q.setD((getP(c)/(gam - 1.0) + 0.5*getRho(c)*( cur.m_UV.getX() * cur.m_UV.getX() + cur.m_UV.getY() * cur.m_UV.getY() ))*volume);
        }

//	std::cout<<cells[68];
//	std::cout<<cells[69];

	return 0; 
}
