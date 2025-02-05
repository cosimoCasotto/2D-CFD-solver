#include "mylib.h"
#include "gdfonts.h"
#include "gdfontl.h"
#include "gdfontg.h"
#include <gd.h> // Include the necessary header for gdImage functions
#include <cstdio>
#include "Point.h" // Include the necessary header for Point-related functions
#include <iostream>
#include "Cell.h"
#include <cmath>

extern Cell* cells;
extern double rho;
extern double gam;
extern double p;

extern int nx, ny; 
extern Point CellCenter(Point bl);
extern Point faceCTR(Point a, Point b); 

int Normali(int nx, int ny, double* x2d, double* y2d) {
	// Create image and define colors
	gdImagePtr imgNorms = gdImageCreate(1000, 1000);
	//colors
	int colWhite = gdImageColorAllocate(imgNorms, 255, 255, 255);
	int colBlack = gdImageColorAllocate(imgNorms, 0, 0, 0);
	int colRed = gdImageColorAllocate(imgNorms, 255, 0, 0);
	int colPurple = gdImageColorAllocate(imgNorms, 135, 31,120);
	int colGreen = gdImageColorAllocate(imgNorms, 0, 200, 0);
	//oustide rectangle 
	gdImageSetThickness (imgNorms, 5); 
	gdImageRectangle(imgNorms, 60, 310, 940, 990, colBlack);
	// fonts
	gdFontPtr LargeFontPtr = gdFontGetLarge(); 
	gdFontPtr GiantFontPtr = gdFontGetGiant(); 
	// thickness of lines
	gdImageSetThickness (imgNorms, 2.5); 
	//axis
	//x and y
	gdImageLine(imgNorms, 300, 950, 400, 950, colBlack); 
	gdImageLine(imgNorms, 300, 950, 300, 850, colBlack); 
	//CSI and ETA
	gdImageLine(imgNorms, 87, 962, 187, 962, colBlack); 
	gdImageLine(imgNorms, 88, 962, 88, 862, colBlack); 
	gdImageString (imgNorms, GiantFontPtr, 167, 964, (unsigned char*) "CSI", colBlack ); 
	gdImageString (imgNorms, GiantFontPtr, 89, 900, (unsigned char*) "ETA", colBlack ); 
	gdImageString (imgNorms, GiantFontPtr, 187, 954, (unsigned char*) ">", colBlack ); 
	gdImageStringUp (imgNorms, GiantFontPtr, 80, 862, (unsigned char*) ">", colBlack ); 
	gdImageString (imgNorms, GiantFontPtr, 380, 952, (unsigned char*) "X", colBlack ); 
	gdImageString (imgNorms, GiantFontPtr, 400, 943, (unsigned char*) ">", colBlack ); 
	gdImageString (imgNorms, GiantFontPtr, 302, 900, (unsigned char*) "Y", colBlack ); 
	gdImageStringUp (imgNorms, GiantFontPtr, 292, 850, (unsigned char*) ">", colBlack ); 
	gdImageString (imgNorms, GiantFontPtr, 300, 965, (unsigned char*) "0", colBlack ); 
	gdImageString (imgNorms, GiantFontPtr, 90 , 965, (unsigned char*) "-0.5", colBlack ); 
	gdImageString (imgNorms, GiantFontPtr, 700, 965, (unsigned char*) "1", colBlack ); 
	gdImageString (imgNorms, GiantFontPtr, 900, 965, (unsigned char*) "1.5", colBlack ); 
	gdImageString (imgNorms, GiantFontPtr, 920, 950, (unsigned char*) "0", colBlack ); 
	gdImageString (imgNorms, GiantFontPtr, 910, 340, (unsigned char*) "1.5", colBlack ); 

	// Draw horizontal grid lines
	for (int j = 0; j <= (ny + 1); j++) {
		Point p1 = flowToImage(gridToFlow(Point(0, j)));
		for (int i = 0; i <= (nx + 1); i++) {
			gdImageSetThickness (imgNorms, 1.5); 
			Point gp(i, j);
			Point fp = gridToFlow(gp);
			Point p2 = flowToImage(fp);
			if (j == 0 || j == 50 || i == 1 || i == 66){
				//debugging
				//std::cout<<"j = 0"<<std::endl;
				gdImageLine(imgNorms, p1.x, p1.y, p2.x, p2.y, colPurple);
			} else{
				gdImageLine(imgNorms, p1.x, p1.y, p2.x, p2.y, colRed);
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
				gdImageLine(imgNorms, p1.x, p1.y, p2.x, p2.y, colPurple);
			} else {
				gdImageLine(imgNorms, p1.x, p1.y, p2.x, p2.y, colRed);
			}
			p1 = p2;
		}
	}

	// Draw lines from grid Points to Cell centers
	for (int j = 0; j < ny + 1; j++) {
		for (int i = 0; i < nx + 1; i++) {
			// point gp and pint on top and to the right
			Point gp(i, j);
			Point rp = getRightPoint(gp); 
			Point up = getUpPoint(gp); 
                        // frid to flow all threee points
			Point fp = gridToFlow(gp);
			Point frp = gridToFlow(rp);
			Point fup = gridToFlow(up);
                        
			//flow to image all three points
			Point p2 = flowToImage(fp);
			Point Ifrp = flowToImage(frp);
			Point Ifup = flowToImage(fup);
                        
			//find face centers
			Point CTRx = faceCTR(Ifup, p2); //vertical face CTR
			Point CTRy = faceCTR(Ifrp, p2); //horizontal face CTR

			//get normal 
			Point csi_norm; 
			Point eta_norm; 
			int c = j*66 + i;

			// make line from CTR of csi norm
			//csi_norm.x = CTRx.x + cells[c].m_nCsi.getX()*5;
			csi_norm.x = CTRx.x + getU(c)/100;
			//csi_norm.y = CTRx.y - cells[c].m_nCsi.getY()*5; 
			csi_norm.y = CTRx.y - getV(c)/100; 

			// make line from CTR of eta norm 
			eta_norm.x = CTRy.x + cells[c].m_nEta.getX()*10;
			eta_norm.y = CTRy.y - cells[c].m_nEta.getY()*10; 
			//plot normal vectors
			gdImageLine(imgNorms, CTRx.x, CTRx.y, csi_norm.x, csi_norm.y, colGreen);
			//gdImageLine(imgNorms, CTRy.x, CTRy.y, eta_norm.x, eta_norm.y, colGreen);
			//debugging
			//if (fp.x == 0 || fp.y == 0 ){

			//std::cout << "x = 0 for i = "<<i<<"on image x = "<<p2.x<< "on image y = "<< p2.y<<std::endl;  
			//}
		}
	}
        // Save image to file
        static int counting = 0;
        char filenames[100];
        sprintf(filenames, "gridImages/imgNorms%03d", counting++);
        FILE* fpV = fopen(filenames, "wb");
        gdImagePng(imgNorms, fpV);
        fclose(fpV);

	// Save image to file
	//FILE* fp = fopen("gridImages/imgNorms.png", "wb");
	//gdImagePng(imgNorms, fp);
	//fclose(fp);

	// Free memory allocated for the image
	//dImageDestroy(imgNorms);

	return 0;
}

