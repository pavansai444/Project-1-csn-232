# Starve-free-and-Deadlock-free-Dining-Philosophers-problem
This repo contains an implementation to solve the Dining Philosophers Problem using C without Starvation and Deadlock.
![alt dining philosophers problem](https://img.youtube.com/vi/kwxrt-LWryQ/0.jpg)
# The Problem
The Dining philosophers is a synchronization problem which is used to evaluate situations where there is a need of allocating multiple resources to multiple processes. The problem is:

Consider there are **five philosophers** sitting around a circular dining table. The dining table has **five forks** and a bowl of food in the middle.
At any instant, a philosopher is either **eating** or **thinking**. When a philosopher wants to eat, he uses *two forks* - one from their left and one from their right. When a philosopher wants to think, he keeps down both forks at their original place.
Eating is not limited by the remaining amounts of food;
# Solution
The classical solution of this problem is using semaphores and the pseudocode for philosopher i looks like below:
```cpp
semaphore chopsticks[n] //where n is the number of philosophers 
```
```cpp
wait(chopsticks[i]);
wait(chopsticks[(i+1)%5];
/*eat*/
signal(chopsticks[(i+1)%5]);
signal(chopsticks[i]);
```
We see that this solution can result in deadlock if all the philosophers pickup their left forks. Also starving of a philosopher to death is possible if each time only 2-3 philosophers are eating and the one ready never gets a chance for a long time is definitely possible with our algorithm.<br/>
Another method is using **Monitors** which are high level constructs present in high level programming languages like Cpp, Java.<br/>

Now, finally let's see the starve free and deadlock free implementation of the Dining Philosophers problem. There are many ways to ensure this but we have implemented the method given in the [book](https://bcs.wiley.com/he-bcs/Books?action=index&itemId=0471694665&itemTypeId=BKS&bcsId=2217).
# Starve Free and Deadlock Free Solution
The main idea behind this was about splitting the philosophers such that the even numbered picked up their left fork first and odd numbered picked up their right fork first so that two neighbouring philosophers would be fighting for the same fork or not asking for the fork atall and this happening alternately. In this process, only one philosopher gets his fork and he can take the other fork as the other neighbour would not ask for this fork, this way there will not be any deadlock. This is starvation free too as unlike the starvation case where one could pick any fork up here we have restricted the forks which are competed to half the total number. So, some forks are never picked up first and even if a philosopher has to wait for the mutual competing fork it would be bounded and after picking it up the worst possible case would be that this neighbour could be eating but like earlier this too will be bounded so starvation to death won't occur.<br/>
**For Example:** Let there be 5 philosophers and philosopher 1 is hungry but philosopher 0 and 2 are eating, now after sometime let's assume 0 has putdown it's fork, then 1 would pick it up and wait for philosopher 2 to complete eating and after philosopher 2 is done grabs it's fork this way the waiting time would be something bounded only.<br/>
This has been implemented in the C file named **DP**.
