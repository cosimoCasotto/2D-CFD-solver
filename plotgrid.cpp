#include "mylib.h"
#include "gdfonts.h"
#include "gdfontl.h"
#include "gdfontg.h"
#include <gd.h> // Include the necessary header for gdImage functions
#include <cstdio>
#include "Point.h" // Include the necessary header for Point-related functions
#include <iostream>

extern int nx, ny; 
extern Point CellCenter(Point bl);

int 
plotgrid(int nx, int ny, double* x2d, double* y2d) 
{
	// Create image and define colors
	gdImagePtr img = gdImageCreate(1000, 1000);
	//colors
	int colWhite  = gdImageColorAllocate(img, 255, 255, 255);
	int colBlack  = gdImageColorAllocate(img, 0  , 0  , 0  );
	int colRed    = gdImageColorAllocate(img, 255, 0  , 0  );
	int colPurple = gdImageColorAllocate(img, 135, 31 , 120);
	int colGreen  = gdImageColorAllocate(img, 0  , 200, 0  );
	//oustide rectangle 
	gdImageSetThickness (img, 5); 
	gdImageRectangle(img, 60, 310, 940, 990, colBlack);
	// fonts
	gdFontPtr LargeFontPtr = gdFontGetLarge(); 
	gdFontPtr GiantFontPtr = gdFontGetGiant(); 
	// thickness of lines
	gdImageSetThickness (img, 2.5); 
	//axis
	//x and y
	gdImageLine(img, 300, 950, 400, 950, colBlack); 
	gdImageLine(img, 300, 950, 300, 850, colBlack); 
	//CSI and ETA
	gdImageLine(img, 87, 962, 187, 962, colBlack); 
	gdImageLine(img, 88, 962, 88, 862, colBlack); 
	gdImageString   (img, GiantFontPtr, 167, 964, (unsigned char*) "CSI" , colBlack ); 
	gdImageString   (img, GiantFontPtr, 89 , 900, (unsigned char*) "ETA" , colBlack ); 
	gdImageString   (img, GiantFontPtr, 187, 954, (unsigned char*) ">"   , colBlack ); 
	gdImageStringUp (img, GiantFontPtr, 80 , 862, (unsigned char*) ">"   , colBlack ); 
	gdImageString   (img, GiantFontPtr, 380, 952, (unsigned char*) "X"   , colBlack ); 
	gdImageString   (img, GiantFontPtr, 400, 943, (unsigned char*) ">"   , colBlack ); 
	gdImageString   (img, GiantFontPtr, 302, 900, (unsigned char*) "Y"   , colBlack ); 
	gdImageStringUp (img, GiantFontPtr, 292, 850, (unsigned char*) ">"   , colBlack ); 
	gdImageString   (img, GiantFontPtr, 300, 965, (unsigned char*) "0"   , colBlack ); 
	gdImageString   (img, GiantFontPtr, 90 , 965, (unsigned char*) "-0.5", colBlack ); 
	gdImageString   (img, GiantFontPtr, 700, 965, (unsigned char*) "1"   , colBlack ); 
	gdImageString   (img, GiantFontPtr, 900, 965, (unsigned char*) "1.5" , colBlack ); 
	gdImageString   (img, GiantFontPtr, 920, 950, (unsigned char*) "0"   , colBlack ); 
	gdImageString   (img, GiantFontPtr, 910, 340, (unsigned char*) "1.5" , colBlack ); 

	// Draw horizontal grid lines
	for (int j = 0; j <= (ny + 1); j++) {
		Point p1 = flowToImage(gridToFlow(Point(0, j)));
		for (int i = 0; i <= (nx + 1); i++) {
			gdImageSetThickness (img, 1.5); 
			Point gp(i, j);
			Point fp = gridToFlow(gp);
			Point p2 = flowToImage(fp);
			if (j == 0 || j == 50 || i == 1 || i == 66){
				//debugging
				//std::cout<<"j = 0"<<std::endl;
				gdImageLine(img, p1.x, p1.y, p2.x, p2.y, colPurple);
			} else{
				gdImageLine(img, p1.x, p1.y, p2.x, p2.y, colRed);
				//debugging
				//std::cout<<"j = "<< j <<" , i = "<<i <<std::endl;
			}
			p1 = p2;
		}
	}

	// Draw vertical grid lines
	for (int i = 0; i <= (nx + 1); i++) {
		Point p1 = flowToImage(gridToFlow(Point(i, 0)));
		for (int j = 0; j <= (ny + 1); j++) {
			Point gp(i, j);
			Point fp = gridToFlow(gp);
			Point p2 = flowToImage(fp);
			if (i == 0 || i == 66 || j == 1 || j == 50){
				gdImageLine(img, p1.x, p1.y, p2.x, p2.y, colPurple);
			} else {
				gdImageLine(img, p1.x, p1.y, p2.x, p2.y, colRed);
			}
			p1 = p2;
		}
	}

	// Draw lines from grid Points to Cell centers
	for (int j = 0; j <= ny; j++) {
		for (int i = 0; i <= nx; i++) {
			Point gp(i, j);
			Point fp     = gridToFlow(gp);
			Point p2     = flowToImage(fp);
			Point ctr    = CellCenter(gp);
			Point imgCtr = flowToImage(ctr);
			gdImageLine(img, p2.x, p2.y, imgCtr.x, imgCtr.y, colGreen);
			//debugging
			//if (fp.x == 0 || fp.y == 0 ){

			//std::cout << "x = 0 for i = "<<i<<"on image x = "<<p2.x<< "on image y = "<< p2.y<<std::endl;  
			//}
		}
	}

	// Save image to file
	FILE* fp = fopen("gridImages/img42.png", "wb");
	gdImagePng(img, fp);
	fclose(fp);

	// Free memory allocated for the image
	gdImageDestroy(img);

	return 0;
}

