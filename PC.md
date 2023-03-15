# Producer-Consumer problem 
The Producer-Consumer problem is a classical multi process synchronization problem,There are more than one Producer in this, Producer is producing some items, whereas there is more than one Consumers that is consuming the items produced by the Producer. The same memory buffer is shared by both producers and consumers.The producer should produce data only when the buffer is not full and the data can only be consumed by Consumer when buffer is not empty.Producer and Consumer are not allowed to access the same memory buffer at same time. 

#### We have three different types of buffer 
1.Bounded 
2.Cyclic  
3.Infinite

# Starve free and Deadlock free solution : 
### Bounded buffer :
we have used 5 semaphores namely full,empty,m,p_sync,c_sync.Where m,p_sync,c_sync are binary semaphores.Initially full is intialised to 0,empty to buffersize,m, p_sync, c_sync to 1 Full semaphore shows out of n slots in buffer how many slots were filled ,empty semaphore shows how many slots are free to produce , m is the mutex ,p_sync and c_sync are used not to allow more than one producer or consumer to access empty and full semaphores respectively.
Our code allows multiple producers produce without any clash by using mutex semaphore it won't allow multiple producers change the index (named prod used to identify where to produce) and also allows multiple consumers to consume.mutex locks while producer/consumer changing prod/cons and releases after completing changes.When a consumer wants to consume while full is 0 it is locked and released after a producer produces and increments full as well as when producer is trying to produce while empty is 0 it is locked and released when empty increments by consumer.\
### Cyclic buffer :






