#include <vector>
#include <math.h>
#include <iostream>

typedef std::vector<double> Vec;
typedef std::vector<Vec> Mat;

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

    return 0;
}