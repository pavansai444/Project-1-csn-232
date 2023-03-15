#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>
#include <sys/time.h>
#include <sys/types.h>
#include "sem[1].h"

int boyscount = 0;
int girlscount = 0;
struct semaphore roomkey;
struct semaphore boysem;
struct semaphore girlsem;
int totboys;
int totgirls;
void dress_change(){

    sleep(1);
}

void *boy_func(){
    wait(&roomkey);
     printf("a boy got access to room \n");
    wait(&boysem);

    boyscount++;
       printf("number of boys in dressing room %d\n",boyscount);
    if(boyscount==1){
        wait(&girlsem);

    }
    signal(&boysem);
    signal(&roomkey);

//////////////////////////////////////////

    dress_change();   // critical section

/////////////////////////////////////////
printf("a boy changed his dress  and left the dressing room\n");
wait(&boysem);

boyscount--;

signal(&boysem);

if(boyscount==0){
    signal(&girlsem);  //if all the boys who came before a girl have finished their job then release the girlsemphore
}


}

void *girl_func(){
  
wait(&roomkey);
printf("a girl got access to room \n");
wait(&girlsem);

girlscount++;
 printf("number of girls in dressing room %d\n",girlscount);
if(girlscount==1){
    wait(&boysem);
}
signal(&girlsem);
signal(&roomkey);

//////////////////////////////////////////

    dress_change();   // critical section

/////////////////////////////////////////
printf("a girl changed her dress and left the dressing room\n");
wait(&girlsem);

girlscount--;

signal(&girlsem);

if(girlscount==0){
    signal(&boysem);
}

}

void *create_boy(void *arg){
  pthread_t *by=(pthread_t*)arg;
    sleep(0.01);// to achieve simultaneous creation of boys and girls
    for(int i = 0;i<totboys;i++){
        pthread_create(&by[i],NULL,boy_func,NULL);
    }
 for(int i = 0;i<totboys;i++){
        pthread_join(by[i],NULL);
    }
}
void *create_girl(void *arg){
  pthread_t *gl=(pthread_t*)arg;
    for(int i = 0;i<totgirls;i++){
        pthread_create(&gl[i],NULL,girl_func,NULL);
    }
 for(int i = 0;i<totgirls;i++){
        pthread_join(gl[i],NULL);
    }
}
int main(){

    create(&girlsem,1);
    create(&boysem,1);
    create(&roomkey,1);

    printf("enter no. of boys \n");
    scanf("%d",&totboys);
    
    printf("enter no. of girls \n");
    scanf("%d",&totgirls);
     pthread_t mboy,mgirl;
     pthread_t boy[totboys];
     pthread_t girl[totgirls];
     pthread_create(&mboy,NULL,create_boy,boy);
      pthread_create(&mgirl,NULL,create_girl,girl);
    
    pthread_join(mboy,NULL);
    pthread_join(mgirl,NULL);
    
}
