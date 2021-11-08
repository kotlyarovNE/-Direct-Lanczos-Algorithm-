#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "all_functions.h"


double print_matrix_A_b(double *A, double *b, int n){
    int i, j;

    for(i = 0; i < n; ++i){
        for(j = 0; j < n; ++j){
            printf("%.03e ", A[i * n + j]);
        }
        printf(" |%.03e ", b[i]);
        printf("\n");
    }
    printf("\n");
return 0;
}



double f(double x, int deg){
    double rez = 1.0;

    for (int i = 0; i < deg; ++i){
        rez *= x;
    }
return rez;
}

//Подаю на вход n+1, Поэтому h = 1/n-1

double input_matrix_A_b(double *A, double *b, int n, int deg){
    int i, j;
    double h = 1.0/(n - 1);

    for( i = 0 ; i < n; ++i){
        for( j = 0; j < n; ++j){
            if(abs(i-j)>1){
                A[i * n + j] = 0.0;
            }
        }
    }


    A[0] = 2.0;
    A[n*n-1] = 2.0;

    for(i = 1; i < n-1; ++i){
        A[i * n + i] = 4.0;
    }

    for(i = 0; i < n-1; ++i){
        A[i * n + i + 1] = 1.0;
        A[(i + 1) * n + i] = 1.0;
    }


    double x_j, x_j_1, x_1_j;

    b[0] = f(0.0, deg) + 2 * f(h/2, deg);
    b[n - 1] = 2 * f(1 - h/2, deg) + f(1.0, deg);

    for(j = 1; j < n-1; ++j){

        x_j = j * h;
        x_j_1 = (j+1) * h;
        x_1_j = (j-1) * h;

        b[j] = 2 * ( f((x_1_j + x_j)/2, deg) + f(x_j, deg) +  f((x_j + x_j_1)/2, deg) );
    }

return 0;
}
