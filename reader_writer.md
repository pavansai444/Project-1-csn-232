# Readers-writers-problem-statement:
   multiple readers and writers problem is a classic synchronization problem in operating systems. It arises when multiple processes or threads try to access shared data simultaneously, where some processes only need to read the data, while others need to modify it. The problem is to ensure that concurrent access to the shared data does not result in data inconsistency or corruption.

   Specifically, the problem is to design a mechanism that allows multiple readers to access the shared data simultaneously while ensuring that no writer can modify the data while it is being read. Additionally, the mechanism must ensure that only one writer can modify the data at a time, and that no other readers or writers can access the data while it is being written
   
## Shared data:
   files, database e.t.c
   
## Starve-free-Solution:
 In order to address the issue, we will utilize three semaphores: a mutex, a wrt, and a decider_mutex. The mutex is a binary semaphore that guarantees atomic changing of read_count. The wrt is also a binary semaphore that ensures mutual exclusion of writer processes. The decider_mutex is a binary semaphore that ensures equal priority for both reader and writer processes, preventing starvation.

When the first person attempting to enter is a reader, we will lock both the decider_mutex and wrt semaphores, increment the read_count, and release the decider_mutex. If the next person is also a reader, the decider_mutex will be locked again, and the read_count will be incremented atomically. However, if the next person is a writer, they will have to wait until the read_count becomes zero. Once the read_count is zero, the wrt semaphore will be signaled, allowing the writer to enter using both the decider_mutex and wrt semaphores. As the wrt takes care of mutual exclusion for writers, only one writer can enter the critical section at a time. By utilizing a FiFo queue in semaphore implementation, we ensure a starvation-free solution, and the use of posix threads ensures the progress of processes by running them simultaneously.
