#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "all_functions.h"
double f(double x, double y, int deg){
    if(deg == 0)
        return 1.0;
    if(deg == 1)
        return (x+y);
    else
        return (x*x+y*y+x*y);
}



int input_A(double *V, int *I, int n, int NE){

    int i, j, N = (n+1)*(n+2)/2;
    int z,d;
    int k = 0;

    //start algorithm!

    //a[0][0] = 2;
    V[k] = 2;
    I[k] = 0;
    I[k + NE] = 0;
    k++;

    //a[n][n] = 2;
    V[k] = 2;
    I[k] = n;
    I[k + NE] = n;
    k++;

    //a[0][1] = 1;
    V[k] = 1;
    I[k] = 0;
    I[k + NE] = 1;
    k++;

    //a[n][n-1] = 1;
    V[k] = 1;
    I[k] = n;
    I[k + NE] = n-1;
    k++;

    //a[0][n+1] = 1;
    V[k] = 1;
    I[k] = 0;
    I[k + NE] = n+1;
    k++;

    //a[n][2*n] = 1;
    V[k] = 1;
    I[k] = n;
    I[k + NE] = 2*n;
    k++;

    //a[n+1][0] = 1;
    V[k] = 1;
    I[k] = n+1;
    I[k + NE] = 0;
    k++;

    //a[2*n][n] = 1;
    V[k] = 1;
    I[k] = 2*n;
    I[k + NE] = n;
    k++;

    for(i = 1; i <= n-1; i++){
        //a[i][i] = 6;
        V[k] = 6;
        I[k] = i;
        I[k + NE] = i;
        k++;

        //a[i][i-1] = 1;
        V[k] = 1;
        I[k] = i;
        I[k + NE] = i-1;
        k++;

        //a[i][i+1] = 1;
        V[k] = 1;
        I[k] = i;
        I[k + NE] = i+1;
        k++;

        //a[i][i+n+1] = 2;
        V[k] = 2;
        I[k] = i;
        I[k + NE] = i+n+1;
        k++;

        //a[i][i+n] = 2;
        V[k] = 2;
        I[k] = i;
        I[k + NE] = i+n;
        k++;

        //a[i+n+1][i] = 2;
        V[k] = 2;
        I[k] = i+n+1;
        I[k + NE] = i;
        k++;

        //a[i+n][i] = 2;
        V[k] = 2;
        I[k] = i+n;
        I[k + NE] = i;
        k++;
    }


    for(i = 0; i <= n-2; i++){
        z = n + 1 - (i*(i-2*n-1))/2;
        d = z + n - (i+1);

        //a[z][z] = 6;
        V[k] = 6;
        I[k] = z;
        I[k + NE] = z;
        k++;

        //a[d][d] = 6;
        V[k] = 6;
        I[k] = d;
        I[k + NE] = d;
        k++;

        //a[z][z+1] = 2;
        V[k] = 2;
        I[k] = z;
        I[k + NE] = z+1;
        k++;

        //a[d][d-1] = 2;
        V[k] = 2;
        I[k] = d;
        I[k + NE] = d-1;
        k++;

        //a[z][z+n-i] = 1;
        V[k] = 1;
        I[k] = z;
        I[k + NE] = z+n-i;
        k++;

        //a[d][d+n-1-i] = 1;
        V[k] = 1;
        I[k] = d;
        I[k + NE] = d+n-1-i;
        k++;

        //a[z+n-i][z] = 1;
        V[k] = 1;
        I[k] = z+n-i;
        I[k + NE] = z;
        k++;

        //a[d+n-1-i][d] = 1;
        V[k] = 1;
        I[k] = d+n-1-i;
        I[k + NE] = d;
        k++;



        for(j = z+1; j <= d-1; j++){
            //a[j][j] = 12;
            V[k] = 12;
            I[k] = j;
            I[k + NE] = j;
            k++;

            //a[j][j+1] = 2;
            V[k] = 2;
            I[k] = j;
            I[k + NE] = j+1;
            k++;

            //a[j][j-1] = 2;
            V[k] = 2;
            I[k] = j;
            I[k + NE] = j-1;
            k++;

            //a[j][j+n-i] = 2;
            V[k] = 2;
            I[k] = j;
            I[k + NE] = j+n-i;
            k++;

            //a[j][j+n-i-1] = 2;
            V[k] = 2;
            I[k] = j;
            I[k + NE] = j+n-i-1;
            k++;

            //a[j+n-i][j] = 2;
            V[k] = 2;
            I[k] = j+n-i;
            I[k + NE] = j;
            k++;

            //a[j+n-i-1][j] = 2;
            V[k] = 2;
            I[k] = j+n-i-1;
            I[k + NE] = j;
            k++;
        }


    }

    //a[N-1][N-1] = 2;
    V[k] = 2;
    I[k] = N-1;
    I[k + NE] = N-1;

    //end algorithm!


return 0;
}


int input_b(double *b, int n, int deg, double l){

    int i, j, N = (n+1)*(n+2)/2, z, d;
    double h_y = 1.0/n;
    double h_x = l/n;
    double h = 1.0/n;

    double x_i, y_j;

    //start algorithm:

    b[0] = 2*f(0.0,h/2,deg) + 2*f(l*h/2, 0.0,deg);
    b[n] = 2*f(l-l*h/2, h/2,deg) + 2*f(l - l*h/2, 0.0,deg);

    for( i = 1; i < n; ++i){
        x_i = i * h_x;
        y_j = 0.0;
        b[i] = 4*f(x_i, y_j+h/2,deg) + 2*f(x_i+l*h/2, y_j,deg) + 4*f(x_i-l*h/2, y_j+h/2,deg) + 2*f(x_i-l*h/2, y_j,deg);
    }

    for(i = 0; i <= n-2; ++i){
        z = n+1 - (i*(i-2*n-1))/2;
        d = z + n-1-i;

        x_i = l - (i+1)*h_x;
        y_j = (i+1)*h_y;

        b[z] = 2*f(0.0,y_j+h/2,deg) + 4*f(l*h/2, y_j,deg)+2*f(0.0, y_j-h/2,deg)+4*f(l*h/2, y_j-h/2,deg);
        b[d] = 4*f(x_i,y_j-h/2,deg) + 2*f(x_i+l*h/2, y_j-h/2,deg)+2*f(x_i-l*h/2, y_j+h/2,deg)+4*f(x_i-l*h/2, y_j,deg);
        x_i = 0;

        for(j = z+1; j<= d-1; ++j){
            x_i += h_x;
            b[j] = 4*f(x_i,y_j-h/2,deg) + 4*f(x_i, y_j+h/2,deg)+4*f(x_i-l*h/2, y_j,deg) + 4*f(x_i+l*h/2, y_j,deg) + 4*f(x_i-l*h/2, y_j+h/2,deg) + 4*f(x_i+l*h/2, y_j-h/2,deg);
        }
    }

    b[N-1] = 2*f(0.0, 1 - h/2, deg) + 2*f(l*h/2, 1 - h/2, deg);
    //end algorithm!


return 0;
}


