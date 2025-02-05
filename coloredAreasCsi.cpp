#include <gd.h> // Include the necessary header for gdImage functions
#include <cstdio>
#include "gdfontg.h"
#include "Point.h" // Include the necessary header for Point-related functions
#include <iostream>
#include "Cell.h"
#include "mylib.h"
#include <cmath>

//obtain values of max and min face area parallel to csi direction 
extern double maxAlf; 
extern double minAlf; 
extern Point CellCenter(Point bl);

int coloredAreasCsi(int nx, int ny, double* x2d, double* y2d) {

	// Create image and define colors
	gdImagePtr imgCsiA = gdImageCreate(1000, 1000);
	// define img colors
	int colWhite = gdImageColorAllocate(imgCsiA, 255, 255, 255);
	int colBlack = gdImageColorAllocate(imgCsiA, 0, 0, 0);
	int colRed = gdImageColorAllocate(imgCsiA, 255, 0, 0);
	int colPurple = gdImageColorAllocate(imgCsiA, 135, 31,120);
	int colGreen = gdImageColorAllocate(imgCsiA, 0, 200, 0);

	//array of colors for contour plot
	int allColorsC[256]; for (int i=0; i<256;i++)  allColorsC[i] = -1;


	for (int j = 0; j <= ny; j++) {
		// find first point of each row (0,j)
		Point p1 = flowToImage(gridToFlow(Point(0, j)));
		for (int i = 0; i <= nx; i++) {

			//find point gp of coordinates (i,j)	
			Point gp(i, j);

			// find all other points in the (i,j) Cell 
			Point fp = gridToFlow(gp);
			Point p2 = flowToImage(fp);

			// br = bottom right of Cell
			Point br = getRightPoint(gp); 
			Point fpbr = gridToFlow(br); 
			Point p2br = flowToImage(fpbr); 

			// tl = top left of Cell 
			Point tl = getUpPoint(gp); 
			Point fptl = gridToFlow(tl); 
			Point p2tl = flowToImage(fptl); 

			// tr = top right of Cell 
			Point tr = getUpPoint(br);
			Point fptr = gridToFlow(tr); 
			Point p2tr = flowToImage(fptr); 
			Cell Cellij = Cell(i,j); 

			// array containing all 4 points in the Cell 
			gdPoint points [4]; 
			points[0].x = p2.x; 
			points[0].y = p2.y;  

			points[1].x = p2br.x;
			points[1].y = p2br.y;

			points[2].x = p2tr.x;
			points[2].y = p2tr.y;

			points[3].x = p2tl.x;
			points[3].y = p2tl.y;

			//calculate LFA of gp Cell 
			double alf = LFA(gp); 

			// assign a color to the Cell
			// normalize the value of the Cell face     
			double nomalizedAlf = (alf-minAlf)/(maxAlf-minAlf); 

			int grayForNormalizedAlf = int(nomalizedAlf * 255.0); 

			// add color to allColorsC array if it does not already exist
			// otherwise, don't add it
			int col; 
			if (allColorsC[grayForNormalizedAlf] < 0){
				// red if value is large 
				int red = 255 *  nomalizedAlf;
				// blue if value is not large 
				int blue = 255 * (1-nomalizedAlf); 
				col = gdImageColorAllocate(imgCsiA,red, 0, blue); 
				allColorsC[grayForNormalizedAlf] = col;     
			}else{
				col = allColorsC[grayForNormalizedAlf];
			}

			// color Cells 
			gdImageFilledPolygon(imgCsiA, points, 4, col); 
			gdImageFilledRectangle(imgCsiA, p2.x, p2.y, p2tr.x, p2tr.y, col); 
			p1 = p2;
		}
	}


	//plot aesthetic improvememts
	//oustide rectangle
	gdImageSetThickness (imgCsiA, 5);
	gdImageRectangle(imgCsiA, 60, 310, 940, 990, colBlack);
	// fonts
	gdFontPtr GiantFontPtr = gdFontGetGiant();
	// thickness of lines
	gdImageSetThickness (imgCsiA, 2.5);
	//axis
	//x and y
	gdImageLine(imgCsiA, 300, 950, 400, 950, colGreen);
	gdImageLine(imgCsiA, 300, 950, 300, 850, colGreen);
	//CSI and ETA
	gdImageLine(imgCsiA, 87, 962, 187, 962, colGreen);
	gdImageLine(imgCsiA, 88, 962, 88, 862, colGreen);
	gdImageString (imgCsiA, GiantFontPtr, 167, 964, (unsigned char*) "CSI", colGreen );
	gdImageString (imgCsiA, GiantFontPtr, 89, 900, (unsigned char*) "ETA", colGreen );
	gdImageString (imgCsiA, GiantFontPtr, 187, 954, (unsigned char*) ">", colGreen );
	gdImageStringUp (imgCsiA, GiantFontPtr, 80, 862, (unsigned char*) ">", colGreen );
	gdImageString (imgCsiA, GiantFontPtr, 380, 952, (unsigned char*) "X", colGreen );
	gdImageString (imgCsiA, GiantFontPtr, 400, 943, (unsigned char*) ">", colGreen );
	gdImageString (imgCsiA, GiantFontPtr, 302, 900, (unsigned char*) "Y", colGreen );
	gdImageStringUp (imgCsiA, GiantFontPtr, 292, 850, (unsigned char*) ">", colGreen );
	gdImageString (imgCsiA, GiantFontPtr, 300, 965, (unsigned char*) "0", colGreen );
	gdImageString (imgCsiA, GiantFontPtr, 90 , 965, (unsigned char*) "-0.5", colGreen );
	gdImageString (imgCsiA, GiantFontPtr, 700, 965, (unsigned char*) "1", colGreen );
	gdImageString (imgCsiA, GiantFontPtr, 900, 965, (unsigned char*) "1.5", colGreen );
	gdImageString (imgCsiA, GiantFontPtr, 920, 950, (unsigned char*) "0", colGreen );
	gdImageString (imgCsiA, GiantFontPtr, 910, 340, (unsigned char*) "1.5", colGreen);



	// Save image to file
	FILE* fpCsiA = fopen("gridImages/imgCsiA.png", "wb");
	gdImagePng(imgCsiA, fpCsiA);
	fclose(fpCsiA);

	// Free memory allocated for the image
	gdImageDestroy(imgCsiA);

	return 0;
}



