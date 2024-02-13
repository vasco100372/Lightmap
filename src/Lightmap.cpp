#include "Lightmap.h"
#include "TRootCanvas.h"
#include "TGraph.h"
#include <cmath>
#include <iostream>
#include <cstdlib>

#define STEP_MAP2 1

using namespace std;


Lightmap::Lightmap(double dx_, double dy_, double sx_, double sy_, double flux_): dx(dx_), dy(dy_), sizex(sx_), sizey(sy_), flux(flux_){
    n_cell_x=sizex/dx;
    n_cell_y=sizey/dy;
    xmin=-sizex/2;
    ymin=-sizey/2;
    vector<double> v;
    for(int i=0;i<n_cell_x;i++){
        v.push_back(0.);
    }
    for(int i=0;i<n_cell_y;i++){
        pow_values.push_back(v);
    }
}

double Lightmap::CalcIrradiance(double x, double y, double z)
{
    return radiant_intensity/(x*x + y*y + z*z);
}

void Lightmap::FillVectors(double z = 100.0){

     for(int i=0; i<n_cell_x; i++){
         xx.push_back(xmin+(2*i-1)*dx/2);
     }
     for(int i=0; i<n_cell_y; i++){
         yy.push_back(ymin+(2*i-1)*dy/2);
     }

     for(int i=0; i<n_cell_x; i++){
         for(int j=0;j<n_cell_y; j++){
             pow_values[i][j]=CalcIndividualPower(xx[i],yy[j], z, CalcIrradiance(xx[i],yy[j], z));
         }
     }
}

double Lightmap::CalcIndividualPower(double x, double y, double z, double irradiance)
{
    return irradiance*z/sqrt(x*x+y*y+z*z);
}

double Lightmap::CalcTotalPower(double z)
{
    double p_inc_tot=0.0;
    for(int i=0; i<n_cell_x; i++){
        for(int j=0;j<n_cell_y; j++){
            p_inc_tot+= CalcIndividualPower(xx[i],yy[j], z, CalcIrradiance(xx[i],yy[j], z))*dx*dy; //CalcIndividualPower(xx[i], 0.0, 100.0, 0.3);
        }
    }
    return p_inc_tot;
}

void Lightmap::CalcRadiantIntensity()
{
    radiant_intensity = flux/(4.0*M_PI);
}

//Getters
double Lightmap::GetRadiantInt()
{
    return radiant_intensity;
}

double Lightmap::GetFlux()
{
    return flux;
}

double Lightmap::GetPower(int x, int y)
{
    return pow_values[x][y];
}

void Lightmap::Draw()
{
    int i=0,j=0;
    auto h2 = new TH2D("h2", "Mapa de luz", n_cell_x, xmin, -xmin, n_cell_y, ymin, -ymin);
    for (i=0;i<n_cell_x;i++) {
        for (j=0;j<n_cell_y;j++) {
            h2->Fill(xx[i], yy[j], pow_values[i][j]);
        }
    }

    //TApplication app("app", nullptr, nullptr);
    auto c = new TCanvas("canvas", "lightmap canvas", 0, 0, 800, 800);
    gStyle->SetPalette(kDarkBodyRadiator);
    h2->Draw("COLZ");
    c->Update();
    c->Print("trab01_mapa_1.pdf");
    TRootCanvas *rc = (TRootCanvas *)c->GetCanvasImp();
    //rc->Connect("CloseWindow()", "TApplication", gApplication, "Terminate()");
    //app.Run();
}

void Lightmap::DrawMap2()
{
    TCanvas* c = new TCanvas("c", "Map2", 0, 0, 800, 600);
    TGraph* map2 = new TGraph();
    map2->SetTitle("Potencia total incidente em funcao da distancia ao plano; z (cm); P total (W)");
    map2->SetLineColor(2);
    map2->SetLineWidth(5);

    for(int varz = 10; varz <=1000; varz += STEP_MAP2)
    {
        map2->SetPoint(varz-10, varz, CalcTotalPower(varz));
    }

    map2->Draw("AL");
    c->Print("trab01_mapa_2.pdf");
}

/*
double Derivative_2nd_x(int i, int j, int h) //Second derivative using mid point derivative
{
    double derivative_2_x = 0;

    //derivative_2_x = 2.0;
    //derivative_2_x = (-GetPower(i+2*h,j) +16*GetPower(i+h,j) -30* GetPower(i,j)-16*GetPower(i-h,j)-GetPower(i-2*h,j))/(12*h*h);
    derivative_2_x = (-GetPower(i+2*h,j+2*h) +16*GetPower(i+h,j+h) -30* GetPower(i,j)-16*GetPower(i-h,j-h)-GetPower(i-2*h,j-2*h))/(12*h*h);
    return derivative_2_x;
}
double Derivative_2nd_y(int i, int j, int h,Lightmap& M) //Second derivative using mid point derivative
{
    double derivative_2_y = 0;

    //derivative_2_y = 2.0;
    derivative_2_y = (-GetPower(i,j+2*h) +16*GetPower(i,j+h) -30* GetPower(i,j)-16*GetPower(i,j-h)-GetPower(i,j-2*h))/(12*h*h);
    return derivative_2_y;
}

/*double Lightmap::CalcTotalPowerError(Lightmap& M)
{
    int h = 1;
    double Error; //arranjar melhor forma de calcular o h se dx e dy não forem =1
    double maxx=0;
    double maxy=0;

    for (int i = 0; i <n_cell_x-2; i++)
    {
        for(int j = 0; j<n_cell_y;j++){
            //Derivative_2nd_x(i,j,h);

            if (abs(Derivative_2nd_x(i,j,h,M)) > maxx)
            {
                maxx = abs(Derivative_2nd_x(i,j,h,M));
            }
        }


    }

    for (int j = 0; j <n_cell_y-2; j++)
    {
        for(int i=0; i<n_cell_x;i++){
            Derivative_2nd_y(i,j,h,M);
        }

        if (fabs(Derivative_2nd_y(i,j,h,M)) > max)
        {
            maxy = fabs(Derivative_2nd_y(i,j,h,M));
        }
    }
    
    cout<<"Segunda derivada em x: "<<maxx<<endl;
    //cout<<"Segunda derivada em y: "<<maxy<<endl;
    Error= (maxx*(-2*xmin)*pow(h,3))/24;

    cout << Derivative_2nd_x(2,2,1) << endl;

    return maxx;
}
*/
