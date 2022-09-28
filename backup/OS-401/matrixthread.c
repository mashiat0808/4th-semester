include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h>
#define N 3
pthread_mutex_t mxlck = PTHREAD_MUTEX_INITIALIZER;
void *multiply(void *);
int matrix1[N][N] = {
    {1, 2, 3},
    {4, 5, 6},
    {7, 8, 9}};
int matrix2[N][N] = {
    {1, 2, 3},
    {4, 5, 6},
    {7, 8, 9}};
int resMatrix[N][N];

int numThreads = N;
int row = 0;
void initializeMatrix()
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            matrix1[i][j] = 1;
            if (i == j)
            {
                matrix2[i][j] = 1;
            }
            else
                matrix2[i][j] = 0;
        }
    }
}

void multiplyRow(int row)
{
    for (int col = 0; col < N; col++)
    {
        resMatrix[row][col] = 0;
        for (int k = 0; k < N; k++)
            resMatrix[row][col] += matrix1[row][k] * matrix2[k][col];
    }
}
void *multiply(void *rowNum)
{

   
    pthread_mutex_lock(&mxlck);
    printf("Ami ki gun dibo? %d\n", row);
    multiplyRow(row);
    row++;
    pthread_mutex_unlock(&mxlck);
}
void printMatrix()
{
    
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            printf("%d\t", resMatrix[i][j]);
        }
        printf("\n");
    }
}
int main()
{
    
    pthread_t threads[N];
    int *rowNum = (int *)malloc(sizeof(int));
   
    for (int i = 0; i < N; i++)
    {
        *rowNum = i;
        pthread_create(&threads[i], NULL, multiply, (void *)rowNum);
    }
    for (int i = 0; i < N; ++i)
    {
        pthread_join(threads[i], NULL);
       
    }
    return 0;
}