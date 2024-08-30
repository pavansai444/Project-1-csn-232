# Synchronization Problems in Concurrent Programming
<em> Project-1-CSN-23 <em>

This repository contains implementations of various synchronization problems commonly encountered in concurrent programming. Each problem is designed to illustrate different aspects of process synchronization and inter-process communication.

## Problems Included

### 1. Producer-Consumer Problem
The Producer-Consumer problem is a classic synchronization problem where two processes, the producer and the consumer, share a common, fixed-size buffer. The producer generates data and puts it into the buffer, while the consumer removes data from the buffer. The challenge is to ensure that the producer does not add data to a full buffer and the consumer does not remove data from an empty buffer.

### 2. Readers-Writers Problem
The Readers-Writers problem involves managing access to a shared resource, such as a database, where multiple readers can read simultaneously, but writers require exclusive access. The goal is to prevent data corruption by ensuring that no reader can access the resource while a writer is writing.

### 3. Dining Philosophers Problem
The Dining Philosophers problem is a classic synchronization problem involving five philosophers who alternate between thinking and eating. Each philosopher needs two forks to eat, but there are only five forks available. The challenge is to design a protocol that prevents deadlock and ensures that no philosopher starves.

### 4. Sleeping Barber Problem
The Sleeping Barber problem involves a barber shop with one barber, one barber chair, and a waiting room with a limited number of chairs. The barber sleeps when there are no customers, and wakes up to cut hair when a customer arrives. The challenge is to manage the synchronization between the barber and the customers to avoid race conditions and ensure efficient operation.

### 5. Cigarette Smoker Problem
The Cigarette Smoker problem involves three smokers and an agent. Each smoker needs three ingredients (tobacco, paper, and matches) to make a cigarette, but each smoker has only one of the ingredients. The agent places two of the three ingredients on the table, and the smoker with the third ingredient makes a cigarette. The challenge is to synchronize the smokers and the agent to ensure that only one smoker makes a cigarette at a time.

### 6. Dressing Room Problem
The Dressing Room problem involves multiple people trying to use a limited number of dressing rooms. The challenge is to manage access to the dressing rooms to ensure that no two people use the same room simultaneously and to minimize waiting time.

### 7. H2O Problem
The H2O problem involves synchronizing the formation of water molecules from hydrogen and oxygen atoms. The challenge is to ensure that exactly two hydrogen atoms and one oxygen atom combine to form a water molecule, and to manage the synchronization of the atoms to prevent any atom from being left unpaired.

## Video Explanation
A detailed video explanation of each problem is available <a href="https://drive.google.com/drive/folders/1HfgVoQIouMHC5jVcnXfbX4LOOoc5nbXa?usp=share_link"> here </a>.
