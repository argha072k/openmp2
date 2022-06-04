
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <sys/time.h>


#define N 10

int A[N][N];
int B[N][N];
int C[N][N];

int main() 
{
    int i,j,k;
    double t1,t2;
    
    for (i= 0; i< N; i++)
        for (j= 0; j< N; j++)
	{
            A[i][j] = 2;
            B[i][j] = 3;
	}
 
    t1=omp_get_wtime();
    #pragma omp parallel for private(i,j,k) shared(A,B,C) num_threads(4)
    for (i = 0; i < N; ++i) {
        for (j = 0; j < N; ++j) {
            for (k = 0; k < N; ++k) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    t2=omp_get_wtime();

    
    for (i= 0; i< N; i++)
    {
        for (j= 0; j< N; j++)
        {
            printf("%d\t",C[i][j]);
        }
        printf("\n");
    }
    printf("expected time is %g\n",t2-t1);
}