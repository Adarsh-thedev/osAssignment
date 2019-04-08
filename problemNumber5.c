/* CPU schedules N processes that arrive at different total intervals and each process is allocated
CPU for a specific user input total(Round Robin and take total quantum as input from user)
Each process must be assigned priority -> Higher number => Higher Priority 
If a process is preempted by a higher priority process -> add it to the end of queue
Also compute ->
                            Turn Around total and Waiting Time 
Input from user ->  Arrival Time, Burst Time, Priority and Time Quantum

Preemptive Round Robin with priority  */

#include<stdio.h>

int main(){
    int i, j, remainingTime[20], arrivalTime[20], burstTime[20], remain, timeOfExecution=0, timeQuantum,priority[20];
    int flag=0, n, pos, temp, turnAroundTime =0, waitingTime = 0;

    printf("Enter the number of processes : ");
    scanf("%d", &n);
    remain = n;

    for(i=0; i<n; i++){
        printf("Enter arrival time, burst time and priority of process %d : ", i+1);
        scanf("%d", &arrivalTime[i]);
        scanf("%d", &burstTime[i]);
        remainingTime[i] = burstTime[i];
        scanf("%d", &priority[i]);
    }

    // ask user for time quantum of each process
    printf("Enter time quantum of for a process : ");
    scanf("%d", &timeQuantum);

    printf("\n\nProcess\t:TurnAround Time:Waiting Time\n\n");
    for(i=0; i<n; i++){
        pos = i;
        for(j=i+1; j<n; j++){
            if(arrivalTime[i] == arrivalTime[j] && priority[j]>priority[i]){
                pos = j;
        }
    }

    temp = priority[i];
    priority[i] = priority[pos];
    priority[pos] = temp;

    temp = burstTime[i];
    burstTime[i] = burstTime[pos];
    burstTime[pos] = temp;
}

for(i = 0; remain != 0; ){
     if(remainingTime[i]<=timeQuantum && remainingTime[i]>0){
		
        timeOfExecution = timeOfExecution + remainingTime[i];
        remainingTime[i] = 0;
        flag = 1;
    }
    else if(remainingTime[i]>0){
        remainingTime[i] = remainingTime[i] - timeQuantum;
        timeOfExecution = timeOfExecution + timeQuantum;
    }

    if(flag ==1 && remainingTime[i] == 0){
        remain = remain-1; //decrease total number of remainig processes by 1
        // print the completed process
        printf("P(%d)\t:\t%d\t:\t%d\n", i+1, timeOfExecution - arrivalTime[i], timeOfExecution - arrivalTime[i] - burstTime[i]);
        turnAroundTime = turnAroundTime + (timeOfExecution - arrivalTime[i]);
        waitingTime = waitingTime + (timeOfExecution - arrivalTime[i] - burstTime[i]);
        // update turnaround time and waiting time
        // at the end turnAround time and waitingTime will be equal to sum of turnaroundTime and waitingTime 
        // of all the processes
        flag = 0;
    }

     if(i==n-1){  //when the last process is encountered and is executed for one time quantum
            i = 0;  // set i=0, so that it checks processes again starting from process 1
        }
        else if(arrivalTime[i+1]<=timeOfExecution){  // if another process has arrived during the execution of ongoing process
            i++;
        }
        else{
            i = 0;  // if no other process has arrived yet, execute current process for one more time quantum(if required)
        }
    }
        // now we have turnAroundTime= sum of all TATs and waitingTime=sum of all WTs
    float averageTurnaroundTime, averageWaitingTime;
    averageTurnaroundTime = 1.0 * turnAroundTime /n; 
    averageWaitingTime = 1.0 * waitingTime/n;

    printf("Average turnaround time = %f\n",averageTurnaroundTime);
    printf("Average waiting time = %f\n",averageWaitingTime);

    return 0;
}


