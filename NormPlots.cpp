#include "mylib.h"
#include "gdfonts.h"
#include "gdfontl.h"
#include "gdfontg.h"
#include <gd.h> // Include the necessary header for gdImage functions
#include <cstdio>
#include "Point.h" // Include the necessary header for Point-related functions
#include <iostream>
#include "vector"

extern int nx, ny; 
extern Point CellCenter(Point bl);
extern std::vector<double> maxA_values; 
extern std::vector<double> maxB_values; 
extern std::vector<double> maxC_values; 
extern std::vector<double> maxD_values; 

extern std::vector<double> L2Atot_values; 
extern std::vector<double> L2Btot_values; 
extern std::vector<double> L2Ctot_values; 
extern std::vector<double> L2Dtot_values; 

int 
NormPlots() 
{
	//number of iterations
	int size = maxA_values.size();
        int sizeOnImg = size/(size/1000) - 200; 	
	// Create image and define colors
	gdImagePtr imgPL = gdImageCreate(1000, 1000);
	//colors
	int colWhite  = gdImageColorAllocate(imgPL, 255, 255, 255);
	int colBlack  = gdImageColorAllocate(imgPL, 0  , 0  , 0  );
	int colRed    = gdImageColorAllocate(imgPL, 255, 0  , 0  );
	int colPurple = gdImageColorAllocate(imgPL, 135, 31 , 120);
	int colGreen  = gdImageColorAllocate(imgPL, 0  , 200, 0  );
	//oustide rectangle 
	// fonts
	gdFontPtr LargeFontPtr = gdFontGetLarge(); 
	gdFontPtr GiantFontPtr = gdFontGetGiant(); 
	// thickness of lines
	//X and Y axis
	gdImageLine(imgPL, 100, 960, 100 + sizeOnImg, 962, colBlack); 
	gdImageLine(imgPL, 100, 960, 100, 360, colBlack); 

	

	// Save image to file
	FILE* fp = fopen("gridImages/errorPLOTS.png", "wb");
	gdImagePng(imgPL, fp);
	fclose(fp);

	// Free memory allocated for the image
	gdImageDestroy(imgPL);

	return 0;
}

