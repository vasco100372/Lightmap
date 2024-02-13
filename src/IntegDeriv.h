#ifndef __INTEGDERIV__
#define __INTEGDERIV__
#include "Lightmap.h"

class IntegDeriv {

    public:

        IntegDeriv(Lightmap&);
        IntegDeriv(double, double, Lightmap&);
        ~IntegDeriv() = default;

        // integration methods
        void simpsonRule(int, double&, double&);
        void MonteCarlo(int, double&, double&);

        // derivative methods

    private:

        Lightmap F;
        double xi, xf;
};
#endif
