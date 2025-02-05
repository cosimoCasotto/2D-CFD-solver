#include <gd.h> // Include the necessary header for gdImage functions
#include <cstdio>
#include "gdfontg.h"
#include "Point.h" // Include the necessary header for Point-related functions
#include <iostream>
#include "Cell.h"
#include "mylib.h"
#include <cmath>

// max and face areas parallel to eta dir. 
extern double maxAbf; 
extern double minAbf; 
extern Point CellCenter(Point bl);

int coloredAreasEta(int nx, int ny, double* x2d, double* y2d) {

	// Create image and define colors
	gdImagePtr imgEtaA = gdImageCreate(1000, 1000);
	// colors
	int colWhite = gdImageColorAllocate(imgEtaA, 255, 255, 255);
	int colBlack = gdImageColorAllocate(imgEtaA, 0, 0, 0);
	int colRed = gdImageColorAllocate(imgEtaA, 255, 0, 0);
	int colPurple = gdImageColorAllocate(imgEtaA, 135, 31,120);
	int colGreen = gdImageColorAllocate(imgEtaA, 0, 200, 0);
	// vector of colors for contour plot 
	int allColors[256]; for (int i=0; i<256;i++)  allColors[i] = -1;


	for (int j = 0; j <= ny; j++) {
		// find first point of each row
		Point p1 = flowToImage(gridToFlow(Point(0, j)));
		for (int i = 0; i <= nx; i++) {
			Point gp(i, j);
			// find all points of each Cell
			Point fp = gridToFlow(gp);
			Point p2 = flowToImage(fp);

			Point br = getRightPoint(gp); 
			Point fpbr = gridToFlow(br); 
			Point p2br = flowToImage(fpbr); 

			Point tl = getUpPoint(gp); 
			Point fptl = gridToFlow(tl); 
			Point p2tl = flowToImage(fptl); 

			Point tr = getUpPoint(br);
			Point fptr = gridToFlow(tr); 
			Point p2tr = flowToImage(fptr); 
			Cell Cellij = Cell(i,j); 

			// array of 4 points in the Cell (top right, top left, bottom right)
			gdPoint points [4]; 
			points[0].x = p2.x; 
			points[0].y = p2.y;  

			points[1].x = p2br.x;
			points[1].y = p2br.y;

			points[2].x = p2tr.x;
			points[2].y = p2tr.y;

			points[3].x = p2tl.x;
			points[3].y = p2tl.y;

			// calculate bottom face area of each Cell 
			double abf = BFA(gp); 	    
			// normalize its value 
			double normalizedAbf = (abf-minAbf)/(maxAbf-minAbf); 
			int grayForNormalizedAbf = int(normalizedAbf * 255.0); 

			// assign colors to each Cell. if color is already present skip, else add to allColors[]
			int col; 
			if (allColors[grayForNormalizedAbf] < 0){
				// red if large value 
				int red = 255 *  normalizedAbf;
				// blue if value not large 
				int blue = 255 * (1-normalizedAbf); 
				col = gdImageColorAllocate(imgEtaA,red, 0, blue); 
				allColors[grayForNormalizedAbf] = col;     
			}else{
				col = allColors[grayForNormalizedAbf];
			}

			// plot aesthetic improvements 
			//oustide rectangle
			gdImageSetThickness (imgEtaA, 5);
			gdImageRectangle(imgEtaA, 60, 310, 940, 990, colBlack);
			// fonts
			gdFontPtr GiantFontPtr = gdFontGetGiant();
			// thickness of lines
			gdImageSetThickness (imgEtaA, 2.5);
			//axis
			//x and y
			gdImageLine(imgEtaA, 300, 950, 400, 950, colGreen);
			gdImageLine(imgEtaA, 300, 950, 300, 850, colGreen);
			//CSI and ETA
			gdImageLine(imgEtaA, 87, 962, 187, 962, colGreen);
			gdImageLine(imgEtaA, 88, 962, 88, 862, colGreen);
			gdImageString (imgEtaA, GiantFontPtr, 167, 964, (unsigned char*) "CSI", colGreen );
			gdImageString (imgEtaA, GiantFontPtr, 89, 900, (unsigned char*) "ETA", colGreen );
			gdImageString (imgEtaA, GiantFontPtr, 187, 954, (unsigned char*) ">", colGreen );
			gdImageStringUp (imgEtaA, GiantFontPtr, 80, 862, (unsigned char*) ">", colGreen );
			gdImageString (imgEtaA, GiantFontPtr, 380, 952, (unsigned char*) "X", colGreen );
			gdImageString (imgEtaA, GiantFontPtr, 400, 943, (unsigned char*) ">", colGreen );
			gdImageString (imgEtaA, GiantFontPtr, 302, 900, (unsigned char*) "Y", colGreen );
			gdImageStringUp (imgEtaA, GiantFontPtr, 292, 850, (unsigned char*) ">", colGreen );
			gdImageString (imgEtaA, GiantFontPtr, 300, 965, (unsigned char*) "0", colGreen );
			gdImageString (imgEtaA, GiantFontPtr, 90 , 965, (unsigned char*) "-0.5", colGreen );
			gdImageString (imgEtaA, GiantFontPtr, 700, 965, (unsigned char*) "1", colGreen );
			gdImageString (imgEtaA, GiantFontPtr, 900, 965, (unsigned char*) "1.5", colGreen );
			gdImageString (imgEtaA, GiantFontPtr, 920, 950, (unsigned char*) "0", colGreen );
			gdImageString (imgEtaA, GiantFontPtr, 910, 340, (unsigned char*) "1.5", colGreen);


			gdImageFilledPolygon(imgEtaA, points, 4, col); 
			gdImageFilledRectangle(imgEtaA, p2.x, p2.y, p2tr.x, p2tr.y, col); 
			p1 = p2;
		}
	}
	// Save image to file
	FILE* fpEtaA = fopen("gridImages/imgEtaA.png", "wb");
	gdImagePng(imgEtaA, fpEtaA);
	fclose(fpEtaA);

	// Free memory allocated for the image
	gdImageDestroy(imgEtaA);

	return 0;
}



