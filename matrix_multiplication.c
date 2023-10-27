#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
#define M 3
#define K 2
#define N 3
struct v
{
    int row;
    int column;
};

int A[M][K] = {{1, 4}, {2, 5}, {3, 6}};
int B[K][N] = {{8,7,6},{5,4,3}};
int C[M][N]={0};
void *runner(void * param)
{

    int row = ((struct v *)param)->row;
    int column = ((struct v *)param)->column;
    for (int i = 0; i < K;i++)
    {
        C[row][column] += A[row][i] * B[i][column];
    }
}
int main()
{
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_t workers[M * N];
    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < N;j++)
        {
            struct v *data = (struct v *)malloc(sizeof (struct v));
            data->row = i;
            data->column = j;
            pthread_create(&workers[i * N + j], &attr, runner, data);
        }
    }
    for (int i = 0; i < M;i++)
    {
        for (int j = 0; j < N;j++)
        {
            pthread_join(workers[i * N + j], NULL);
        }
    }
    for (int i = 0; i < M;i++)
    {
        for (int j = 0; j < N;j++)
        {
            printf("%d ", C[i][j]);
        }
        printf("\n");
    }
}