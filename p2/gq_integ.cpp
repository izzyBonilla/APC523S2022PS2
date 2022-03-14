#include <iostream>
#include <math.h>
#include <iomanip>
#include <fstream>
#include <vector>
#include <omp.h>

int main(int argc, char *argv[]) {
    int n;
    double a;
    double b;
    
    
    if(argc == 4) {
        n = atoi(argv[1]);
        a = atof(argv[2]);
        b = atof(argv[3]);
    } else {
        std::cout << "Please input number of domains n and integration limits a and b \n";
        exit(1);
    }

        std::vector<double> xg = {-0.9061798459386640,-0.5384693101056831,
                                0,0.5384693101056831, 0.9061798459386640}; // that was nasty
        std::vector<double> wg = {0.2369268850561891,0.4786286704993665,
                                  0.5688888888888889,0.4786286704993665,0.2369268850561891};

        for(int i = 0; i < 5; ++i) {
            std::cout << xg[i] << "\t" << wg[i] << "\n";
        }

    return 0;
}