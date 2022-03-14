#include <iostream>
#include <math.h>
#include <iomanip>
#include <string>
#include <fstream>
#include <vector>
#include <functional>
#include <omp.h>

#define P 5 // num points to avoid magic numbering

int main(int argc, char *argv[]) {

    // initialize input variables
    int n;
    double a;
    double b;
    std::string func;
    
    // initialize index variables
    int i;
    int j;
    
    if(argc == 5) {
        n = atoi(argv[1]);
        a = atof(argv[2]);
        b = atof(argv[3]);
        func = argv[4];
    } else {
        std::cout << "Please specify input number of domains n, integration limits a and b, and function f \n"
                  << "avail functions are x8, abs_poly, step, inv_sqrt, e.g. 16 -1 1 x8 \n";
        exit(1);
    }
    std::function <double(double)> f;

    if(func == "x8") {
        f = [](double x){return pow(x,8);};
    } else if(func == "abs_poly") {
        f = [](double x){return pow(abs(x-1./sqrt(2)),3);};
    } else if(func == "step") {
        f = [](double x){return ((x-1./sqrt(2)) >= 0) ? 1 : 0;};
    } else if(func == "inv_sqrt") {
        f = [](double x){return 1./sqrt(x);};
    } else {
        std::cout << "Invalid function \n";
        exit(1);
    }

    
    std::vector<double> xg = {-0.9061798459386640,-0.5384693101056831,
                               0,0.5384693101056831, 0.9061798459386640}; // that was nasty
    std::vector<double> wg = {0.2369268850561891,0.4786286704993665,
                              0.5688888888888889,0.4786286704993665,0.2369268850561891};

    double L = b-a; // require b > a, need L > 0
    double h = L/n;

    double x0;
    double f0; 

    double sum = 0;

    for(i=1; i < n+1; ++i) {
        for(j=0; j < P; ++j) {
                x0 = (i-1)*h + (xg[j]+1)/2*h;
                f(x0,f0);
                sum += h*f0*wg[j]/2;
        }
    }

    double integ = sum;
    return 0;
}