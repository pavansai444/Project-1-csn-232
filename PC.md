# Producer-Consumer problem 
The Producer-Consumer problem is a classical multi process synchronization problem,There are more than one Producer in this, Producer is producing some items, whereas there is more than one Consumers that is consuming the items produced by the Producer. The same memory buffer is shared by both producers and consumers.The producer should produce data only when the buffer is not full and the data can only be consumed by Consumer when buffer is not empty.Producer and Consumer are not allowed to access the same memory buffer at same time. 

#### We have three different types of buffer 
1.Bounded   
2.Cyclic  
3.Infinite

# Starve free and Deadlock free solution : 
### Bounded buffer :
There is a buffer of n slots and each slot is capable of storing one unit of data.

we have used 5 semaphores namely full,empty,m,p_sync,c_sync.Where m,p_sync,c_sync are binary semaphores.Initially full is intialised to 0,empty to buffersize,m, p_sync, c_sync to 1 Full semaphore shows out of n slots in buffer how many slots were filled ,empty semaphore shows how many slots are free to produce , m is the mutex ,p_sync and c_sync are used not to allow more than one producer or consumer to access empty and full semaphores respectively.

Our code allows multiple producers produce without any clash by using mutex semaphore it won't allow multiple producers change the index (named prod used to identify where to produce) and also allows multiple consumers to consume.mutex locks while producer/consumer changing prod/cons and releases after completing changes.When a consumer wants to consume while full is 0 it is locked and released after a producer produces and increments full as well as when producer is trying to produce while empty is 0 producer is locked forever.

#### producer implementation:
void * producer(void* pn){
    int p=(int)pn;
    
    while(1){
        sem_wait(&p_sync);
        if(t>0){
            t--;
            sem_post(&p_sync);
            sem_wait(&empty);
            sem_wait(&m);
            buffer[prod]=10-prod;
            printf("producer %d produced %d in %d\n",p,10-prod,prod);
            prod++;
            sem_post(&m);
            sem_post(&full);
        }
        else{
            sem_post(&p_sync);
            break;
        }
    }   
}

#### consumer implementation:
void* consumer(void * cn){
    int c=(int)cn;
    while(1){
        sem_wait(&c_sync);
        if(e>0){
            e--;
            sem_post(&c_sync);
            sem_wait(&full);
            sem_wait(&m);
            printf("consumer %d consumed %d from %d\n",c,buffer[cons],cons);
            cons++;
            sem_post(&m);
            sem_post(&empty);
         }
         else{
            sem_post(&c_sync);
            break;
         }
    }
}

### Cyclic buffer :
It is a data structure that uses a single, fixed - size buffer as if it were connected end to end.

we have used the same semaphores as in the case of bounded buffer the only difference is that when empty became 0 and producer tries to produce it waits until the consumer consumes and signals empty and after that produces starts produce from the beginning for this we used %buffersize indexing.It can be used in the cases where no.of productions is greater than buffer size.

#### producer implementation :
void * producer(void* pn){
    int p=(int)pn;
    
    while(1){
        sem_wait(&p_sync);
        if(t>0){
            t--;
            sem_post(&p_sync);
            sem_wait(&empty);
            sem_wait(&m);
            buffer[prod]=10-prod;
            printf("producer %d produced %d in %d\n",p,10-prod,prod);
            prod=(prod+1)%10;
            sem_post(&m);
            sem_post(&full);
        }
        else{
            sem_post(&p_sync);
            break;
        }
    }   
}
#### consumer implementation :
void* consumer(void * cn){
    int c=(int)cn;
    while(1){
        sem_wait(&c_sync);
        if(e>0){
            e--;
            sem_post(&c_sync);
            sem_wait(&full);
            sem_wait(&m);
            printf("consumer %d consumed %d from %d\n",c,buffer[cons],cons);
            cons=(cons+1)%10;
            sem_post(&m);
            sem_post(&empty);
         }
         else{
            sem_post(&c_sync);
            break;
         }
    }
}
### Infinite buffer :
In this case we used single semaphore uncomsumed instead of empty and full semaphores.

Unlike bounded and cyclic buffer we donot have to wait for consumer to consume while buffer is full beacuse we have buffer with variable size we can produce any no.of items without waiting for customer . unconsumed is used to determine whether consumer can consume means whether the buffer is empty or not.If the buffer is empty(unconcumed is 0) consumer is locked until producer produces an item(increments unconsumed ). 

#### producer implementation
void * producer(void* pn){
    int p=(int)pn;
    
    while(1){
        sem_wait(&p_sync);
        if(t>0){
            t--;
            sem_post(&p_sync);
            sem_wait(&m);
            int pro=0;
            insert(&inf_buff,pro);
            printf("producer %d produced %d\n",p,0);
            sem_post(&m);
            sem_post(&unconsumed);
        }
        else{
            sem_post(&p_sync);
            break;
        }
    }   
}
#### consumer implementation
void* consumer(void * cn){
    int c=(int)cn;
    while(1){
        sem_wait(&c_sync);
        if(e>0){
            e--;
            sem_post(&c_sync);
            sem_wait(&unconsumed);
            sem_wait(&m);
            printf("consumer %d consumed %d\n",c,inf_buff->data);
            inf_buff=inf_buff->next;
            sem_post(&m);
         }
         else{
            sem_post(&c_sync);
            break;
         }
    }
}
