#include <gd.h> // Include the necessary header for gdImage functions
#include <cstdio>
#include "gdfontg.h"
#include "Point.h" // Include the necessary header for Point-related functions
#include <iostream>
#include "Cell.h"
#include "mylib.h"
#include <cmath>

// obtain max and min voliume extenally 
extern double maxVol; 
extern double minVol; 
extern Point CellCenter(Point bl);

int coloredCells(int nx, int ny, double* x2d, double* y2d) {

	// Create image and define colors
	gdImagePtr imgV = gdImageCreate(1000, 1000);
	int colWhite = gdImageColorAllocate(imgV, 255, 255, 255);
	int colBlack = gdImageColorAllocate(imgV, 0, 0, 0);
	int colRed = gdImageColorAllocate(imgV, 255, 0, 0);
	int colPurple = gdImageColorAllocate(imgV, 135, 31,120);
	int colGreen = gdImageColorAllocate(imgV, 0, 200, 0);
	// array of colors for contour plot
	int allColors[256]; for (int i=0; i<256;i++)  allColors[i] = -1;


	for (int j = 0; j <= ny; j++) {
		// find first point of each row
		Point p1 = flowToImage(gridToFlow(Point(0, j)));
		for (int i = 0; i <= nx; i++) {
			Point gp(i, j);
			// find all other points in Cell (br, tr, tl, bl) 
			// = (bottom right, top right, top left, bottom left) 
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

			// array of points in Cell
			gdPoint points [4]; 
			points[0].x = p2.x; 
			points[0].y = p2.y;  

			points[1].x = p2br.x;
			points[1].y = p2br.y;

			points[2].x = p2tr.x;
			points[2].y = p2tr.y;

			points[3].x = p2tl.x;
			points[3].y = p2tl.y;

			// calculate volume of Cell 
			double CellVolume = Vol(gp);
			// normalize value of volume 
			double normalizedVolume = (CellVolume-minVol)/(maxVol-minVol); 

			int grayForNormalizedVolume = int(normalizedVolume * 255.0); 
			// assign color to Cells based on volume
			// if color already present in allColors[], kip 
			int col; 
			if (allColors[grayForNormalizedVolume] < 0){
				// red if volume large 
				int red = 255 *  normalizedVolume;
				// blue of volume not large 
				int blue = 255 * (1-normalizedVolume); 
				col = gdImageColorAllocate(imgV,red, 0, blue); 
				allColors[grayForNormalizedVolume] = col;     
			}else{
				col = allColors[grayForNormalizedVolume];
			}
			// color Cell
			gdImageFilledPolygon(imgV, points, 4, col); 
			gdImageFilledRectangle(imgV, p2.x, p2.y, p2tr.x, p2tr.y, col); 
			p1 = p2;
		}
	}


	// plot aestetic improvements
	//oustide rectangle
	gdImageSetThickness (imgV, 5);
	gdImageRectangle(imgV, 60, 310, 940, 990, colBlack);
	// fonts
	gdFontPtr GiantFontPtr = gdFontGetGiant();
	// thickness of lines
	gdImageSetThickness (imgV, 2.5);
	//axis
	//x and y
	gdImageLine(imgV, 300, 950, 400, 950, colGreen);
	gdImageLine(imgV, 300, 950, 300, 850, colGreen);
	//CSI and ETA
	gdImageLine(imgV, 87, 962, 187, 962, colGreen);
	gdImageLine(imgV, 88, 962, 88, 862, colGreen);
	gdImageString (imgV, GiantFontPtr, 167, 964, (unsigned char*) "CSI", colGreen );
	gdImageString (imgV, GiantFontPtr, 89, 900, (unsigned char*) "ETA", colGreen );
	gdImageString (imgV, GiantFontPtr, 187, 954, (unsigned char*) ">", colGreen );
	gdImageStringUp (imgV, GiantFontPtr, 80, 862, (unsigned char*) ">", colGreen );
	gdImageString (imgV, GiantFontPtr, 380, 952, (unsigned char*) "X", colGreen );
	gdImageString (imgV, GiantFontPtr, 400, 943, (unsigned char*) ">", colGreen );
	gdImageString (imgV, GiantFontPtr, 302, 900, (unsigned char*) "Y", colGreen );
	gdImageStringUp (imgV, GiantFontPtr, 292, 850, (unsigned char*) ">", colGreen );
	gdImageString (imgV, GiantFontPtr, 300, 965, (unsigned char*) "0", colGreen );
	gdImageString (imgV, GiantFontPtr, 90 , 965, (unsigned char*) "-0.5", colGreen );
	gdImageString (imgV, GiantFontPtr, 700, 965, (unsigned char*) "1", colGreen );
	gdImageString (imgV, GiantFontPtr, 900, 965, (unsigned char*) "1.5", colGreen );
	gdImageString (imgV, GiantFontPtr, 920, 950, (unsigned char*) "0", colGreen );
	gdImageString (imgV, GiantFontPtr, 910, 340, (unsigned char*) "1.5", colGreen);



	// Save image to file
	FILE* fpV = fopen("gridImages/imgV.png", "wb");
	gdImagePng(imgV, fpV);
	fclose(fpV);

	// Free memory allocated for the image
	gdImageDestroy(imgV);

	return 0;
}



