# Readers-writers-problem-statement:
   multiple readers and writers problem is a classic synchronization problem in operating systems. It arises when multiple processes or threads try to access shared data simultaneously, where some processes only need to read the data, while others need to modify it. The problem is to ensure that concurrent access to the shared data does not result in data inconsistency or corruption.

   Specifically, the problem is to design a mechanism that allows multiple readers to access the shared data simultaneously while ensuring that no writer can modify the data while it is being read. Additionally, the mechanism must ensure that only one writer can modify the data at a time, and that no other readers or writers can access the data while it is being written
   
<img width="500" alt="image" src="https://user-images.githubusercontent.com/116514653/225282994-0f924ad5-5db4-4c5f-99d2-d9dda34aa861.png">



   
## Shared data:
   files, database e.t.c
   
## Starve-free-Solution:
 In order to address the issue, we will utilize three semaphores: a mutex, a wrt, and a decider_mutex. The mutex is a binary semaphore that guarantees atomic changing of read_count. The wrt is also a binary semaphore that ensures mutual exclusion of writer processes. The decider_mutex is a binary semaphore that ensures equal priority for both reader and writer processes, preventing starvation.

When the first person attempting to enter is a reader, we will lock both the decider_mutex and wrt semaphores, increment the read_count, and release the decider_mutex. If the next person is also a reader, the decider_mutex will be locked again, and the read_count will be incremented atomically. However, if the next person is a writer, they will have to wait until the read_count becomes zero. Once the read_count is zero, the wrt semaphore will be signaled, allowing the writer to enter using both the decider_mutex and wrt semaphores. As the wrt takes care of mutual exclusion for writers, only one writer can enter the critical section at a time. By utilizing a FiFo queue in semaphore implementation, we ensure a starvation-free solution, and the use of posix threads ensures the progress of processes by running them simultaneously.
## Writers code:
    void* write(void* i){
    int w=(int)i;
    
    wait(&decider_mutex);
    printf("writer  %d entered\n",w);
    waitwrt=1;
    wait(&mutex);
    if(in_read_count){
        signal(&mutex);
        wait(&wrt);
    }
    else{
        signal(&mutex);
    }
    
     /*write*/
     usleep(1);
     wait(&mutex);
     printf("written by %d            # number of readers in cs %d\n",w,in_read_count);
     signal(&mutex);
     waitwrt=0;
    signal(&decider_mutex);
    
   }
## Readers code:
    void * read(void* i){
    int r=(int)i;
    
    
    wait(&decider_mutex);
    printf("reader %d started\n",r);
    wait(&mutex);
     in_read_count++;
    signal(&mutex);
    signal(&decider_mutex);
    /*read*/
    usleep(1);
    printf("read by %d               # number of readers in cs %d\n",r,in_read_count);
    wait(&mutex);
     in_read_count--;
     if((in_read_count==0)&&(waitwrt==1)){
        signal(&wrt);
     }
    signal(&mutex);
   
    }
