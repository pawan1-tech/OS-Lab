#include <stdio.h>

#define MAX_PROCESS 10

struct Process {
    int pid; // Process ID
    int arrivalTime; // Arrival Time
    int burstTime; // Burst Time
    int priority; // Priority
    int remainingTime; // Remaining Burst Time
};

// Function to perform Priority Pre-emptive Scheduling
void priorityPreemptiveScheduling(struct Process processes[], int n) {
    int remainingProcesses = n;
    int currentTime = 0;
    int i, highestPriority;

    // Array to keep track of the completion status of each process
    int completionTime[MAX_PROCESS] = {0};

    while (remainingProcesses > 0) {
        highestPriority = -1;
        int highestPriorityValue = 999999; // Initialize with a very large value
        for (i = 0; i < n; i++) {
            if (processes[i].arrivalTime <= currentTime && processes[i].priority < highestPriorityValue && processes[i].remainingTime > 0) {
                highestPriority = i;
                highestPriorityValue = processes[i].priority;
            }
        }

        if (highestPriority == -1) {
            currentTime++;
            continue;
        }

        // Execute the process with the highest priority for 1 unit
        processes[highestPriority].remainingTime--;

        // If the process is completed
        if (processes[highestPriority].remainingTime == 0) {
            remainingProcesses--;
            int completion = currentTime + 1;
            completionTime[highestPriority] = completion;
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
    printf("Enter arrival time, burst time, and priority for each process:\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d: ", i + 1);
        scanf("%d %d %d", &processes[i].arrivalTime, &processes[i].burstTime, &processes[i].priority);
        processes[i].pid = i + 1;
        processes[i].remainingTime = processes[i].burstTime;
    }

    // Perform Priority Preemptive Scheduling
    priorityPreemptiveScheduling(processes, n);

    return 0;
}
