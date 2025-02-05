#include "mylib.h"
#include "Cell.h"
#include "Point.h"
#include <iostream>
#include <cstdio>
#include "Point.h" // Include the necessary headers for point-related functions

// Declare global variables
int nx, ny, gridsize;
double* x2d;
double* y2d;


//read grid from .dat file and create x2d and y2d vectors
int readgrid() {
	// declare variables
	int p;       // counter variables
	double temp1,temp2;  // temp variables
	FILE * fp;
	FILE * foutput;

	// try to open original grid file
	fp = fopen("g65x49u.dat","rt");

	// open output file for writing coordinates; "w" opens in write mode
	foutput = fopen("vecsHalo.dat","w");

	// check if file exists, otherwise exit with error message
	if (fp == NULL)
	{
		printf("Error opening source file\n");
	}

	// scan first line for nx and ny
	fscanf(fp,"%d,%d\n", &nx, &ny);
	fprintf(foutput, "%s\t%s%d\t%s%d\n", "ZONE", "i=", nx, "j=", ny);

	// reset to start position (mostly for convenience)
	rewind(fp);

	// skip first line because we already read in nx,ny
	char c;
	do {
		c = fgetc(fp);
	} while (c != '\n');

	//create an array of size 67*51 to allow the halo cells to fit
	gridsize = (nx+2)*(ny+2);
	std::cout << "grid size is: " << gridsize << std::endl ;

	//allocate space for x2d and y2d which we will start to fill
	x2d = (double*)malloc(gridsize*sizeof(double));
	y2d = (double*)malloc(gridsize*sizeof(double));

	// main loop for reading file
	// while loop reads until it reaches end of file (feof)
	// start assigning from the 68th point in x2d and y2d. It will become our (i,j)=(1,1) point
	p = nx+3;
	for (p = nx+3; p<= 3348; p++)
	{
		//skip halo cells for now
		if ((p-66) % (67) == 0){
			//debugging
			//std::cout<< "point number " << p << "is right halo "<< std::endl;
			p += 2;
		}

		//assign to x2d and y2d from .dat file
		fscanf(fp, "%lf%*c %lf\n", &temp1, &temp2);     // read and assign to temp vars
		x2d[p] = temp1;
		y2d[p] = temp2;
		fprintf(foutput, "\t%.16E,\t%.16E\n", x2d[p], y2d[p]);// assign to main array and write to file
	}


	//left column of halo cells
	//(mirroring the inner cells on to the outside of the grid)
	int j = 1;
	for (j = 1; j <= 49; j++){
		Point rp = getRightPoint(Point(0,j));
		Point coordrp = coordinates(rp);
		Point rrp = getRRPoint(Point(0,j));
		double xdist = Xdist(rp,rrp);
		double ydist = Ydist(rp,rrp);
		x2d[67*j] = coordrp.x - xdist;
		y2d[67*j] = coordrp.y;
		//debugging
		//std::cout << "left halo point at i = 0 and j = " << j << "	" << x2d[67*j] << " , " << y2d[67*j] << std::endl;

		//right side halo cells
		Point lp = getLeftPoint(Point(66,j));
		Point coordlp = coordinates(lp);
		Point llp = getLLPoint(Point(66,j));
		xdist = Xdist(lp,llp);
		ydist = Ydist(lp,llp);
		x2d[66+67 *j] = coordlp.x + xdist;
		y2d[66+67*j] = coordlp.y;
		//debugging
		//std::cout << "right halo point at i = 66 and j = " << j << "	" << x2d[66+67*j] << " , " << y2d[66+67*j] << std::endl;
	}


	//bottom halo cells
	int i = 1;
	for (i = 1; i <= 65; i++){
		Point up = getUpPoint(Point(i,0));
		Point coordup = coordinates(up);
		Point uup = getUUPoint(Point(i,0));
		double xdist = Xdist(up, uup);
		double ydist = Ydist(up, uup);
		y2d[i] = coordup.y - ydist;
		x2d[i] = coordup.x;
		//debugging
		//std::cout << "bottom halo point at i = " << i << " and j = 0  " << x2d[i] << " , " << y2d[i] << std::endl;

		//top halo cells
		Point dp = getDownPoint(Point(i,50));
		Point coorddp = coordinates(dp);
		Point ddp = getDDPoint(Point(i,50));
		xdist = Xdist(dp, ddp);
		ydist = Ydist(dp, ddp);
		y2d[i + 3350] = coorddp.y + ydist;
		x2d[i + 3350] = coorddp.x;
		//debugging
		//	std::cout << "top halo point at i = " << i << " and j = 50  " << x2d[i + 3350] << " , " << y2d[i+3350] << std::endl;
	}

	//corner halo points 
	//bootom left
	Point up = getUpPoint(Point(0,0));
	Point coordup = coordinates(up);
	Point uup = getUUPoint(Point(0,0));
	double xdist = Xdist(up, uup);
	double ydist = Ydist(up, uup);
	double Y1= coordup.y - ydist;
	double X1 = coordup.x;

	Point rp = getRightPoint(Point(0,0));
	Point coordrp = coordinates(rp);
	Point rrp = getRRPoint(Point(0,0));
	xdist = Xdist(rp,rrp);
	ydist = Ydist(rp,rrp);
	//debugging
	//std::cout << "HEY this is rp = " << rp << "HEY THIS is rrp " << rrp << "and dist " << xdist <<" "<< ydist<<std::endl;
	double X2 = coordrp.x - xdist;
	double Y2 = coordrp.y - ydist;
	x2d[0] = (X1+X2)/2;
	y2d[0] = (Y1+Y2)/2;

	//bottom right
	Point lp = getLeftPoint(Point(66,0));
	Point coordlp = coordinates(lp);
	Point llp = getLLPoint(Point(66,0));
	xdist = Xdist(lp,llp);
	ydist = Ydist(lp,llp);
	X1 = coordlp.x + xdist;
	Y1 = coordlp.y;

	up = getUpPoint(Point(66,0));
	coordup = coordinates(up);
	uup = getUUPoint(Point(66,0));
	xdist = Xdist(up,uup);
	ydist = Ydist(up,uup);
	X2 = coordup.x;
	Y2 = coordup.y - ydist;
	x2d[66] = X1;
	y2d[66] = Y2;

	//top left
	rp = getRightPoint(Point(0,50));
	coordrp = coordinates(rp);
	rrp = getRRPoint(Point(0,50));
	xdist = Xdist(rp,rrp);
	ydist = Ydist(rp,rrp);
	X1 = coordrp.x - xdist;
	Y1 = coordrp.y;


	Point dp = getDownPoint(Point(0,50));
	Point coorddp = coordinates(dp);
	Point ddp = getDDPoint(Point(0,50));
	xdist = Xdist(dp,ddp);
	ydist = Ydist(dp,ddp);
	X2 = coorddp.x;
	Y2 = coorddp.y + ydist;
	x2d[3350] = X1;
	y2d[3350] = Y2;


	//top right
	lp = getLeftPoint(Point(66,50));
	coordlp = coordinates(lp);
	llp = getLLPoint(Point(66,50));
	xdist = Xdist(lp,llp);
	ydist = Ydist(lp,llp);
	X1 = coordlp.x + xdist;
	Y1 = coordlp.y;

	dp = getDownPoint(Point(66,50));
	coorddp = coordinates(dp);
	ddp = getDDPoint(Point(66,50));
	xdist = Xdist(dp,ddp);
	ydist = Ydist(dp,ddp);
	X2 = coorddp.x;
	Y2 = coorddp.y + ydist;
	x2d[3416] = X1;
	y2d[3416] = Y2;


	// close both files
	fclose(fp);
	fclose(foutput);

	return 0;

}
