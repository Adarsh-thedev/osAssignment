/*CPU schedules N processes which arrive at diff time intervals
each process is allocated the CPU for a specific time unit according to user input(preemptive Round Robin)
Each process should be provided numerical priority(higher the number higher the priority is)
If a process is preemted with a higher priority process-> add it to end of queue*/
#include<stdio.h>
int main(){
    int n, time, timeQuantom, remain, i, j, flag=0, waitingTime=0, turnAroundTime=0;
    int arrivalTime[10], remainingTime[10], burstTime[10], priorityOfProcess[10];

    // ask the user for number of processes
    printf("Enter the number of processes : ");
    scanf("%d",&n);
    remain = n; //initially remainig process=total number of processes

    // ask user for arrival time,burst time and priority for every process
    for(i=0; i<n; i++){
        printf("Enter arrival time,burst time and priority of process %d : ",i+1);
        scanf("%d", &arrivalTime[i]);
        scanf("%d", &burstTime[i]);
        //scanf("%d", &priorityOfProcess[i]);
        //initially set remaining time of the process=burst time
        remainingTime[i]=burstTime[i];
    }

    // ask user for time quantom of each process
    printf("Enter time quantom of processes : ");
    scanf("%d", &timeQuantom);

    printf("\n\nProcess\t:TurnAround Time:Waiting Time\n\n");
    for(time=0, i=0; remain!=0;){  //  loop will run until vlaue of remain equals to 0 or no process is remained
        if(remainingTime[i]<=timeQuantom&&remainingTime[i]>0){
            time = time+remainingTime[i];  //if burst time <= time quantum then total time taken by the process
            // is burst time itself
            remainingTime[i]=0;
            flag = 1;
        }
        else if(remainingTime[i]>0 /*&& remainingTime>timeQuantom*/){
            remainingTime[i] = remainingTime[i] - timeQuantom; // if burst time>time quantum,
            // decrease remaining time by time quantum
            time = time + timeQuantom;
            // increase total time of execution by one time quantum
        }

        if(remainingTime[i]==0 && flag==1){ //when a process is completed
            remain = remain-1; //decrease total number of remainig processes by 1
            // print the completed process
            printf("P(%d)\t:\t%d\t:\t%d\n", i+1, time - arrivalTime[i], time - arrivalTime[i] - burstTime[i]);
            turnAroundTime = turnAroundTime + (time - arrivalTime[i]);
            waitingTime = waitingTime + (time - arrivalTime[i] - burstTime[i]);
            // update turnaround time and waiting time
            // at the end turnAround time and waitingTime will be equal to sum of turnaroundTime and waitingTime 
            // of all the processes
            flag = 0;
        }
        if(i==n-1){  //when the last process is encountered and is executed for one time quantum
            i = 0;  // set i=0, so that it checks processes again starting from process 1
        }
        else if(arrivalTime[i+1]<=time){  // if another process has arrived during the execution of ongoing process
            i++;
        }
        else{
            i = 0;  // if no other process has arrived yet, execute current process for one more time quantum(if required)
        }
    }
    // now we have turnAroundTime= sum of all TATs and waitingTime=sum of all WTs
    float averageTurnaroundTime, averageWaitingTime;
    averageTurnaroundTime = 1.0 * turnAroundTime /n; 
    averageWaitingTime = 1.0 * waitingTime;

    printf("Average turnaround time = %f\n",averageTurnaroundTime);
    printf("Average waiting time = %f\n",averageWaitingTime);

    return 0;
}