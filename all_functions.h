#include <stdio.h>
#include<math.h>
#include <stdlib.h>

double input_matrix_A_b(double *A, double *b, int n, int deg);

double print_matrix_A_b(double *A, double *b, int n);


double Lanzo_algorithm(double *A, double *b, int n, double *v_0, double *v_1, double *w, double *c_0, double *c_1, double *p_0, double *p_1, int deg, double h);


