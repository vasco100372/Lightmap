#ifndef __Lightmap__
#define __Lightmap__

#include <vector>
#include "TCanvas.h"
#include "TH2D.h"
#include "TStyle.h"
#include "TApplication.h"

using namespace std;

class Lightmap{
public:

    Lightmap() = default;
    Lightmap(double, double, double, double, double); //constructor arguments: size of cell in x and y, size of wall in x and in y
    ~Lightmap() = default;

    void CalcRadiantIntensity(); //Calculate radiant intensity
    void FillVectors(double); //Fill vectors with values required in calculations

    double CalcIndividualPower(double, double, double, double); //x, y, z, irradiance
    double CalcIrradiance(double, double, double); //x, y, z coordinates of the cell
    double CalcTotalPower(double); //Calculates total power; z coordinate of the cells
    //double CalcTotalPowerError(); //Calculates error of total power

    //Getters
    double GetRadiantInt();
    double GetFlux();
    double GetPower(int, int);

    void Draw(); //Draw lightmap
    void DrawMap2(); //Draw graph: Power/z


private:

    double dx, dy; //Size of the cells (cm)
    double sizex, sizey, xmin, ymin; //size of the plane x and y (cm)
    int n_cell_x, n_cell_y; //number of cells in x and y
    double flux; //Flux of the source
    vector<double> xx, yy; //Fill matrix with power values
    double radiant_intensity;
    vector<vector <double>> pow_values; //power values on the cells


};
#endif
