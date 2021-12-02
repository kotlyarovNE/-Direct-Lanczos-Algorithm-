#include <stdio.h>
#include<math.h>
#include <stdlib.h>

int input_A(double *V, int *I, int n, int NE);

int input_b(double *b, int n, int deg, double l);

double Lanzo_algorithm(double *VALUE, int *INDEX, double *b, int n, int N, int NE, double l, int deg, double *v_0, double *v_1, double *w, double *c_0, double *c_1, double *p_0, double *p_1, double *y);

int mult_A_x(double *VALUE, int *INDEX, double *x, int NE, int N, double *y);
