#include <vector>
#include <math.h>
#include <iostream>
#include <limits> 

typedef std::vector<double> Vec;

#define N 100
#define ITER 1000
#define a 2
int main(int argc, char *argv[]) {

    int i;
    int j;
    int k;
    int jvec;

    if(argc==2){
        jvec = atoi(argv[1]);
    } else {
        std::cout << "Usage: gs j where j is the jth eigenvalue-eigenvector pair to solve for \n";
        exit(1);
    }

    // calculate eigenvalue and eigenvector
    double lambda = a - 2*cos(jvec*M_PI/(N+1));
    Vec v(N);

    for(i=0; i<N; ++i){
        v[i] = sin((i+1)*jvec*M_PI/(N+1));
    }

    // Build T2

    Vec x_new(N);
    Vec x_old(N);
    Vec err(ITER);

    // main loop
    double sigma;
    double curr_err;

    for(k=0; k<ITER; ++k) {
        curr_err = 0;
        for(i=0; i<N; ++i) {
            if(i==0) {
                sigma = -x_old[i+1];
            } else if(i==N-1) {
                sigma = -x_old[i-1];
            } else {
                sigma = -x_old[i-1] - x_old[i+1];
            }

            x_new[i] = 0.5*(lambda*v[i]-sigma);
            if(abs(x_new[i] - v[i]) > curr_err) {
                curr_err = abs(x_new[i] - v[i]);
            }
        }
        err[k] = curr_err;
        x_old = x_new;

        std::cout << k << "\t" << curr_err << "\n";
    }

    return 0;
}