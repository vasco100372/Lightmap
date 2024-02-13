#include <iostream>
#include <math.h>
#include <time.h>
#include "IntegDeriv.h"
#include "Lightmap.h"

using namespace std;


IntegDeriv::IntegDeriv(Lightmap& P) : F(P){;}

IntegDeriv::IntegDeriv(double a, double b, Lightmap& P) : F(P)
{
    if(a>b){
        xi = b;
        xf = a;
    }
    else{
        xi=a;
        xf=b;
    }
}

double Derivative_2nd(double x, double j, double h, Lightmap& F) //Second derivative using mid point derivative
{
    double derivative_2 = 0;

    derivative_2 = (-F.GetPower(x + 2*h, j) +16*F.GetPower(x+h, j) -30* F.GetPower(x, j)-16*F.GetPower(x-h, j)-F.GetPower(x-2*h, j))/(12*h*h);
    return derivative_2;
}

double Derivative_4th(double x, double j, double h, Lightmap& F)
{
  double derivative_4 = 0;

  derivative_4 = (F.GetPower(x + 2*h, j)-2*F.GetPower(x + h, j)+6*F.GetPower(x, j)-4*F.GetPower(x - h, j)+F.GetPower(x - 2*h, j))/pow(h,4);
  return derivative_4;
}

void IntegDeriv::simpsonRule(int N, double& Integral, double& Error)
{
    if(N%2==1) {
      cout << "O método de Simpson só aceita números de pontos pares!" << endl;
      N++;
      cout << "Integral calculado com " << N << " pontos:" << endl;
    }

    double h=(xf-xi)/N;

    double soma=0;
    double erro=0;
    double max=0;

    //posicao[0]=xi;

    //A derivada no 1ºponto é dada com foward difference
    //derivadas[0]=(-F.operator()(xi + 2*h)+4*F.operator()(xi + h)+3*F.operator()(xi))/(2*h);
    //A derivada no último ponto é dada com backward difference
    //derivadas[N]=(F.operator()(xi - 2*h)-4*F.operator()(xi - h)+3*F.operator()(xi))/(2*h);


    //Descobrir o máximo das derivadas

    for (int i = 0; i < N; i++)
    {
        for(int j=1;j<N/2;j++)
        {
            soma+= (h/3)*(F.GetPower(2*j-2 , i)+4*F.GetPower(2*j-1, i)+F.GetPower(2*j, i));
        }
    }

    for(double j = 0; j < N; j++)
    for(double j = 0; j < N; j++)
    {
        for (double i = xi + 2*h; i <= xf - 2*h; i+= h)
        {
            Derivative_4th(i, j, h, F);

            if (fabs(Derivative_4th(i, j, h, F)) > max)
            {
                max = fabs(Derivative_4th(i, j, h, F));
            }
        }
    }


    Integral=soma;
    Error= (max*(xf-xi)*pow(h,4))/180;
    cout << "Integral de Simpson bem calculado"<<endl;
    cout << "Integral: " << Integral << ", com erro: "<<Error<<endl;
}

void IntegDeriv::MonteCarlo(int N, double& Integral, double& Error)
{
    srand(time(NULL));

    double n = N;
    double h = (xf-xi)/n;
    double a1, sum = 0, sum2 = 0, r_x_2, r_y_2;
    int r_x, r_y;

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            a1 = double(rand())/double(RAND_MAX);
            r_x = floor(((xf- xi)*a1)) + xi;
            r_y = floor(((xf- xi)*a1)) + xi;
            r_x_2 = floor(((sqrt(fabs(xf)) - sqrt(fabs(xi)))*a1)) + floor(sqrt(fabs(xi)));
            r_y_2 = floor(((sqrt(fabs(xf)) - sqrt(fabs(xi)))*a1)) + floor(sqrt(fabs(xi)));
            sum += F.GetPower(r_x, r_y);
            sum2 += F.GetPower(r_x_2*r_x_2, r_y_2*r_y_2);
        }
    }

    Integral = sum*h;
    Error = ((xf-xi)/sqrt(n))*sqrt((1./n)*sum2 - pow((1./n)*sum, 2));

    cout << "O valor da Integral é: " << Integral << endl;
    cout << "O erro associado é: " << Error << endl;
}
