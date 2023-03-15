# Dressing-room-problem-statement:
  The dressing room synchronization problem is a classic synchronization problem in operating systems. It is used to model situations where multiple threads need to     access a shared resource in a mutually exclusive manner.
  The problem is often formulated as follows:
1. There is a dressing room in a mall.
2. It is a common dressing room for both men and women.
3. Both men and women cannot use it simultaneously.
4. Multiple men can use it simultaneously.
5. Multiple women can use it simultaneously.
<img width="300" alt="image" src="https://user-images.githubusercontent.com/116514653/225326241-1bc63d2e-3309-4870-b4c5-4ddc163f70ca.png">

## Shared data:
  Common dressing room
## Semaphores
 1. roomkey      //room key semaphore is common for both,whoever first acquires this can enter into waiting room.
 2. boysem       //this sem is for maintaining mutual exclusion between boys for increasing boysem atomically.
 3. girlsem     m// this sem is for maintaining mutual exclusion between girls for increasing girlsem atomically.
## Starve free solution:
  To solve the problem of managing the entry of boys and girls into a dressing room, semaphores are used. Two variables, girlscount and boyscount, are created to keep track of how many boys or girls are present in the dressing room. Three semaphores are used:

1)The semaphore roomkey ensures mutual exclusion between men and women.
2)The semaphore girlsem updates the girlscount variable atomically.
3)The semaphore boysem updates the boyscount variable atomically.
To allow entry into the dressing room, the roomkey semaphore is used to allow either boys or girls. Once a person enters the dressing room, the other gender's entry is locked using girlsem/boysem and roomkey semaphore is signaled before entering the dressing room and made available for the next person. If the next person is of the same gender, they are allowed to enter the dressing room, and their gender count is incremented atomically using girlsem/boysem. However, if the opposite gender enters, they must wait until the present gender count becomes zero. During this process, the gender count is decremented atomically by using girlsem/boysem semaphore. When the gender count becomes zero, the opposite gender semaphore is released. Since we are using a FIFO queue in the wait and signal functions, this ensures a starvation-free solution. The roomkey semaphore ensures mutual exclusion, and since we are using pthreads that run concurrently, the progress of processes is maintained.

For instance, if a boy enters the dressing room first, girsem is locked, and roomkey semaphore is released, and boyscount is incremented. If another boy tries to enter next, they can enter using the roomkey semaphore, and boyscount will be incremented. However, if a girl tries to enter next, she must wait until boyscount becomes zero. Once boyscount becomes zero, both the roomkey semaphore and girlsem semaphore are signaled, and she will be able to enter the dressing room.
## boys_code:
    void *boy_func(){
    wait(&roomkey); //room key semaphore is common for both 
                     //whoever first acquires this can enter into waiting room
     printf("a boy[pid = %lu] got access to room \n",pthread_self());
    wait(&boysem); 
    boyscount++;
       printf("number of boys in dressing room %d\n",boyscount);
    if(boyscount==1){
        wait(&girlsem); //if there are atleast one boy in dressingroom then lock the girl semaphore
    }
    signal(&boysem);
    signal(&roomkey);  //release the roomkey when the boy enters into dressing room

      //////////////////////////////////////////

        dress_change();   // critical section

     /////////////////////////////////////////
    printf("a boy[pid = %lu] changed his dress  and left the dressing room\n",pthread_self());
    wait(&boysem);

    boyscount--;

    signal(&boysem);

    if(boyscount==0){
         signal(&girlsem);  //if all the boys who came before a girl have finished their job then release the girlsemphore
                    }


            }
            
 ## girls_code:
    void *girl_func(){
  
    wait(&roomkey);
    printf("a girl[pid = %lu] got access to room \n",pthread_self());
    wait(&girlsem);

    girlscount++;
    printf("number of girls in dressing room %d\n",girlscount);
    if(girlscount==1){
    wait(&boysem); //if there are atleast one girl in dressingroom then lock the boy semaphore
    }
    signal(&girlsem);
    signal(&roomkey);

     //////////////////////////////////////////

         dress_change();   // critical section

     /////////////////////////////////////////
      printf("a girl[pid = %lu] changed her dress and left the dressing room\n",pthread_self());
      wait(&girlsem);

      girlscount--;

      signal(&girlsem);

      if(girlscount==0){
           signal(&boysem);  //if all the girls who came before a boy have finished their job then release the boysemphore
       }

       }

