#include <stdlib.h>

double* c_sum(const double* matrix, int n, int m){
    double* results = (double*) malloc(sizeof(double) * n);
    int index = 0;

    for(int i=0;i<n*m;i+=n){
        results[index] = 0;
        for(int j=0;j<m;j++){
            results[index] += matrix[i+j];
        }
        index += 1;
    }

    return results;
}
