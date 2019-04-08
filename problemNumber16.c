/* Design a scheduler that can schedule the processes arriving system at periodical order
Every process is assigned a fixed time slice
If it is unable to completeb its execution in fixed time slice then automated timer generates interrupt
                                     ->(Round Robin)
scheduler will select next process
Compute avg waiting and turn around time
Take input from user of   -> burst time, arrival time and time quantum */

#include<stdio.h>
int main(){
    int n, time, timeQuantum, remain, i, flag=0, waitingTime=0, turnAroundTime=0;
    int arrivalTime[20], remainingTime[20], burstTime[20];

    // ask the user for number of processes
    printf("Enter the number of processes : ");
    scanf("%d",&n);
    remain = n; //initially remainig process=total number of processes

    // ask user for arrival time,burst time for every process
    for(i=0; i<n; i++){
        printf("Enter arrival time and burst time of process %d : ",i+1);
        scanf("%d", &arrivalTime[i]);
        scanf("%d", &burstTime[i]);
        //initially set remaining time of the process=burst time
        remainingTime[i]=burstTime[i];
    }

    // ask user for time quantum of each process
    printf("Enter time quantum of for a process : ");
    scanf("%d", &timeQuantum);

    printf("\n\nProcess\t:TurnAround Time:Waiting Time\n\n");
    for(time=0, i=0; remain!=0;){  //  loop will run until vlaue of remain equals to 0 or no process is remained
        if(remainingTime[i]<=timeQuantum&&remainingTime[i]>0){
            time = time+remainingTime[i];  //if burst time <= time quantum then total time taken by the process
            // is burst time itself
            remainingTime[i]=0;
            flag = 1;
        }
        else if(remainingTime[i]>0 /*&& remainingTime>timeQuantum*/){
            remainingTime[i] = remainingTime[i] - timeQuantum; // if burst time>time quantum,
            // decrease remaining time by time quantum
            time = time + timeQuantum;
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
    averageWaitingTime = 1.0 * waitingTime/n;

    printf("Average turnaround time = %f\n",averageTurnaroundTime);
    printf("Average waiting time = %f\n",averageWaitingTime);

    return 0;
}