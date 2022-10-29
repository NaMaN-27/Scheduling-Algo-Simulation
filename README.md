# Scheduling-Algo-Simulation
simulating Process scheduling algorithm in c++ .

The main goal of this project is to develop Preemptive Kernel,   More specifically, we will:

●	Implement a preemptive scheduler priority based and round robin .

●	Perform context switching  between processes 

A process in this project is a “hypothetical” operating system abstraction that groups together multiple resources. A process is basically a program in execution. The execution of a process must progress in a sequential fashion. 





PREEMPTIVE - PRIORITY BASED:

●	Schedules processes on the basis of priority.

●	In the case of two processes with similar priorities, we use FCFS to choose between them.

●	A number is given to each process to indicate its priority level.

●	Lower is the number assigned, lower is the priority level of a process.

●	If a higher priority task arrives when a lower priority task is executing, the higher priority task replaces the one with lower priority and the latter is put on hold until it completes execution.




ROUND ROBIN :

![image](https://user-images.githubusercontent.com/83614865/198856239-50bc71a9-35eb-4a01-abc4-b86d1806e001.png)





Also Banker's Algorithm has been used for deadlock avoidance to find the safe sequence of the processes . In one of the file the test data has been taken sunch that it generates deadlock . 


WORKFLOW :


![image](https://user-images.githubusercontent.com/83614865/198855991-765c7620-f389-4310-afd4-44dce11bc2c7.png)

Overall workflow of the project is illustrated in the figure above.




