#ifndef MYLIB_H
#define MYLIB_H

#include "Cell.h"
#include "vector"

extern         Cell* cells; 
extern int     plotgrid(int nx, int ny, double* x2d, double* y2d);
extern int     nx, ny;
extern double* x2d;
extern double* y2d;
extern double  sx;
extern double  sy;
extern int     readgrid();
extern double  L; 
extern std::vector<double> maxA_values; 
extern std::vector<double> maxB_values; 
extern std::vector<double> maxC_values; 
extern std::vector<double> maxD_values; 
extern std::vector<double> L2Atot_values; 
extern std::vector<double> L2Btot_values; 
extern std::vector<double> L2Ctot_values; 
extern std::vector<double> L2Dtot_values; 

int    readgrid(); 

int    calcCell();

int    coloredCells(int nx, int ny, double* x2d, double* y2d);

int    coloredAreasEta(int nx, int ny, double* x2d, double* y2d);

int    coloredAreasCsi(int nx, int ny, double* x2d, double* y2d);

int    initializeQ(); 
int    stegerinitializeQ(); 

int    firstColumn(); 
int    stegerfirstcolumn(); 

int    Fluxcalc();
int    stegerFluxcalc();

int    slipwall(); 

int    slipwall2(); 

int    Normali(int nx, int ny, double* x2d, double* y2d);

int    timeStep(); 

int    iter(); 
int    stegerIter(); 

int    PLOTiter(int nx, int ny, double* x2d, double* y2d);

int    makeItVec();

extern double getRho(int c); 

double getU  (int c); 

double getV  (int c); 
double getUcsi  (int c); 
double getVeta  (int c); 
double getP  (int c);
double getE0 (int c); 
double getB (int c); 
double getT (int c); 

int NormPlots (); 
#endif 























