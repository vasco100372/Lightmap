#ifndef __DataPoints__
#define __DataPoints__

#include <iostream>
#include <cstdlib>
#include <ostream>
#include <string>
#include <vector>
#include "math.h"
#include "TCanvas.h"
#include "TGraph.h"
#include "TROOT.h"
using namespace std;

class DataPoints{
    public:
    // constructors, destructor
    DataPoints() = default; //default constructor (nothing to be done?)
    DataPoints(int, double*, double*); // build DataPoints from C-arrays of x and y  values
    DataPoints(const std::vector< std::pair<double,double> >&);
    DataPoints(const std::vector< double>&, const std::vector< double>& );
    ~DataPoints();


    // getters
    const std::vector< std::pair<double,double> >& GetPoints();
    void GetGraph(TGraph&);
    // draw points using ROOT object TGraph
    void Draw();
    // friend functions (optional)
    friend std::ostream& operator<< (std::ostream&, const DataPoints&);

    protected:
    vector< pair<double,double> > P; // points
};

#endif
