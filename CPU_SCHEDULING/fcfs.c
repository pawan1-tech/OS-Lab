#include <stdio.h>

void findWaitingTime(int processes[], int n, int bt[], int wt[], int at[]) {
    int service_time[n];
    service_time[0] = at[0];
    wt[0] = 0;

    for (int i = 1; i < n ; i++) {
        service_time[i] = service_time[i-1] + bt[i-1];

        wt[i] = service_time[i] - at[i];

        if (wt[i] < 0) wt[i] = 0;
    }
}

void findTurnAroundTime(int processes[], int n, int bt[], int wt[], int tat[]) {
    for (int i = 0; i < n ; i++)
        tat[i] = bt[i] + wt[i];
}

void findavgTime(int processes[], int n, int bt[], int at[]) {
    int wt[n], tat[n], total_wt = 0, total_tat = 0;

    findWaitingTime(processes, n, bt, wt, at);

    findTurnAroundTime(processes, n, bt, wt, tat);

    printf("Processes   Burst time  Arrival time   Waiting time   Turn around time\n");

    for (int i = 0; i < n ; i++) {
        total_wt = total_wt + wt[i];
        total_tat = total_tat + tat[i];
        printf(" %d \t\t %d \t %d \t\t  %d  \t\t  %d\n",i+1,bt[i],at[i],wt[i],tat[i]);
    }

    printf("Average waiting time = %.2f\n",(float)total_wt / (float)n);
    printf("Average turn around time = %.2f\n",(float)total_tat / (float)n);
}

int main() {
    int processes[] = { 1, 2, 3, 4, 5, 6};
    int n = sizeof processes / sizeof processes[0];

    int burst_time[] = {2,5,6,8,1,3};

    int arrival_time[] = {1,2,0,5,4,3};

    // int burst_time[] = {10,5,2,6,4};

    // int arrival_time[] = {0,3,5,6,8};

    findavgTime(processes, n, burst_time, arrival_time);

    return 0;
}
