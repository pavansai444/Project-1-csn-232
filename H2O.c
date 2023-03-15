#include <stdio.h>
#include <pthread.h>
#include "sem.h"
#include <time.h>
#include <sys/time.h>
#include <sys/types.h>
#define H_atoms 11
#define O_atoms 10
int H2O = 0;
int bar[2];
int H_bar = 0;
struct semaphore H_count;
struct semaphore H_ready;
struct semaphore m;
struct semaphore bond;
void *Hydrogen(void *i)
{
    int h = (int)i;
    printf("H %d has entered\n",h);
    wait(&H_count);
    wait(&m);
    bar[H_bar] = h;
    H_bar++;
    if (H_bar == 2)
    {
        signal(&H_ready);
    }
    signal(&m);
    wait(&bond);
    signal(&H_count);
}
void *Oxygen(void *i)
{   
    int O_id = (int)i;
    printf("O %d has entered\n",O_id);
    wait(&H_ready);
    printf("O atom %d has formed water with H atoms %d and %d\n", O_id, bar[0], bar[1]);
    H_bar = 0;
    signal(&bond);
    signal(&bond);
    wait(&m);
    H2O++;
    signal(&m);
}
int main()
{
    create(&H_count,  2);
    create(&bond,  0);
    create(&m,  1);
    create(&H_ready,  0);
    pthread_t H[H_atoms];
    pthread_t O[O_atoms];
    for (int i = 0; i < H_atoms; i++)
    {
        pthread_create(&H[i], NULL, &Hydrogen, (void *)i);
    }
    for (int i = 0; i < O_atoms; i++)
    {
        pthread_create(&O[i], NULL, &Oxygen, (void *)i);
    }
    usleep(10);
    if (O_atoms - H2O)
    {
        printf("%d O atoms remain unreacted\n", O_atoms - H2O);
    }
    if (H_atoms - 2 * H2O)
    {
        printf("%d H atoms remain unreacted\n", H_atoms - 2 * H2O);
    }

    return 0;
}