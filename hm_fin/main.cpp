#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include "all_functions.h"



int main(int argc,char *argv[]){

    int n = 64, N = (n+1)*(n+2)/2;
    int NE = (7*n*n+9*n+2)/2;
    int deg;
    double l = 1.0;

    if ( argc != 2 )  {
        printf("incorrect data entered");
        return -1;
        }
    deg = atoi(argv[1]);

    if(deg > 2 || deg < 0){
        printf("incorrect data entered");
        return -1;}

    double *b = NULL, *VALUE = NULL, *y = NULL;
    int *INDEX = NULL;

    double *v_0 = NULL, *v_1 = NULL, *w = NULL, *c_0 = NULL, *c_1 = NULL, *p_0 = NULL, *p_1 = NULL;

    //b[i]
    b = (double*)malloc(N * sizeof(double));

    //A[ij]
    VALUE = (double*)malloc(NE * sizeof(double));
    INDEX = (int*)malloc(NE*2 * sizeof(int));

    //for LANCZOS
    v_0 = (double*)malloc(N * sizeof(double));
    v_1 = (double*)malloc(N * sizeof(double));
    w = (double*)malloc(N * sizeof(double));
    c_0 = (double*)malloc(N * sizeof(double));
    c_1 = (double*)malloc(N * sizeof(double));
    p_0 = (double*)malloc(N * sizeof(double));
    p_1 = (double*)malloc(N * sizeof(double));

    //dop mass for mult A*x
    y = (double*)malloc(N * sizeof(double));

    if (!(VALUE && INDEX && b && v_0 && v_1 && w && c_0 && c_1 && p_0 && p_1 && y)){
        free(VALUE);
        free(INDEX);
        free(b);
        free(v_0);
        free(v_1);
        free(c_0);
        free(c_1);
        free(p_0);
        free(p_1);
        free(y);
        return -1;
        }

    //printf("count NE : %d\n", NE);
    input_A(VALUE, INDEX, n, NE);
    input_b(b, n, deg, l);

    /*int i;
    for(i = 0; i < NE; ++i){
        printf("A[%d][%d] = %0.3f\n", INDEX[i], INDEX[i+NE], VALUE[i]);
    }
    printf("\n");
    for(i = 0; i < N; ++i)
            printf("b[%d] = %0.3f\n", i, b[i]);
    printf("\n");*/
    Lanzo_algorithm(VALUE, INDEX, b, n, N, NE, l, deg, v_0, v_1, w, c_0, c_1, p_0, p_1, y);
    /*for(i = 0; i < N; ++i)
            printf("c[%d] = %0.3f\n", i, c_1[i]);*/

    return 0;
}

