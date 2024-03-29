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
int calc_max(std::vector<double> &f, std::vector<double> &f_n, double &l2, double &max);

int main(int argc, char *argv[]) {

	// big apologies for the copy paste, I wrote this and realized I misunderstood
	// that the n = {10,20,40} part should all be on one plot per function

    std::string func_arg; 

    if(argc == 2) {
        func_arg = argv[1];
    } else {
        std::cout << "Please supply which function to interpolate func_arg \n";
        exit(1);
    }

    // fine grid exact vectors
    std::vector<double> x(NF);
    std::vector<double> f(NF);

	// n values
	std::vector<int> n = {10,20,40};
	
    // node grid exact vectors
    std::vector<double> x10(n[0]);
	std::vector<double> x20(n[1]);
    std::vector<double> x40(n[2]);

    std::vector<double> f10(n[0]);
    std::vector<double> f20(n[1]);
    std::vector<double> f40(n[2]);

    // x for fine grid
    for (int i = 0; i < NF; ++i) {
        x[i] = -1 + HF*i;
    }

    // x for 10 node grid
    for(int i=0; i < n[0]; ++i) {
        x10[i] = cos((2.*i+1.)/(n[0]+1)*M_PI/2.);
    }
    
    // x for 10 node grid
    for(int i=0; i < n[1]; ++i) {
        x20[i] = cos((2.*i+1.)/(n[1]+1)*M_PI/2.);
    }

    // x for 10 node grid
    for(int i=0; i < n[2]; ++i) {
        x40[i] = cos((2.*i+1.)/(n[2]+1)*M_PI/2.);
    }
    // find exact data on fine grid and node grid
    if(func_arg == "runge") {
        runge_exact(x,f,NF);
        runge_exact(x10,f10,n[0]);
        runge_exact(x20,f20,n[1]);
        runge_exact(x40,f40,n[2]);
    } else if (func_arg == "abs") {
        abs_exact(x,f,NF);
        abs_exact(x10,f10,n[0]);
        abs_exact(x20,f20,n[1]);
        abs_exact(x40,f40,n[2]);
    } else if (func_arg == "step") {
        step_exact(x,f,NF);
        step_exact(x10,f10,n[0]);
        step_exact(x20,f20,n[1]);
        step_exact(x40,f40,n[2]);
    } else {
        std::cout << "supported functions: 'runge', 'abs', 'step'";
        exit(1);
    }

    // lagrange interpolation
    std::vector<double> f10_hat(NF);
    std::vector<double> f20_hat(NF);
    std::vector<double> f40_hat(NF);
    
	interp(x,x10,f10,f10_hat,n[0]);
	interp(x,x20,f20,f20_hat,n[1]);
	interp(x,x40,f40,f40_hat,n[2]);

    std::ofstream arr_file("interp.dat");
    if(arr_file.is_open()) {
        for(int i=0; i < NF; ++i) {
            arr_file << x[i] << "\t" << f[i] << "\t" << f10_hat[i] << "\t" << f20_hat[i] << "\t" << f40_hat[i] << "\n"; 
        }
        arr_file.close();
    } else {
        std::cout << "Can't open the file oops";
    }

    // error collection no longer necessary for this version
    /* double l2;
    double max;

    calc_max(f,f_hat,l2,max);

    std::cout << n << "\t" << l2 << "\t" << max << "\n";
	*/
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
/*
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
} */
