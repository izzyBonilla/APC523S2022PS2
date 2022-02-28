#include <iostream>
#include <math.h>
#include <iomanip>
#include <fstream>
#include <limits>
#include <vector>

#define NDEF 10

// forward declarations
int runge_exact(std::vector<double> &x, std::vector<double> &f, const int n);
int abs_exact(std::vector<double> &x, std::vector<double> &f, const int n);
int step_exact(std::vector<double> &x, std::vector<double> &f, const int n);

int main(int argc, char *argv[]) {
    int n;
    
    if(argc == 1) {
        n = NDEF;
    } else if(argc == 2) {
        n = atoi(argv[1]);
    } else {
        std::cout << "Please supply number of gridpoints n \n";
        exit(1);
    }

    int i;
    double h = 2./n;
    n++; // incrementing to have the actual closed set [-1,1]

    std::vector<double> x(n);
    std::vector<double> runge(n);


    for (i = 0; i < n; ++i) {
        x[i] = -1 + h*i;
    }

    abs_exact(x,runge,n);

    std::ofstream arr_file("interp.dat");
    if(arr_file.is_open()) {
        for(i=0; i < n; ++i) {
            arr_file << x[i] << "\t" << runge[i] << "\n"; 
        }
        arr_file.close();
    } else {
        std::cout << "Can't open the file oops";
    }

    return 0;
}

int runge_exact(std::vector<double> &x, std::vector<double> &f, const int n){
    for (int i = 0; i < n; ++i) {
        f[i] = 1./(1+25*pow(x[i],2));
    }

    return 0;

}

int abs_exact(std::vector<double> &x, std::vector<double> &f, const int n) {
    for (int i = 0; i < n; ++i) {
        f[i] = abs(x[i]);
    }

    return 0;
}

int step_exact(std::vector<double> &x, std::vector<double> &f, const int n) {
    for(int i = 0; i < n; ++i) {
        if(x[i]-0.25 >= 0) {
            f[i] = 1;
        } else f[i] = 0;
    }

    return 0;
}