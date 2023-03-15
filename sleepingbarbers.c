#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "sem.h"

int freeseats;
struct semaphore readybarber; 
struct semaphore readycustomer;
struct semaphore accessSeats;  //with this semaphore either barber or customer can access the waiting room
struct semaphore barb;
struct semaphore forcount;
int chairs;
int totbarbers;
int totcustomers;
int nonservedcust= 0;
int count = 0;

void serve_customer(){

sleep(0.01);

}
void *barber_func(){


while(1){
 wait(&barb);  //this semaphore is for mainitaining mutual excusion between barbers for accessing waiting room
 wait(&readycustomer); //this semaphore is released whenever a customer enters into a waiting room
 
wait(&accessSeats);   
 
 printf("barber[pid = %lu] got access to waiting room and he took the customer to barber seat  \n",pthread_self());
 freeseats++;        //barber access the waiting room and get the customer to barber seat.
 signal(&barb);      
 signal(&accessSeats);
  
 signal(&readybarber);   //this semaphore tells barber is  ready to do hair cut.

    serve_customer();//critical section
 wait(&forcount);
 count++;
 signal(&forcount);
 printf("barber[pid = %lu] provided service to a customer.\n", pthread_self());
if(count == (totcustomers)){
    break;
}
}
}

void *customer_func(void *cn){
    int c=(int)cn;

wait(&accessSeats);
if(freeseats>=1){
    freeseats--;
    
    printf("a customer  %d is entered and number of customers waiting in room : %d\n",c,(chairs - freeseats));
    signal(&readycustomer); //customer is set to ready

    signal(&accessSeats);
    
    wait(&readybarber);

    //critical section

}

else{
 signal(&accessSeats);
 printf("a customer %d left the barber shop as waiting room is full \n",c,pthread_self());
 sleep(rand()%3+1);
 customer_func(cn);  //customer again returns after random time..

}

}


int main(){

create(&readybarber, 0);
create(&readycustomer, 0);
create(&accessSeats, 1);
create(&barb,1);
create(&forcount,1);
printf("no. of barbers: \n");
scanf("%d",&totbarbers);
printf("no. of customers: \n");
scanf("%d",&totcustomers);
printf("no. of chairs : \n");
scanf("%d",&chairs);

freeseats = chairs;
pthread_t bar[totbarbers];
for(int i = 0;i<totbarbers;i++){
    
    pthread_create(&bar[i],NULL,&barber_func,NULL);
}
pthread_t cus[totcustomers];
for(int i = 0;i<totcustomers;i++){
    
    pthread_create(&cus[i],NULL,&customer_func,(void*)i);
  
   sleep(0.998); //for every 0.998s a customer arrives
}



for(int i = 0;i<totcustomers;i++){
    
    pthread_join(cus[i],NULL);
    
}



}
