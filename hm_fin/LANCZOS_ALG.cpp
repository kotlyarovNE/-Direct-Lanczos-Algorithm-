#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "all_functions.h"

//Use 5 operation and than SOLUTION

int mult_A_x(double *VALUE, int *INDEX, double *x, int NE, int N, double *y){

    int i,j,k;
    double v;

    for(i = 0; i < N; ++i)
        y[i] = 0.0;

    for(k = 0; k < NE; ++k){
        v = VALUE[k];
        i = INDEX[k];
        j = INDEX[k+NE];
        y[i] += v*x[j];
    }

return 0;
}



double first_operation(double *VALUE, int *INDEX, double *v_0, double betta, double *v_1, double *w, int N, int NE, double *y){
    int i, j, k;
    double v;
    for(i = 0; i < N; ++i)
        y[i] = 0.0;

    for(k = 0; k < NE; ++k){
        v = VALUE[k];
        i = INDEX[k];
        j = INDEX[k+NE];
        y[i] += v*v_1[j];
    }


    for(i = 0; i < N; ++i)
        w[i] = y[i] - betta * v_0[i];

return 0;
}


double second_operation(double *p_1, double *v_1, double betta, double *p_0, double ny, int N){
    int i;

    for(i = 0; i < N; ++i)
        p_1[i] = (v_1[i] - betta * p_0[i]) / ny;

return 0;
}



double mult_mass(double *v_1, double *w, double betta, int N){
    int i;

    for(i = 0; i < N; ++i)
        v_1[i] = w[i]/betta;

return 0;
}


double v_0_into_v_1(double *v_0, double *v_1, int N){
    int i;

    for(i = 0; i < N; ++i)
        v_0[i] = v_1[i];

return 0;
}



double skal_pr(double *w, double *v, int n){
    double rez = 0.0;

    for(int i = 0; i < n; ++i)
        rez += w[i] * v[i];

return(rez);
}



double initial_position_in_LA(double *b, int N, double *v_0, double *v_1, double *p_0, double *c_0){
    double tmp;
    int i;

    for(i = 0; i < N; ++i){
        v_0[i] = 0.0;
        p_0[i] = 0.0;
        c_0[i] = 0.0;
    }

    tmp = sqrt(skal_pr(b, b, N));

    for(i = 0; i < N; ++i)
        v_1[i] = b[i]/tmp;

return 0;
}

double Norma_nevazki(double *VALUE, int *INDEX, double *b, double *x, int N, int NE, double *y){
    double rez = 0.0;
    double tmp = 0.0;
    int i,j,k;
    double v;

    for(i = 0; i < N; ++i)
        y[i] = 0.0;

    for(k = 0; k < NE; ++k){
        v = VALUE[k];
        i = INDEX[k];
        j = INDEX[k+NE];
        y[i] += v*x[j];
    }

    for(i = 0; i < N; ++i){
        tmp = b[i]-y[i];
        rez += tmp*tmp;
    }

return sqrt(rez);
}



double DELTA(double *VALUE, int *INDEX, double *b, double *c, int deg, int n, int N, int NE, double l, double *y){
    double rez = 0.0;
    double rez_1 = 0.0, rez_2 = 0.0, rez_3 = 0.0;
    double h = 1.0/n;

    int i,j,k;
    double v;

    for(i = 0; i < N; ++i)
        y[i] = 0.0;

    for(k = 0; k < NE; ++k){
        v = VALUE[k];
        i = INDEX[k];
        j = INDEX[k+NE];
        y[i] += v*c[j];
    }

    rez_3 = skal_pr(y, c, N);
    rez_3 *= h*h*l/24.0;


    rez_2 = -2.0 * skal_pr(b, c, N) * h*h*l / 24.0;


    if(deg == 0)
        rez_1 = l/2.0;


    if(deg == 1)
        rez_1 = l*(l*l+l+1)/12.0;

    if(deg == 2)
        rez_1 = l*(6*l*l*l*l+3*l*l*l+3*l*l+3*l+6)/180.0;

    //printf("rez_1 : %lf\n", rez_1);
    //printf("rez_2 : %lf\n", rez_2);
    //printf("rez_3 : %lf\n", rez_3);
    rez = (rez_1 + rez_2 + rez_3);
    //printf("rez : %lf\n", rez);

return sqrt(fabs(rez));
}



double Lanzo_algorithm(double *VALUE, int *INDEX, double *b, int n, int N, int NE, double l, int deg, double *v_0, double *v_1, double *w, double *c_0, double *c_1, double *p_0, double *p_1, double *y){

    double alpha, betta = 0.0, lambda = 0.0, ksi = sqrt(skal_pr(b, b, N)), ny;
    double Norm_0 = sqrt(skal_pr(b, b, N)), epsilon_1 = 1e-4, epsilon_2 = 1e-6, epsilon_3 = 1e-10;

    initial_position_in_LA(b, N, v_0, v_1, p_0, c_0);


    int j = 1;

    while( true ){

        if(Norma_nevazki(VALUE, INDEX, b, c_1, N, NE, y)/Norm_0 <= epsilon_2)
            break;

        else{

            first_operation(VALUE, INDEX, v_0, betta, v_1, w, N, NE, y); //Меняется только w
            alpha  = skal_pr(w, v_1, N);               //Считаем альфу

            if(j > 1){
                lambda = betta / ny;
                ksi *= (lambda * (-1.0));
            }

            ny = alpha - lambda * betta;

            second_operation(p_1, v_1, betta, p_0, ny, N);         //Заполняем p_1
            second_operation(c_1, c_0, ksi*(-1.0), p_1, 1.0, N);   //Заполняем c_1
            second_operation(w, w, alpha, v_1, 1.0, N);            //Заполняем w

            betta  = sqrt(skal_pr(w, w, N));                       //Считаем бетту

            v_0_into_v_1(v_0, v_1, N);                 //V_1 уходит на V_0
            mult_mass(v_1, w, betta, N);               //Меняем V_1 для стед.итерации
            v_0_into_v_1(p_0, p_1, N);                 //p_0 должен стать p_1
            v_0_into_v_1(c_0, c_1, N);                 //c_0 должен стать c_1

            j++;
        }
    }

    /*for(int i = 0; i < n; ++i){
        printf("%.03e ", c_1[i]);
    }
    printf("\n%0.3e ", Norma_nevazki(A, b, c_1, n));*/

    double delt = 0.0;
    delt = DELTA(VALUE, INDEX, b, c_1, deg, n, N, NE, l, y);
    printf("\nDELTA = %.03e ", delt);
    printf("\nKol-vo iter = %d ", j-1);
    printf("\n");


return 0;
}

