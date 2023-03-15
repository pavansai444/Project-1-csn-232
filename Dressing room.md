# Dressing-room-problem-statement:
  The dressing room synchronization problem is a classic synchronization problem in operating systems. It is used to model situations where multiple threads need to     access a shared resource in a mutually exclusive manner.
  The problem is often formulated as follows:
1. There is a dressing room in a mall.
2. It is a common dressing room for both men and women.
3. Both men and women cannot use it simultaneously.
4. Multiple men can use it simultaneously.
5. Multiple women can use it simultaneously.
## Shared data:
  Common dressing room
## Starve free solution:
  To solve the problem of managing the entry of boys and girls into a dressing room, semaphores are used. Two variables, girlscount and boyscount, are created to keep track of how many boys or girls are present in the dressing room. Three semaphores are used:

1)The semaphore roomkey ensures mutual exclusion between men and women.
2)The semaphore girlsem updates the girlscount variable atomically.
3)The semaphore boysem updates the boyscount variable atomically.
To allow entry into the dressing room, the roomkey semaphore is used to allow either boys or girls. Once a person enters the dressing room, the other gender's entry is locked using girlsem/boysem and roomkey semaphore is signaled before entering the dressing room and made available for the next person. If the next person is of the same gender, they are allowed to enter the dressing room, and their gender count is incremented atomically using girlsem/boysem. However, if the opposite gender enters, they must wait until the present gender count becomes zero. During this process, the gender count is decremented atomically by using girlsem/boysem semaphore. When the gender count becomes zero, the opposite gender semaphore is released. Since we are using a FIFO queue in the wait and signal functions, this ensures a starvation-free solution. The roomkey semaphore ensures mutual exclusion, and since we are using pthreads that run concurrently, the progress of processes is maintained.

For instance, if a boy enters the dressing room first, girsem is locked, and roomkey semaphore is released, and boyscount is incremented. If another boy tries to enter next, they can enter using the roomkey semaphore, and boyscount will be incremented. However, if a girl tries to enter next, she must wait until boyscount becomes zero. Once boyscount becomes zero, both the roomkey semaphore and girlsem semaphore are signaled, and she will be able to enter the dressing room.
