/*******************************************************************************
*   Copyright(C) 2012 Intel Corporation. All Rights Reserved.
*   
*   The source code, information  and  material ("Material") contained herein is
*   owned  by Intel Corporation or its suppliers or licensors, and title to such
*   Material remains  with Intel Corporation  or its suppliers or licensors. The
*   Material  contains proprietary information  of  Intel or  its  suppliers and
*   licensors. The  Material is protected by worldwide copyright laws and treaty
*   provisions. No  part  of  the  Material  may  be  used,  copied, reproduced,
*   modified, published, uploaded, posted, transmitted, distributed or disclosed
*   in any way  without Intel's  prior  express written  permission. No  license
*   under  any patent, copyright  or  other intellectual property rights  in the
*   Material  is  granted  to  or  conferred  upon  you,  either  expressly,  by
*   implication, inducement,  estoppel or  otherwise.  Any  license  under  such
*   intellectual  property  rights must  be express  and  approved  by  Intel in
*   writing.
*   
*   *Third Party trademarks are the property of their respective owners.
*   
*   Unless otherwise  agreed  by Intel  in writing, you may not remove  or alter
*   this  notice or  any other notice embedded  in Materials by Intel or Intel's
*   suppliers or licensors in any way.
*
********************************************************************************/

/*******************************************************************************
*   This example measures performance of computing the real matrix product 
*   C=alpha*A*B+beta*C using a triple nested loop, where A, B, and C are 
*   matrices and alpha and beta are double precision scalars. 
*
*   In this simple example, practices such as memory management, data alignment, 
*   and I/O that are necessary for good programming style and high MKL 
*   performance are omitted to improve readability.
********************************************************************************/

#define min(x,y) (((x) < (y)) ? (x) : (y))

#include <stdio.h>
#include <stdlib.h>
#include "mkl.h"

/* Consider adjusting LOOP_COUNT based on the performance of your computer */
/* to make sure that total run time is at least 1 second */
#define LOOP_COUNT 10

int main()
{
    double *A, *B, *C;
    int m, n, k, i, j, l, r;
    double alpha, beta;
    double sum;
    double s_initial, s_elapsed;

    printf ("\n This example measures performance of rcomputing the real matrix product \n"
            " C=alpha*A*B+beta*C using a triple nested loop, where A, B, and C are \n"
            " matrices and alpha and beta are double precision scalars \n\n");

    m = 2000, k = 200, n = 1000;
    printf (" Initializing data for matrix multiplication C=A*B for matrix \n"
            " A(%ix%i) and matrix B(%ix%i)\n\n", m, k, k, n);
    alpha = 1.0; beta = 0.0;
    
    printf (" Allocating memory for matrices aligned on 64-byte boundary for better \n"
            " performance \n\n");
    A = (double *)mkl_malloc( m*k*sizeof( double ), 64 );
    B = (double *)mkl_malloc( k*n*sizeof( double ), 64 );
    C = (double *)mkl_malloc( m*n*sizeof( double ), 64 );
    if (A == NULL || B == NULL || C == NULL) {
        printf( "\n ERROR: Can't allocate memory for matrices. Aborting... \n\n");
        mkl_free(A);
        mkl_free(B);
        mkl_free(C);
        return 1;
    }

    printf (" Intializing matrix data \n\n");
    for (i = 0; i < (m*k); i++) {
        A[i] = (double)(i+1);
    }

    for (i = 0; i < (k*n); i++) {
        B[i] = (double)(-i-1);
    }

    for (i = 0; i < (m*n); i++) {
        C[i] = 0.0;
    }

    printf (" Making the first run of matrix product using triple nested loop\n"
            " to get stable run time measurements \n\n");
    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++) {
            sum = 0.0;
            for (l = 0; l < k; l++)
                sum += A[k*i+l] * B[n*l+j];
            C[n*i+j] = sum;
        }
    }

    printf (" Measuring performance of matrix product using triple nested loop \n\n");
    s_initial = dsecnd();
    for (r = 0; r < LOOP_COUNT; r++) {
        for (i = 0; i < m; i++) {
            for (j = 0; j < n; j++) {
                sum = 0.0;
                for (l = 0; l < k; l++)
                    sum += A[k*i+l] * B[n*l+j];
                C[n*i+j] = sum;
            }
        }
    }
    s_elapsed = (dsecnd() - s_initial) / LOOP_COUNT;
    
    printf (" == Matrix multiplication using triple nested loop completed == \n"
            " == at %.5f milliseconds == \n\n", (s_elapsed * 1000));
    
    printf (" Deallocating memory \n\n");
    mkl_free(A);
    mkl_free(B);
    mkl_free(C);
    
    if (s_elapsed < 0.9/LOOP_COUNT) {
        s_elapsed=1.0/LOOP_COUNT/s_elapsed;
        i=(int)(s_elapsed*LOOP_COUNT)+1;
        printf(" It is highly recommended to define LOOP_COUNT for this example on your \n"
               " computer as %i to have total execution time about 1 second for reliability \n"
               " of measurements\n\n", i);
    }
    
    printf (" Example completed. \n\n");
    return 0;
}
