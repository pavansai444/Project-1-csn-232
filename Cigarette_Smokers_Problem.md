# Cigarette Smokers Problem
## Problem Statement 
Three smokers are present, each with an endless supply of either tobacco, paper, or matches. An agent places two of the ingredients at a time on a table. There are cigarette rolling machines, for each smoker. To make and smoke cigarettes, the smokers must cooperate together, but only one smoker can smoke at once.

The objective is to create a synchronisation protocol to guarantee that the smokers can produce and consume cigarettes without experiencing resource conflicts, deadlocks, or starvation.

Here the Agent represents the OS which allocates multiple (in this case 2) resources to applications that need resources represented by smokers. 
The main aim is to make sure that if the ingredients (resources) are available that would allow a smoker (application) to smoke (proceed or complete), then that smoker should be woken up and we need to avoid waking up smokers(applications) that cannot smoke(proceed) with the given ingredients provided by agent(OS). 

## Classical Solution

### Sempahores Used are :

- **`AgentSem`**: used for synchronization of the 3 agent threads which is initialised to 1. 

3 semaphores are used for  synchronization of the smokers who take the ingredients 

- **`tobacco`**: initialised to 0
- **`paper`**: initialised to 0
- **`match`**: initialised to 0

### Agnent Threads :

Thre three agent threads are :

- **agentTP**: agent who provides tobacco and paper. 
- **agentPM**: agent who provides paper and match. 
- **agentMT**: agent who provides match and tobacco. 

### Pseudo Code for Agent threads are :

- **agentTP**:
```
AgentSem.wait()
tobacco.signal() // signals that tobacco has been placed on table
paper.signal() //signals that paper has been placed on table
```
- **agentPM**:
```
AgentSem.wait()
paper.signal() //signals that paper has been placed on table
match.signal() //signals that match has been placed on table
```
- **agentMT**:
```
AgentSem.wait()
match.signal() //signals that match has been placed on table
tobacco.signal() // signals that tobacco has been placed on table
```
### Pseudo Code for Smokers with different ingredients :

- Smoker with infinite **matches**:
```
tobacco.wait()
paper.wait()
AgentsSem.signal()

```
- Smoker with infinite **tobacco**: 
```
paper.wait()
match.wait()
AgentSem.signal()

```
- Smoker with infinite **paper**:
```
match.wait() 
tobacco.wait() 
AgentSem.signal() 

```
## DEADLOCK :
- This solution is **not** deadlock free. This is because when an agent places 2 ingredients on the table, each ingredients are required by exactly 2 smokers. Suppose **both the smokers take one ingredient each**, then both the smokers cannot make a complete cigarette and hence cannot smoke and do not release `AgentSem`. This leads to a deadlock situation. (if both the ingredient were taken by a single smoker, then it wouldn’t have been a deadlock case). 
- This deadlock situation can be overcome by implementing a pusher or helper fucntion. 

https://www.google.com/url?sa=i&url=https%3A%2F%2Fblog.ksub.org%2Fbytes%2F2016%2F01%2F31%2Fthe-cigarette-smokers%2F&psig=AOvVaw28bMPJidjWeOsoSO0dpKg0&ust=1678970065241000&source=images&cd=vfe&ved=0CA0QjRxqFwoTCNDb1YT53f0CFQAAAAAdAAAAABAD
