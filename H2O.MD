# Building H2O
## Problem statement
There are two kinds of threads, oxygen and hydrogen. In order to assemble
these threads into water molecules, we have to create a barrier that makes each
thread wait until a complete molecule is ready to proceed.
As each thread passes the barrier, it should invoke bond. You must guarantee
that all the threads from one molecule invoke bond before any of the threads
from the next molecule do.
In other words:
• If an oxygen thread arrives it has to wait for the hydrogen barrier to full.
• If a hydrogen thread arrives at the barrier when no other threads are
present, it has to wait for an oxygen thread and another hydrogen thread.
<img width="469" alt="image" src="https://user-images.githubusercontent.com/116514626/225289706-1b959851-c435-41c2-8a6f-e577ff62f20c.png">

## Solution
We have implemented the barrier using a array of size 2 which stored hydrogen atoms if the buffer is full the new incoming hydrogens must wait on H_count semaphore
which is intialized to zero once the barrier is full H_ready semaphore is signaled. Oxygen threads wait for this H_ready semaphore(wait for the barrier to be full).
Once all three atoms are ready they form water.We have printed which hydrogen atoms and oxygen atom formed water and also if some element is a limiting reagent,it is
left unreacted and hence after all the execution we have printed number of unreacted atoms at the end of the reation.

## Semaphores
```c
struct semaphore H_count;
struct semaphore H_ready;
struct semaphore m;
struct semaphore bond;
```
we have used four semaphores H_count,H_ready,m,bond which are used for hydrogen threads to wait for one more oxygen and hydrogen and oxygen thread to wait for two more
hydrogens

## Global variables
```c
int H2O = 0;
int bar[2];
int H_bar = 0;
```
H2O is the count of number of water molecules stored, bar is the barrier array, H_bar is the number of H atoms at the barrier which is also used as the index of bar
array because it can have only 3 values 0,1,2 and before 2nd atom entering the barrier it has only two values 0,1.

Hydrgen and oxygen thread run the following functions

## Hydrogen Implementation
```c
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
```

## Oxygen Implementation 
```c
printf("O %d has entered\n",O_id);
    wait(&H_ready);
    printf("O atom %d has formed water with H atoms %d and %d\n", O_id, bar[0], bar[1]);
    H_bar = 0;
    signal(&bond);
    signal(&bond);
    wait(&m);
    H2O++;
    signal(&m);
```


