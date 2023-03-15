# Sleeping barber
## Problem Statement
Few barbers has a store with a barber chair for each barber and a waiting area that can accommodate a specified number of customers. When clients come at the barbershop, they either discover the barber sleeping on his chair or find a seat in the waiting area. The client wakes the barber up if he is sleeping and then sits in the chair. The customer leaves if there are no seats available in the waiting area.

As the barbers are cutting hair, costumers must wait in the waiting area until a seat opens up. The barbers checks the waiting area for customers after finishing a customer's hair cut. He trims the hair of the next person in line if there are custmers waiting. He falls asleep in his chair when no customers are waiting for him.


The sleeping barber problem's difficulty is to make sure that both the barber and the customers can utilize the shared resources (i.e., the barber chair and waiting room) securely and without problems, while preventing starvation or deadlock. Semaphores are frequently used as part of the solution to control access to shared resources.
## Global variables
``` cpp
int freeseats;
int chairs;
int totbarbers;
int totcustomers;
int nonservedcust= 0;
int count = 0;
 ```
## Semaphores
accessSeats is semaphore used for the mutual exclusion of the variable freeseats and with this semaphore either barber or customer can access the waiting room.
barb this semaphore is for mainitaining mutual excusion between barbers for accessing waiting room
readycustomer is a counting semaphore to count the number of customers waiting in waiting room which when signalled wakes the barbers.
readybarber is a semaphore used to place waiting customers in a queue so that the first customer to come is the first customer to be served.

## Customer code
``` cpp
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
```
### Logic
Firstly, function waits for the accessSeats semaphore and then holds it and access freeseats variable. If the value of freeseats is greater than or equal to 1 that means there is a vacancy in waiting hall and customer can wait there and freeseats is decremented by 1 and then signal readycustomer indicating that a new customer is waiting and releases accessSeats semaphore and it waits for the readybarber semaphore and enters the queue associated with it. Or if the freeseats value is equal to 0 which means there is no vacancy in waiting room so the customer leaves and comes after a random time and recalls the customer function.

## Barber code
``` cpp
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
```
### Logic
Firstly, the barber should check for waiting customers in waiting hall. Only one barber should check at a time which is ensured by the barb semaphore. Then barber picks a waiting customer or goes to sleep until a customer arrives. After barber picks a customer there will be a extra free seat which should by updated by incremented freeseats variable by 1 using the accessSeats semaphore and readybarber is signalled which tells customer to be served from the order as in queue. Barber serves the customer. Count should be incremented by 1 because a customer is served and this is done using forcount semaphore. Finally, if count is equal to total customers, we can break while loop.

## Main Function Code
``` cpp
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
```
### Logic
Initially readybarber is initialized to 0 because no customer is in barber chair so barbers cannot serve customers, readycustomers is initialized to 0 because there aren't any customers waiting before hand, accessSeats is set to 1 in order to access freeseats variable, barb is set to 1 so that barber can check for waiting customers and forcount is also set to 1 because we need to increment count after serving customers.gocustomer is initaialized to 0 because it is necessary for inserting the customers in queue.

Number of barbers, customers and chairs are taken as input respectively. pthreads are created for each barber and for each customer and they are initialized. In this case we are assuming that customers arrive in the interval of 0.9999s 

## Prevention of Starvation
Starvation of the customers is prevented by semaphore gocustomer as it has a queue containing waiting customer in the order of their arrival they will be served in the same order, this ensures that their is no starvation of cusotmers what-so-ever.

Starvation of the barbers is prevented by semaphore barb as it has a queue of barbers waiting to enter the waiting room, barb has queue these barbers in a queue and releases them in the same order, this ensures that their is no starvation of barbers what-so-ever.
