#include <iostream>
#include <math.h>
#include <iomanip>
#include <fstream>
#include <limits>
#include <vector>
#include <string>
#include <omp.h>

#define NDEF 10 // default n
#define NF 1001 // fine grid
#define HF 0.002 // h for fine grid

// forward declarations
int calc_max(std::vector<double> &f, std::vector<double> &f_n, double &l2, double &max);

int main(int argc, char *argv[]) {

    // for the purposes of this assignment, parallelization does not appear necessary

    int n;
    std::string func_arg; 
    int log_flag = 1;

    if(argc == 2) {
        func_arg = argv[1];
        n = NDEF;
    } else if(argc == 3) {
        func_arg = argv[1];
        n = atoi(argv[2]);
    } else if(argc == 4){
        func_arg = argv[1];
        n = atoi(argv[2]);
        log_flag = atoi(argv[3]);
    } else {
        std::cout << "Please supply which function to interpolate func_arg, number of Chebyshev nodes n" << "\n" << "and optional flag for data log (1 for yes 0 for no) \n";
        exit(1);
    }

    // fine grid exact vectors
    std::vector<double> x(NF);
    std::vector<double> f(NF);

    // node grid exact vectors
    std::vector<double> x_node(n);
    std::vector<double> f_node(n);

    // set up index variables for parallelism
    int i;
    int j;
    int k;

    
    std::vector<double> f_hat(NF);
    // x for fine grid
    #pragma omp parallel
    {
    #pragma omp for
    for (i = 0; i < NF; ++i) {
        x[i] = -1 + HF*i;
    }

    // x for node grid
    #pragma omp for
    for(int i=0; i < n; ++i) {
        x_node[i] = cos((2.*i+1.)/(n+1)*M_PI/2.);
    }
    // find exact data on fine grid and node grid
    if(func_arg == "runge") {
        #pragma omp for
        for (int i = 0; i < NF; ++i) {
            f[i] = 1./(1+25*pow(x[i],2));
        }
        #pragma omp for
        for (int i = 0; i < n; ++i) {
            f_node[i] = 1./(1+25*pow(x_node[i],2));
        }
    } else if (func_arg == "abs") {
        #pragma omp for
        for (int i = 0; i < NF; ++i) {
            f[i] = abs(x[i]);
        }
        #pragma omp for
        for (int i = 0; i < n; ++i) {
        f_node[i] = abs(x_node[i]);
        }
    } else if (func_arg == "step") {
        #pragma omp for
        for(int i = 0; i < NF; ++i) {
            if(x[i]-0.25 >= 0) {
                f[i] = 1;
            } else f[i] = 0;
        }
        #pragma omp for
        for(int i = 0; i < n; ++i) {
            if(x_node[i]-0.25 >= 0) {
                f_node[i] = 1;
            } else f[i] = 0;
        }
    } else {
        std::cout << "supported functions: 'runge', 'abs', 'step'";
        exit(1);
    }
    
    // lagrange interpolation

    double L;
    double rational;
    // overall sum of the exp(log(L_j)) will be signed by whether there is an even number of
    // negative polynomials, i.e. even negative polynomials will be positive
	int sign_count;
    #pragma omp for private(j,k)
    for(i=0; i < NF; ++i) {
        for(j=0; j < n; ++j) {
            L = 0;
            sign_count = 0;
            for(k=0; k < n; ++k) {
                if(k != j) {
                    rational= (x[i]-x_node[k])/(x_node[j] - x_node[k]);
                    sign_count += (rational > 0) ? 0 : 1;
                    L+= log(abs(rational));
                }
            }
            f_hat[i] += (sign_count % 2 == 0) ? exp(L)*f_node[j] : -exp(L)*f_node[j];
        }
    }
    }

    if(log_flag) {
        std::ofstream arr_file("interp.dat");
        if(arr_file.is_open()) {
            for(int i=0; i < NF; ++i) {
                arr_file << x[i] << "\t" << f[i] << "\t" << f_hat[i] << "\n"; 
            }
            arr_file.close();
        } else {
            std::cout << "Can't open the file oops";
        }
    }

    // error collection
    double l2;
    double max;

    calc_max(f,f_hat,l2,max);

    std::cout << n << "\t" << l2 << "\t" << max << "\n";

    return 0;
}

int calc_max(std::vector<double> &f, std::vector<double> &f_n, double &l2, double &max) {
    // calculates L2 error and max error given an interpolated function f_n and
    // exact function f

    double sum;
    double diff;
    max = 0;

    for(int i = 0; i < NF; ++i) {
        diff = f_n[i] - f[i];
        sum += pow(diff,2);
        max = (abs(diff)) ? abs(diff) : max;
    }

    l2 = sqrt(sum/NF);
    return 0;
}
