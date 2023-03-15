# Cigarette Smokers Problem
## Problme Statement 
Three smokers are present, each with an endless supply of either tobacco, paper, or matches. An agent places two of the ingredients at a time on a table. There are cigarette rolling machines, for each smoker. To make and smoke cigarettes, the smokers must cooperate together, but only one smoker can smoke at once.

The objective is to create a synchronisation protocol to guarantee that the smokers can produce and consume cigarettes without experiencing resource conflicts, deadlocks, or starvation.

Here the Agent represents the OS which allocates multiple (in this case 2) resources to applications that need resources represented by smokers. 
The main aim is to make sure that if the ingredients (resources) are available that would allow a smoker (application) to smoke (proceed or complete), then that smoker should be woken up and we need to avoid waking up smokers(applications) that cannot smoke(proceed) with the given ingredients provided by agent(OS). 
## Classical Solution
### Sempahores Used are:
- agentsem: used for synchronization of the 3 agent threads which is initialised to 1. 

3 semaphores are used for  synchronization of the smokers who take the ingredients 

- Tobacco: initialised to 0
- Paper: initialised to 0
- Match: initialised to 0

