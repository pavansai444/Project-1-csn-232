# Building H2O
## Problem statement
There are two kinds of threads, oxygen and hydrogen. In order to assemble
these threads into water molecules, we have to create a barrier that makes each
thread wait until a complete molecule is ready to proceed.
As each thread passes the barrier, it should invoke bond. You must guarantee
that all the threads from one molecule invoke bond before any of the threads
from the next molecule do.
In other words:
• If an oxygen thread arrives at the barrier when no hydrogen threads are
present, it has to wait for two hydrogen threads.
• If a hydrogen thread arrives at the barrier when no other threads are
present, it has to wait for an oxygen thread and another hydrogen thread.
