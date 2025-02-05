#include "Cell.h"
#include <gd.h> // Include the necessary header for gdImage functions
#include <cstdio>
#include "Point.h" // Include the necessary header for Point-related functions
#include <iostream>

//extern Point cellCenter(Point bl);
extern int nx;
extern int ny; 
//int j = 0;
//int i = 0; 
//int gridsizeCells = (nx+1)*(ny+1);
//Cell* cells = nullptr;
extern Cell* cells; 
////Cell* cells = NULL;

//initialize max and min values 
//for cell volumes and cell face areas
double minVol = 0.001; 
double maxVol = 0.0001; 

//Alf = area left face    
double minAlf = 0.035; 
double maxAlf = 0.025; 

//Abf = area bottom face
double minAbf = 0.035; 
double maxAbf = 0.025; 


int calcCell() {

//	Cell* cells = new Cell[3400]; //we only need thiss array to have 66*50=3300 elemnets but it is convenient to initialize it to a greater length to avoid some errors
	for (int j = 0; j <= ny; j++) {
		for (int i = 0; i <= nx; i++) {
			int c = i + j * (nx + 1);
			Point bl(i,j); // Create a Point object for the cell center
			cells[c] = Cell(i,j); // Initialize the cell with its center coordinates

                        double SETAx = getSetaX(bl); 
			double SETAy = getSetaY(bl);
			//std::cout<< bl <<" seta X = " <<SETAx << " seta y = " << SETAy<<std::endl; 
		        //std::cout<< "//////////////////////////////////" << std::endl; 

			// Calculate face areas and volume using the helper functions
			// calculate left face area
			cells[c].m_Alf = LFA(bl); 
			// Update minVol and maxVol
			if (cells[c].m_Alf < minAlf) {
				minAlf = cells[c].m_Alf;
			}
			if (cells[c].m_Alf > maxAlf) {
				maxAlf = cells[c].m_Alf;
			}
                        
			// also calculate right face and top face which are not specifically needed 
			cells[c].m_Arf = RFA(bl); // Right face area
			cells[c].m_Atf = TFA(bl); // Top face area
                        

			//calculate bottom face 
			cells[c].m_Abf = BFA(bl); // Bottom face area
						  // Update minVol and maxVol
			if (cells[c].m_Abf < minAbf) {
				minAbf = cells[c].m_Abf;
			}
			if (cells[c].m_Abf > maxAbf) {
				maxAbf = cells[c].m_Abf;
			}
                         
			// calculate cell volume
			cells[c].m_Vol = Vol(bl); // Volume
						  // Update minVol and maxVol
			if (cells[c].m_Vol < minVol) {
				minVol = cells[c].m_Vol;
			}
			if (cells[c].m_Vol > maxVol) {
				maxVol = cells[c].m_Vol;
			}
			Vec2 nEta = getnEta(bl); 
			Vec2 nCsi = getnCsi(bl); 
			cells[c].m_nCsi = nCsi; 
			cells[c].m_nEta = nEta; 
		}
	}

	//std::cout<<"before    "<<cells[65]<<std::endl;
	//debugging section 
	// Output the cell information for verification
	//for (int i = 0; i < 300; ++i) {
	//	std::cout << "i = "<<i << cells[i]; // Assuming the Cell class has an overloaded << operator for output
	//} 

	// print maximum and minimum volume and face areas
	//std::cout << "maxVol is " << maxVol << "minVol is " << minVol<< std::endl << "maxAbf is " << maxAbf << "minAbf is " << minAbf<< std::endl << "maxAlf is " << maxAlf << "minAlf is " << minAlf<< std::endl; 


	return 0;
}

