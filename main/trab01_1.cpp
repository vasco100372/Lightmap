#include <iostream>
#include <vector>
#include "IntegDeriv.h"
#include "Lightmap.h"

using namespace std;

//Assuming square plane centered on z axis

//Size of the cells
#define DX 1.0
#define DY 1.0

//Size of the plane (cm)
#define SIZE_X 400.0
#define SIZE_Y 400.0

//Flux
#define FLUX 5000

int main()
{
    double Integral = 0.0, Error = 0.0, Integral_1 = 0.0, Error_1 = 0.0;
    Lightmap lm(DX, DY, SIZE_X, SIZE_Y, FLUX);
    lm.CalcRadiantIntensity();
    lm.FillVectors(100.00);


    //Alinea a
    cout << "Valores da irradiância (W/cm²):\n"
         << "(0, 0, 100):      " << lm.CalcIrradiance(0., 0., 100.) << endl
         << "(50, 0, 100):     " << lm.CalcIrradiance(50., 0., 100.) << endl
         << "(0, 50, 100):     " << lm.CalcIrradiance(0., 50., 100.) << endl
         << "(200, 100, 100):  " << lm.CalcIrradiance(200., 100., 100.) << endl
         << "(-100, 200, 100): " << lm.CalcIrradiance(-100., 200., 100.) << endl
         << "(60, 50, 100):    " << lm.CalcIrradiance(60., 50., 100.) << "\n\n\n";

    //Alinea b
    cout << "\n\n";
    lm.Draw();

    //Alinea c
    cout << "A potência total incidente no plano é:  " << lm.CalcTotalPower(100.00) << "  W\n"
         << "\n\n\n";

    //Alinea d
    lm.DrawMap2();
    cout << "\n\n";

    //Alinea e
    IntegDeriv Intg(0., 399., lm);

    Intg.MonteCarlo(400, Integral, Error);
    Intg.simpsonRule(400, Integral , Error);

/*
    cout << "Valor do integral utlizando os métodos:\n "
         << "Monte Carlo: " << Intg.MonteCarlo(400, Integral, Error)
         << "Simpson:     " << Intg.simpsonRule(400, Integral , Error) << "\n\n";

*/
    return 0;
}
