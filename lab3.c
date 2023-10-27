#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
int minimum = __INT32_MAX__;
int maximum = -__INT32_MAX__ - 1;
int average = 0;
int numbercount = 0;
void *claverage(char *param[]);
void *clminimum(char *param[]);
void *clmaximum(char *param[]);
int main(int argc, char *argv[])
{
    pthread_t workers[3];
    pthread_attr_t attr;
    numbercount = argc - 1;

    pthread_attr_init(&attr);

    pthread_create(&workers[0], &attr, claverage, argv);
    pthread_create(&workers[1], &attr, clminimum, argv);
    pthread_create(&workers[2], &attr, clmaximum, argv);
    for (int i = 0; i < 3; i++)
    {
        pthread_join(workers[i], NULL);
    }
    printf("The average value is %d\n", average);
    printf("The minumum value is %d\n", minimum);
    printf("The maximum value is %d\n", maximum);
    return 0;
}
void *claverage(char *param[])
{
    for (int i = 1; i <= numbercount; i++)
    {
        average += atoi(param[i]);
    }
    average = average / numbercount;
}
void *clminimum(char *param[])
{
    for (int i = 1; i <= numbercount; i++)
    {
        int k = atoi(param[i]);
        if (k < minimum)
        {
            minimum = k;
        }
    }
}
void *clmaximum(char *param[])
{
    for (int i = 1; i <= numbercount; i++)
    {
        int k = atoi(param[i]);
        if (k > maximum)
        {
            maximum = k;
        }
    }
}
