#include <iostream>
#include <vector>
#include "TApplication.h"
#include "TCanvas.h"
#include "TRootCanvas.h"
#include "DataPoints.h"
#include "TF1.h"
#include "TAxis.h"

using namespace std;

DataPoints::DataPoints(const std::vector<std::pair<double,double>> &DataSet): P(DataSet) {;}

DataPoints::DataPoints(const std::vector<double> &data_x, const std::vector< double> &data_y)
{
    int n = sizeof(data_x)/sizeof(data_x[0]) + 1;

    for (int i = 0; i < n; i++)
    {
        P[i].first  = data_x[i];
        P[i].second = data_y[i];
    }
}

DataPoints::DataPoints(int N, double* x, double* y)
{
    for (int i = 0; i < N; i++)
    {
        P[i].first  = x[i];
        P[i].second = y[i];
    }
}

DataPoints::~DataPoints(){;}

void DataPoints::GetGraph(TGraph& graph)
{
    Int_t N = P.size();

    for (int i = 0; i < N; i++)
    {
       graph.SetPoint(i, Double_t(P[i].first), Double_t(P[i].second));
    }
}

void DataPoints::Draw()
{
    TGraph gr;

    GetGraph(gr);

    TCanvas *c1 = new TCanvas("c1","Interpolation Points",200,10,600,400);

    gr.SetMarkerColor(2);
    gr.SetMarkerStyle(87);
    gr.Draw("AP");
    gr.SetTitle("Points of the Data Set");
    gr.GetXaxis()->SetTitle("Time t(s)");
    gr.GetYaxis()->SetTitle("Angular Velocity (rad/s)");
    c1->Print("./plots/Interpolation_Points.png");
}
