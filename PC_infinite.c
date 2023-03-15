#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include<stdlib.h>
#define n_pros 10
#define n_cons 10
struct Node {
    int data;
    struct Node* next;
};
void insert (struct Node **head, int data){
  struct Node *newNode = (struct Node *) malloc (sizeof (struct Node));
  newNode->data = data;
  // since this will be the last node so it will point to NULL
  newNode->next = NULL;

  // if the Linked List is empty this is the first node being entered
  if (*head == NULL)
    {
      *head = newNode;
      return;
    }

  // create another variable to traverse the LL
  // *head should not be used as we do not want to change head
  struct Node *temp = *head;

  // traverse to the last node of Linked List
  while (temp->next != NULL)
    temp = temp->next;

  // assign last node's next to this newNode
  temp->next = newNode;
}
struct Node* inf_buff=NULL;
sem_t unconsumed;
sem_t m;
sem_t p_sync;
sem_t c_sync;
int t=10;
int e=5;
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

int main() {  
    sem_init(&unconsumed,0,0);
    sem_init(&m,0,1);
    sem_init(&p_sync,0,1);
    sem_init(&c_sync,0,1);
    pthread_t producer_thread[n_pros];
    pthread_t consumer_thread[n_cons];
    for(int i=0;i<n_pros;i++){
        pthread_create(&producer_thread[i],NULL,&producer,(void*)i);
    }
    for(int i=0;i<n_cons;i++){
        pthread_create(&consumer_thread[i],NULL,&consumer,(void*)i);
    }
    for(int i=0;i<n_pros;i++){
         pthread_join(producer_thread[i],NULL);
    }
    for(int i=0;i<n_cons;i++){
        pthread_join(consumer_thread[i],NULL);
        
    }

    
    
    return 0;                   
}    
