#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "all_functions.h"

//Use 5 operation and than SOLUTION


double first_operation(double *A, double *v_0, double betta, double *v_1, double *w, int n){
    int i, j;
    double tmp = 0.0;

    for(i = 0; i < n; ++i){
        for(j = 0; j < n; ++j){
            tmp += A[i * n + j] * v_1[j];
        }
        w[i] = tmp;
        tmp = 0.0;
    }

    for(i = 0; i < n; ++i){
        w[i] -= betta * v_0[i];
    }
return 0;
}


double second_operation(double *p_1, double *v_1, double betta, double *p_0, double ny, int n){
    int i;

    for(i = 0; i < n; ++i){
        p_1[i] = (v_1[i] - betta * p_0[i]) / ny;
    }

return 0;
}



double mult_mass(double *v_1, double *w, double betta, int n){
    int i;

    for(i = 0; i < n; ++i){
        v_1[i] = w[i]/betta;
    }
return 0;
}


double v_0_into_v_1(double *v_0, double *v_1, int n){
    int i;

    for(i = 0; i < n; ++i)
        v_0[i] = v_1[i];

return 0;
}



double skal_pr(double *w, double *v, int n){
    double rez = 0.0;

    for(int i = 0; i < n; ++i)
        rez += w[i] * v[i];

return(rez);
}



double initial_position_in_LA(double *b, int n, double *v_0, double *v_1, double *p_0, double *c_0){
    double tmp;
    int i;

    for(i = 0; i < n; ++i){
        v_0[i] = 0.0;
        p_0[i] = 0.0;
        c_0[i] = 0.0;
    }

    tmp = sqrt(skal_pr(b, b, n));

    for(i = 0; i < n; ++i)
        v_1[i] = b[i]/tmp;

return 0;
}

double Norma_nevazki(double *A, double *b, double *x, int n){
    double rez = 0.0;
    double tmp = 0.0;

    for(int i = 0; i < n; ++i){
        for(int j = 0; j < n; ++j){
            tmp += A[i * n + j] * x[j];
        }
        tmp *= -1.0;
        tmp += b[i];
        rez += tmp * tmp;
        tmp = 0.0;
        }
return sqrt(rez);
}



double DELTA(double *A, double *b, double *c, int deg, int n, double h){
    double rez = 0.0;
    double rez_1 = 0.0, rez_2 = 0.0, rez_3 = 0.0;
    double tmp = 0.0;

    for(int i = 0; i < n; ++i){
        for(int j = 0; j < n; ++j){
            tmp += A[i * n + j] * c[j];
        }
        tmp *= c[i];
        rez_3 += tmp;
        tmp = 0.0;
    }

    rez_3 *= h / 6;

    rez_2 = -2.0 * skal_pr(b, c, n) * h / 6;

    rez_1 = 1.0 / (2.0 * (double)deg + 1.0);

    rez = (rez_1 + rez_2 + rez_3);

return sqrt(rez);
}



double Lanzo_algorithm(double *A, double *b, int n, double *v_0, double *v_1, double *w, double *c_0, double *c_1, double *p_0, double *p_1, int deg, double h){

    double alpha, betta = 0.0, lambda = 0.0, ksi = sqrt(skal_pr(b, b, n)), ny;
    double Norm_0 = sqrt(skal_pr(b, b, n)), epsilon_1 = 1e-4, epsilon_2 = 1e-6;

    initial_position_in_LA(b, n, v_0, v_1, p_0, c_0);


    int j = 1;

    while( true ){

        if(Norma_nevazki(A, b, c_1, n)/Norm_0 <= epsilon_2)
            break;

        else{

            first_operation(A, v_0, betta, v_1, w, n); //Меняется только w
            alpha  = skal_pr(w, v_1, n);               //Считаем альфу

            if(j > 1){
                lambda = betta / ny;
                ksi *= (lambda * (-1.0));
            }

            ny = alpha - lambda * betta;

            second_operation(p_1, v_1, betta, p_0, ny, n);         //Заполняем p_1
            second_operation(c_1, c_0, ksi*(-1.0), p_1, 1.0, n);   //Заполняем c_1
            second_operation(w, w, alpha, v_1, 1.0, n);            //Заполняем w

            betta  = sqrt(skal_pr(w, w, n));                       //Считаем бетту

            v_0_into_v_1(v_0, v_1, n);                 //V_1 уходит на V_0
            mult_mass(v_1, w, betta, n);               //Меняем V_1 для стед.итерации
            v_0_into_v_1(p_0, p_1, n);                 //p_0 должен стать p_1
            v_0_into_v_1(c_0, c_1, n);                 //c_0 должен стать c_1

            j++;
        }
    }

    /*for(int i = 0; i < n; ++i){
        printf("%.03e ", c_1[i]);
    }
    printf("\n%0.3e ", Norma_nevazki(A, b, c_1, n));*/

    double delt;
    delt = DELTA(A, b, c_1, deg, n, h);
    printf("\nDELTA = %.03e ", delt);
    printf("\nKol-vo iter = %d ", j-1);
    printf("\n");


return 0;
}

