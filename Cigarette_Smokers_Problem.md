# Cigarette Smokers Problem
## Problem Statement 
Three smokers are present, each with an endless supply of either Tobacco, Paper, or  Matches. An agent places two of the ingredients at a time on a table. There are cigarette rolling machines, for each smoker. To make and smoke cigarettes, the smokers must cooperate together, but only one smoker can smoke at once.
The objective is to create a synchronisation protocol to guarantee that the smokers can produce and consume cigarettes without experiencing resource conflicts, deadlocks, or starvation. There can be multiple smokers of a type.
Here the Agent represents the OS which allocates multiple (in this case 2) resources to applications that need resources represented by smokers. 
The main aim is to make sure that if the ingredients (resources) are available that would allow a smoker (application) to smoke (proceed or complete), then that smoker should be woken up and we need to avoid waking up smokers(applications) that cannot smoke(proceed) with the given ingredients provided by agent(OS). 
![image](https://user-images.githubusercontent.com/98742800/225323743-291e36f7-756a-42f5-983e-3afc51db8608.png)
## Solution

### Sempahores Used are :

- **`mutex_Agent`**: used for synchronization of the 3 agent threads which is initialised to 1. 

3 semaphores are used for  synchronization of the smokers who take the ingredients 

- **`Tobacco`**: initialised to 0
- **`Paper`**: initialised to 0
- **` Match`**: initialised to 0

### Agnent Threads :

Thre three agent threads are :

- **agentTP**: agent who provides Tobacco and Paper. 
- **agentPM**: agent who provides Paper and  Match. 
- **agentMT**: agent who provides  Match and Tobacco. 

### Pseudo Code for Agent threads are :

- **agentTP**:
```c
    // Agent producing Tobacco and Paper
void *agentTP(void* arg){
    while(1){
    wait(&mutex_Agent);
    printf("Agent placed Tobacco and Paper\n");
    signal(&Tobacco);
    signal(&Paper);
    }
}
```
Agent encompasses three concurrent threads that produces two ingredients at a time. The agent TP places tobacco and paper on the table.​
### Pseudo Code for Helper :
```c
    //The three helpers help to determine the state of the ingredients on table
void *helperT(void* num){
    while(1){
        wait(&Tobacco);
        wait(&mutex);
        if(PaperReady){
            PaperReady=false;
            signal(&MatchSem);
        }else if(MatchReady){
            MatchReady=false;
            signal(&PaperSem);
        }else{
            TobaccoReady=true;
        }
        signal(&mutex);
       
    }
}
```
Helper is used to determine the ingredients placed by the agent. The three helpers T M & P signal the smoker with counter ingredient. ​
### Pseudo Code for Smokers with different ingredients :
```c
    //The code for smoker holding infinite supply of Tobacco
void *TobaccoSmoker(void *arg){
    char* ch="TS";
   while(1){
        wait(&tMut);
    printf("\033[0;34mTS %d\033[0;0m waiting for Paper & Matches\n",pthread_self()%100);
   // signal(&mutex_Agent);
    wait(&TobaccoSem);
    makeCigarette(ch);
    printf("TobaccoSmoker %d enter CS \n",pthread_self()%100);
    signal(&mutex_Agent);
    smoke(ch);
        signal(&tMut);
    }
}
```
The smoker waits for the helper to signal on their respective semaphore. After creating cigarette it signals the agent to produce next set of ingredients. The mutual exclusion between the same type of smokers is ensured by tmut, pmut, mmut.​
## DEADLOCK :
- This solution is deadlock free. This is because when an agent places 2 ingredients on the table, the helper checks for the smoker that requires these ingredients and signals them. This is done mutually exclusively.

## STARVATION :
- The type of smoker is determined by the agent threads that produce ingredients randomly. The starvation might occur between the smokers of same type. This is avoided by the use of semaphores based on queues that ensures faireness.

