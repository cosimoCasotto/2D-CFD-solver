#include <gd.h> // Include the necessary header for gdImage functions
#include <cstdio>
#include "gdfontg.h"
#include "Point.h" // Include the necessary header for Point-related functions
#include <iostream>
#include "Cell.h"
#include "mylib.h"
#include <cmath>
#include "gnuplot-iostream.h"


// obtain max and min voliume extenally 
extern Cell* cells; 
extern double maxU; 
extern double minU; 
extern double* ItVec; 

int PLOTiter(int nx, int ny, double* x2d, double* y2d) {

	// Create image and define colors
	gdImagePtr imgU = gdImageCreate(1000, 1000);
	int colWhite    = gdImageColorAllocate(imgU, 255, 255, 255);
	int colBlack    = gdImageColorAllocate(imgU, 0  , 0  , 0  );
	int colRed      = gdImageColorAllocate(imgU, 255, 0  , 0  );
	int colPurple   = gdImageColorAllocate(imgU, 135, 31 , 120);
	int colGreen    = gdImageColorAllocate(imgU, 0  , 200, 0  );
        gdFontPtr GiantFontPtr = gdFontGetGiant();
	// array of colors for contour plot
	int allColors[256]; for (int i=0; i<256;i++)  allColors[i] = -1;


	for (int j = 0; j <= ny; j++) {
		// find first point of each row
		Point p1 = flowToImage(gridToFlow(Point(0, j)));
		for (int i = 0; i <= nx; i++) {
			Point gp(i, j);
			int c = 66*j + i ; 
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

			// calculate value of Cell 
			double u = ItVec[c];
			// normalize value  
			double denominatore = maxU-minU; 
			//double denominatore = 800; 
			double normalizedU  = denominatore>0? (u-minU)/denominatore : 1.0; 
			//double normalizedU  = u/800.0; 
			int grayForNormalizedU = int(normalizedU * 255.0); 
			if (grayForNormalizedU < 0){
				grayForNormalizedU = 0; 
			}
			// assign color to Cells based on U
			// if color already present in allColors[], kip 
			int col; 
			if (allColors[grayForNormalizedU] < 0){
				// red if volume large 
				int red  = 255 *  normalizedU;
				// blue of volume not large 
				int blue = 255 * (1-normalizedU); 
				//middle value is green
				int green = -std::abs(510*(normalizedU-0.5))+255;
				col = gdImageColorAllocate(imgU,red, green, blue); 
				allColors[grayForNormalizedU] = col;     
			}else{
				col = allColors[grayForNormalizedU];
			}
			// color Cell
			gdImageFilledPolygon(imgU, points, 4, col); 
			gdImageFilledRectangle(imgU, p2.x, p2.y, p2tr.x, p2tr.y, col); 
			p1 = p2;
		}
	}


	// plot aestetic improvements
	//oustide rectangle
	gdImageSetThickness (imgU, 5);
	gdImageRectangle(imgU, 30-10 , 310, 910-10, 990, colBlack);
	gdImageSetThickness (imgU, 2.5 );
        gdImageString  (imgU, GiantFontPtr, 450, 320, (unsigned char*) "Velocity" , colBlack );
	
	gdImageRectangle(imgU, 915-10, 310, 925-10, 990, colBlack);
	for (int i = 0; i < 68; i++){
		int s = 310 + i*10; 
		int g = s + 10; 
		int colorindex = i/68.0 * 255.0;
		if (allColors[colorindex] >= 0){
			gdImageFilledRectangle(imgU, 915-10, s, 925-10 , g, allColors[colorindex]);
		}	
		if (0 == i){ 
	        char legendText[12]; 
		sprintf(legendText , "%.2e" , minU);  
                gdImageString  (imgU, GiantFontPtr, 920, 315, (unsigned char*) legendText , colBlack );
		}
		if (67 == i){
                char legendTextmax[12];
                sprintf(legendTextmax , "%.2e" , maxU);
                gdImageString  (imgU, GiantFontPtr, 920, 975, (unsigned char*) legendTextmax , colBlack );
                }

	}
#ifdef OLDCODE
	//for (int s = 310; s <= 980; s += 10){
	//	int g = s + 10; 	
	//gdPoint Legpoints [4];
	//	Legpoints[0].x = 960;
	//	Legpoints[0].y = s;
	//
	//		Legpoints[1].x = 970;
	//		Legpoints[1].y = s;
	//
	//		Legpoints[2].x = 960;
	//		Legpoints[2].y = g;
	//
	//		Legpoints[3].x = 970;
	//		Legpoints[3].y = g;
	int legred = -255/670 * s + 24990/67;
	int leggreen = -std::abs(510*s - 328950) + 255; 
	int legblue = 255/670 * s - 7905/67; 	
	//int Legcol = gdImageColorAllocate(imgU, legred, leggreen, legblue);
	int sNorm = int(((s-310)/670)*255); 
	int Legcol = allColors[sNorm]; 
	gdImageFilledRectangle(imgU, 960-10, s, 970-10 , g, Legcol);
}	
#endif
// fonts
// thickness of lines
gdImageSetThickness (imgU, 2.5);
//axis
//x and y
gdImageLine     (imgU, 270-10, 950, 370-10, 950, colGreen);
gdImageLine     (imgU, 270-10, 950, 270-10, 850, colGreen);
//CSI and ETA
gdImageLine     (imgU, 57 , 962, 157, 962, colGreen);
gdImageLine     (imgU, 58-10 , 962, 58-10 , 862, colGreen);

gdImageString   (imgU, GiantFontPtr, 137-10, 964, (unsigned char*) "CSI" , colGreen );
gdImageString   (imgU, GiantFontPtr, 59 -10, 900, (unsigned char*) "ETA" , colGreen );
gdImageString   (imgU, GiantFontPtr, 157-10, 954, (unsigned char*) ">"   , colGreen );
gdImageStringUp (imgU, GiantFontPtr, 50 -10, 862, (unsigned char*) ">"   , colGreen );
gdImageString   (imgU, GiantFontPtr, 350-10, 952, (unsigned char*) "X"   , colGreen );
gdImageString   (imgU, GiantFontPtr, 370-10, 943, (unsigned char*) ">"   , colGreen );
gdImageString   (imgU, GiantFontPtr, 272-10, 900, (unsigned char*) "Y"   , colGreen );
gdImageStringUp (imgU, GiantFontPtr, 262-10, 850, (unsigned char*) ">"   , colGreen );
gdImageString   (imgU, GiantFontPtr, 270-10, 965, (unsigned char*) "0"   , colGreen );
gdImageString   (imgU, GiantFontPtr, 60 -10, 965, (unsigned char*) "-0.5", colGreen );
gdImageString   (imgU, GiantFontPtr, 670-10, 965, (unsigned char*) "1"   , colGreen );
gdImageString   (imgU, GiantFontPtr, 870-10, 965, (unsigned char*) "1.5" , colGreen );
gdImageString   (imgU, GiantFontPtr, 890-10, 950, (unsigned char*) "0"   , colGreen );
gdImageString   (imgU, GiantFontPtr, 880-10, 340, (unsigned char*) "1.5" , colGreen);



// Save image to file
static int countImgs = 0; 
char filename[100];
sprintf(filename, "gridImages/imgU%03d.png", countImgs++); 	
FILE* fpV = fopen(filename, "wb");
gdImagePng(imgU, fpV);
fclose(fpV);

// Free memory allocated for the image
gdImageDestroy(imgU);

return 0;
}



