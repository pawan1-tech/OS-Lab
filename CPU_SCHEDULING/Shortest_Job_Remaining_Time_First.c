#include <stdio.h>

#define MAX_PROCESS 10

struct Process {
    int pid; // Process ID
    int arrivalTime; // Arrival Time
    int burstTime; // Burst Time
    int remainingTime; // Remaining Burst Time
};

// Function to perform Shortest Job Remaining Time First (SJRTF) scheduling
void sjrtfScheduling(struct Process processes[], int n) {
    int remainingProcesses = n;
    int currentTime = 0;
    int i, shortest;

    // Array to keep track of the completion status of each process
    int completionTime[MAX_PROCESS] = {0};

    while (remainingProcesses > 0) {
        shortest = -1;
        int shortestBurst = 999999; // Initialize with a very large value
        for (i = 0; i < n; i++) {
            if (processes[i].arrivalTime <= currentTime && processes[i].remainingTime < shortestBurst && processes[i].remainingTime > 0) {
                shortest = i;
                shortestBurst = processes[i].remainingTime;
            }
        }

        if (shortest == -1) {
            currentTime++;
            continue;
        }

        // Execute the shortest remaining time process for 1 unit
        processes[shortest].remainingTime--;

        // If the process is completed
        if (processes[shortest].remainingTime == 0) {
            remainingProcesses--;
            int completion = currentTime + 1;
            completionTime[shortest] = completion;
        }
        currentTime++;
    }

    // Calculate turnaround time and waiting time
    int totalTurnaroundTime = 0;
    int totalWaitingTime = 0;
    for (i = 0; i < n; i++) {
        int turnaroundTime = completionTime[i] - processes[i].arrivalTime;
        totalTurnaroundTime += turnaroundTime;
        totalWaitingTime += turnaroundTime - processes[i].burstTime;
        printf("Process %d - Turnaround Time: %d, Waiting Time: %d\n", processes[i].pid, turnaroundTime, turnaroundTime - processes[i].burstTime);
    }

    printf("Average Turnaround Time: %.2f\n", (float)totalTurnaroundTime / n);
    printf("Average Waiting Time: %.2f\n", (float)totalWaitingTime / n);
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[MAX_PROCESS];
    printf("Enter arrival time and burst time for each process:\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d: ", i + 1);
        scanf("%d %d", &processes[i].arrivalTime, &processes[i].burstTime);
        processes[i].pid = i + 1;
        processes[i].remainingTime = processes[i].burstTime;
    }

    // Perform Shortest Job Remaining Time First (SJRTF) Scheduling
    sjrtfScheduling(processes, n);

    return 0;
}
