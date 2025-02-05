#include "mylib.h"
#include "Cell.h"
#include "Point.h"
#include <cmath>
#include <algorithm>
#include <iostream>
#include <vector>

extern Cell* cells;
extern int g_ShowWhat;
double* ItVec  = new double[3300];
double maxU;
double minU;

int makeItVec()
{
    // Check if cells is properly allocated
    if (!cells) {
        std::cerr << "Error: cells is not properly allocated." << std::endl;
        return -1;
    }

    std::fill(ItVec, ItVec + 3300, 0.0); // Initialize ItVec with zeros
    for (int c = 0; c < 3300; c++) {
	    Cell& cur = cells[c];

	    double u = getU(c);
	    double v = getV(c); 
	    int i = cur.m_i; 
	    int j = cur.m_j; 
	    Point bl(i,j);  
	    // Check if getP, getU, getB functions are properly defined
	    switch (g_ShowWhat) {
		    case 0:
			    ItVec[c] = getP(c);
			    break;
		    case 1:
			    ItVec[c] = getU(c);
			    break;
		    case 2:
			    ItVec[c] = std::sqrt(u*u + v*v); 
			    break; 	
		    case 3:
			    ItVec[c] = getSetaX(bl); 
			    break; 	
		    case 4:
			    ItVec[c] = getRho(c); 
			    break; 	
		    case 5:
			    ItVec[c] = getT(c); 
			    break; 	
		    default:
			    ItVec[c] = getP(c); // or set a default value
			    break;
	    }
    }

    
    // Find max and min of ItVec
    if (ItVec != nullptr && std::distance(ItVec, ItVec + 3300) > 0) {
    	    maxU = *std::max_element(ItVec, ItVec + 3300);
    	    minU = *std::min_element(ItVec, ItVec + 3300);
     	    if (minU < 0){
    		    minU = 0; 
    	    }
    	   // std::cout << "max value is : " << maxU << " min value is : " << minU << std::endl;
    } else {
    	    std::cerr << "Error: ItVec is empty or not properly initialized." << std::endl;
    }

    return 0;
}

