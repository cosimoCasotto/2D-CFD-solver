#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gd.h>
#include <iostream>
#include <cmath>
#include "Point.h"
#include "Cell.h"
#include "mylib.h"
#include "vector"
#include <fstream>


//scaling factors used to plot grid 
double         sx = 400; 
double         sy = 400;
//extrenal variables
double maxA = 10.0; 
double maxB = 10.0; 
double maxC = 10.0; 
double maxD = 10.0; 
double L2A = 0.0; 
double L2B = 0.0; 
double L2C = 0.0; 
double L2D = 0.0; 
double L2Atot = 0.0; 
double L2Btot = 0.0; 
double L2Ctot = 0.0; 
double L2Dtot = 0.0; 
extern int     nx,ny;  
extern double* x2d; 
extern double* y2d; 
extern double  maxU; 
//create cell array of 3300 cells
Cell* cells = new Cell[3300]; 
int g_MaxIter = 100; 
int g_ShowWhat = 0; // 0 is pressure 
int g_numberOfPlots = 100;
//extern double L; //from iter

int 
main(int argc, char* argv[])
{
	//define max iterations, what qunatity to plot, and the number of plots to create
	for (int i = 1; i < argc - 1 ; i++){
		if (strcmp( argv[i], "-m") == 0){
			g_MaxIter = atoi(argv[i+1]);
		} 
		if (strcmp( argv[i], "-s") == 0){
			g_ShowWhat = atoi(argv[i+1]);
		} 
		if (strcmp( argv[i], "-p") == 0){
			g_numberOfPlots = atoi(argv[i+1]);
		} 
	}
	// Vectors to store values for plotting
	std::vector<double> maxA_values;
	std::vector<double> maxB_values;
	std::vector<double> maxC_values;
	std::vector<double> maxD_values;
	std::vector<double> L2Atot_values;
	std::vector<double> L2Btot_values;
	std::vector<double> L2Ctot_values;
	std::vector<double> L2Dtot_values;
	// Call readgrid function to read grid from .dat file
	if (readgrid() != 0) {
		std::cerr << "Error reading grid from file" << std::endl;
		return 1; // Return error code if reading grid fails
	}

	// Call plotgrid function to plot the grid
	plotgrid(nx, ny, x2d, y2d);

	// call calcCell to calculate all cell areas and volumes 
	calcCell(); 
	
	//Initiualize Q vector in all cells using U = 694.4 m/s
	//initializeQ(); 
        stegerinitializeQ(); 
	
	//define wall conditions
	slipwall2();
	
	//calculate E(Q) and F(Q)
	//Fluxcalc(); 
	stegerFluxcalc(); 
	
	//find local time step for each cell
	timeStep();
	
	//ectract values of quantities to plot
	makeItVec(); 
	//create plot
	PLOTiter( nx, ny,  x2d,  y2d);
	
	//create file to store NORM2 and NORMinf
	FILE* Normfp  = fopen("Norm.csv" , "w"); 
	FILE* Norm2fp = fopen("Norm2.csv" , "w"); 

	//initialize NORMinf vals
	double la = 1; 
	double lb = 1; 
	double lc = 1; 
	double ld = 1; 

	//iterate
	int iteration = 1; 
	while (iteration < g_MaxIter){
		maxA = 0.0; 
		maxB = 0.0; 
		maxC = 0.0; 
		maxD = 0.0; 

		L2A  = 0.0; 
		L2B  = 0.0; 
		L2C  = 0.0; 
		L2D  = 0.0; 

		//iter();
		//firstColumn();
		stegerIter();
		stegerfirstcolumn();
	
		//plot iteration 
		if (iteration % g_numberOfPlots == 0){
			std::cout<<"iteration : "<< iteration <<std::endl;
			Normali(nx, ny, x2d, y2d);
			makeItVec();
			PLOTiter(nx, ny, x2d, y2d);
		}
		//Fluxcalc();
		//slipwall2();
		//Fluxcalc();
		stegerFluxcalc();
		slipwall2();
		stegerFluxcalc();
		
		timeStep();
		// Store values after each iteration
		maxA_values.push_back(maxA);
		maxB_values.push_back(maxB);
		maxC_values.push_back(maxC);
		maxD_values.push_back(maxD);
		L2Atot_values.push_back(L2Atot);
		L2Btot_values.push_back(L2Btot);
		L2Ctot_values.push_back(L2Ctot);
		L2Dtot_values.push_back(L2Dtot);
		
		iteration = iteration + 1; 
		//la = linfAvec.back(); 
		//lb = linfBvec.back(); 
		//lc = linfCvec.back(); 
		//ld = linfDvec.back();

		//write to files
		fprintf (Normfp, "%d,%e,%e,%e,%e\n", iteration, maxA, maxB, maxC, maxD); 
		fprintf (Norm2fp, "%d,%e,%e,%e,%e\n", iteration, L2Atot, L2Btot, L2Ctot, L2Dtot); 
	}
	//call coloredCells to plot volume contour plot 

	//coloredCells(nx, ny, x2d, y2d);

	//call coloredAreasEta to plot volume contour plot of cells
	//areas parallel to ETA direction
	//coloredAreasEta(nx,ny,x2d,y2d); 

	//call coloredAreasCsi to plot volume contour plot of cells
	//areas parallel to Csi direction
	//coloredAreasCsi(nx,ny,x2d,y2d); 
        
	//NormPlots(); 
	fclose(Normfp); 
	fclose(Norm2fp); 
	delete [] cells; 
	return 0;
}

