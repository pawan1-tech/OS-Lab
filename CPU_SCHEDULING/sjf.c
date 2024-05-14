

#include <stdio.h>

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void sortProcessByBurstTime(int n, int burstTime[], int process[]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (burstTime[j] > burstTime[j + 1]) {
                swap(&burstTime[j], &burstTime[j + 1]);
                swap(&process[j], &process[j + 1]);
            }
        }
    }
}

void findWaitingTime(int processes[], int n, int bt[], int wt[]) {
    wt[0] = 0;

    for (int i = 1; i < n ; i++ ) {
        wt[i] = bt[i-1] + wt[i-1] ;
    }
}

void findTurnAroundTime( int processes[], int n, int bt[], int wt[], int tat[]) {
    for (int i = 0; i < n ; i++)
        tat[i] = bt[i] + wt[i];
}

void findavgTime( int processes[], int n, int bt[]) {
    int wt[n], tat[n], total_wt = 0, total_tat = 0;

    findWaitingTime(processes, n, bt, wt);

    findTurnAroundTime(processes, n, bt, wt, tat);

    printf("Processes  Burst time  Waiting time  Turn around time\n");

    for (int i=0; i<n; i++) {
        total_wt = total_wt + wt[i];
        total_tat = total_tat + tat[i];
        printf(" %d   \t\t  %d \t\t %d  \t\t\t  %d\n",i+1,bt[i],wt[i],tat[i]);
    }

    printf("Average waiting time = %.2f\n", (float)total_wt / (float)n);
    printf("Average turn around time = %.2f\n", (float)total_tat / (float)n);
}

int main() {
    int processes[] = { 1, 2, 3,4};
    int n = sizeof processes / sizeof processes[0];

    int burst_time[] = {6, 8, 7, 3};

    sortProcessByBurstTime(n, burst_time, processes);
    findavgTime(processes, n, burst_time);
    
    return 0;
}