#include <iostream>
#include <math.h>
#include <iomanip>
#include <fstream>
#include <limits>
#include <vector>
#include <string>

#define NDEF 10 // default n
#define NF 1001 // fine grid
#define HF 0.002 // h for fine grid

// forward declarations
int runge_exact(std::vector<double> &x, std::vector<double> &f, const int n);
int abs_exact(std::vector<double> &x, std::vector<double> &f, const int n);
int step_exact(std::vector<double> &x, std::vector<double> &f, const int n);
int interp(std::vector<double> &x, std::vector<double> &x_n, std::vector<double> &f, std::vector<double> &f_n, const int n);

int main(int argc, char *argv[]) {

    // for the purposes of this assignment, parallelization does not appear necessary

    int n;
    std::string func_arg; 
    
    if(argc == 2) {
        func_arg = argv[1];
        n = NDEF;
    } else if(argc == 3) {
        func_arg = argv[1];
        n = atoi(argv[2]);
    } else {
        std::cout << "Please supply which function to interpolate func_arg and number of Chebyshev nodes n \n";
        exit(1);
    }

    // fine grid exact vectors
    std::vector<double> x(NF);
    std::vector<double> f(NF);

    // node grid exact vectors
    std::vector<double> x_node(n);
    std::vector<double> f_node(n);

    // x for fine grid
    for (int i = 0; i < NF; ++i) {
        x[i] = -1 + HF*i;
    }

    // x for node grid
    for(int i=0; i < n; ++i) {
        x_node[i] = cos((2.*i+1.)/(n+1)*M_PI/2.);
        std::cout << x_node[i] << "\n";
    }
    
    // find exact data on fine grid and node grid
    if(func_arg == "runge") {
        runge_exact(x,f,NF);
        runge_exact(x_node,f_node,n);
    } else if (func_arg == "abs") {
        abs_exact(x,f,NF);
        abs_exact(x_node,f_node,n);
    } else if (func_arg == "step") {
        step_exact(x,f,NF);
        step_exact(x_node,f,n);
    } else {
        std::cout << "supported functions: 'runge', 'abs', 'step'";
        exit(1);
    }

    // lagrange interpolation
    std::vector<double> f_hat(NF);
    double L;
    interp(x,x_node,f_node,f_hat,n);

    std::ofstream arr_file("interp.dat");
    if(arr_file.is_open()) {
        for(int i=0; i < NF; ++i) {
            arr_file << x[i] << "\t" << f[i] << "\t" << f_hat[i] << "\n"; 
        }
        arr_file.close();
    } else {
        std::cout << "Can't open the file oops";
    }
    
    return 0;
}

int runge_exact(std::vector<double> &x, std::vector<double> &f, const int n){
    // calculate exact values of runge function on domain x with n points
    for (int i = 0; i < n; ++i) {
        f[i] = 1./(1+25*pow(x[i],2));
    }

    return 0;

}

int abs_exact(std::vector<double> &x, std::vector<double> &f, const int n) {
    // calculate exact values of abs(x) on domain x with n points
    for (int i = 0; i < n; ++i) {
        f[i] = abs(x[i]);
    }

    return 0;
}

int step_exact(std::vector<double> &x, std::vector<double> &f, const int n) {
    // calculate exact values of step function on domain x with n points
    for(int i = 0; i < n; ++i) {
        if(x[i]-0.25 >= 0) {
            f[i] = 1;
        } else f[i] = 0;
    }

    return 0;
}

int interp(std::vector<double> &x, std::vector<double> &x_n, std::vector<double> &f, std::vector<double> &f_n, const int n) {
   // given domain x, nodepoints x_n, function values at node points f, and number of node points, perform lagrange
   // interpolation and store in f_n 
    
    double L;
    double rational;
    // overall sum of the exp(log(L_j)) will be signed by whether there is an even number of
    // negative polynomials, i.e. even negative polynomials will be positive
	int sign_count;
    for(int i=0; i < NF; ++i) {
        for(int j=0; j < n; ++j) {
            L = 0;
            sign_count = 0;
            for(int k=0; k < n; ++k) {
                if(k != j) {
                    rational= (x[i]-x_n[k])/(x_n[j] - x_n[k]);
                    sign_count += (rational > 0) ? 0 : 1;
                    L+= log(abs(rational));
                }
            }
            f_n[i] += (sign_count % 2 == 0) ? exp(L)*f[j] : -exp(L)*f[j];
        }
    }

    return 0;
}
