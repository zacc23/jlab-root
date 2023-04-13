// https://root.cern/doc/master/TGraph_8cxx_source.html#l01875
#include <iostream>
using namespace std;

double integrate(int lines, double BX[], double F2[]) {
    // last = number of points (lines)
    int first = 0, last = lines;
    int np = last - first + 1;
    double sum = 0;
    for (int i = first; i <= last; i++) {
       int j = first + (i - first + 1) % np;
       // fY -> F2, fX -> BX 
       sum += (F2[i] + F2[j]) * (BX[j] - BX[i]);
    }

    return 0.5 * abs(sum);
}
