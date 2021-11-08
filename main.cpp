#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include "all_functions.h"

//Запуск программы - ./a.out
//h - длина деления отрезка [0, 1]


int main(int argc,char *argv[]){

    double *A = NULL, *b = NULL, *v_0 = NULL, *v_1 = NULL, *w = NULL;
    double *c_0 = NULL, *c_1 = NULL, *p_0 = NULL, *p_1 = NULL;

    int n = 64, deg = 3; //n + 1 размер матрицы, deg -степеь многочлена
    double h = 1.0/n;

    A = (double*)malloc((n+1)*(n+1) * sizeof(double));
    b = (double*)malloc((n+1) * sizeof(double));

    v_0 = (double*)malloc((n+1) * sizeof(double));
    v_1 = (double*)malloc((n+1) * sizeof(double));
    w = (double*)malloc((n+1) * sizeof(double));
    c_0 = (double*)malloc((n+1) * sizeof(double));
    c_1 = (double*)malloc((n+1) * sizeof(double));
    p_0 = (double*)malloc((n+1) * sizeof(double));
    p_1 = (double*)malloc((n+1) * sizeof(double));

    if (!(A && b && v_0 && v_1 && w)){
        free(A);
        free(b);
        free(v_0);
        free(v_1);
        free(w);
        return -1;
        }

    if ( argc != 1 )  {
        printf("incorrect data entered");
        return -1;
        }


    //input_matrix_A_b(A, b, n + 1, deg);
    //print_matrix_A_b(A, b, n + 1);
    int k;
    for(int i = 0; i < 4; ++i){
        for(int j = 0; j < 4; ++j){
            input_matrix_A_b(A, b, 8 * pow(2,i) + 1, j);
            k = 8 * pow(2,i);
            printf("h = %d, deg = %d", k, j);
            Lanzo_algorithm(A, b, 8 * pow(2,i) + 1, v_0, v_1, w, c_0, c_1, p_0, p_1, j, 1.0/(8 * pow(2,i)));
        }
    }



    return 0;
}

