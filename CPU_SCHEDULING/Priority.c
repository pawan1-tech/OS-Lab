#include <stdio.h>
#define MAX 100 

int arrival_time[MAX], burst_time[MAX], priority[MAX];
int waiting_time[MAX], turnaround_time[MAX], completion_time[MAX];
int n; // Number of processes

void calculateSchedulingParameters() {
    int time = 0, NoP = n, LAT = 0, MAX_P = 0;  //NoP = no of process   LAT = least Arival Time
    int PPt[MAX], ATt[MAX];
    int total_waiting_time = 0, total_turnaround_time = 0;
    
    for (int i = 0; i < n; i++) {
        PPt[i] = priority[i];
        ATt[i] = arrival_time[i];
        if (arrival_time[i] > LAT) LAT = arrival_time[i];
        if (priority[i] > MAX_P) MAX_P = priority[i];
    }
    
    int ATi = 0, P1 = PPt[0], P2 = PPt[0];
    int j = -1;
    while (NoP > 0 && time <= 1000) {
        for (int i = 0; i < n; i++) {
            if (ATt[i] <= time && ATt[i] != LAT + 10) {
                if (PPt[i] != MAX_P + 1) {
                    P2 = PPt[i];
                    j = 1;
                    
                    if (P2 < P1) {
                        j = 1;
                        ATi = i;
                        P1 = PPt[i];
                        P2 = PPt[i];
                    }
                }
            }
        }
        
        if (j == -1) {
            time++;
            continue;
        } else {
            waiting_time[ATi] = time - ATt[ATi];
            time += burst_time[ATi];
            turnaround_time[ATi] = time - ATt[ATi];
            ATt[ATi] = LAT + 10;
            j = -1;
            PPt[ATi] = MAX_P + 1;
            ATi = 0;
            P1 = MAX_P + 1;
            P2 = MAX_P + 1;
            NoP--;
        }
    }
    
    for (int i = 0; i < n; i++) {
        total_waiting_time += waiting_time[i];
        total_turnaround_time += turnaround_time[i];
        completion_time[i] = arrival_time[i] + turnaround_time[i];
    }
    printf("\nProcess   Burst Time   Arrival Time   Waiting Time   Turnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf(" %d   \t\t   %d  \t\t %d    \t\t   %d     \t\t   %d\n", i+1, burst_time[i], arrival_time[i], waiting_time[i], turnaround_time[i]);
    }
    
    float avg_waiting_time = (float)total_waiting_time / n;
    float avg_turnaround_time = (float)total_turnaround_time / n;
    
    printf("Average waiting time = %.2f\n", avg_waiting_time);
    printf("Average turnaround time = %.2f\n", avg_turnaround_time);
    

}

int main() {

    n = 5; 
    arrival_time[0] = 0; burst_time[0] = 4; priority[0] = 1;
    arrival_time[1] = 0; burst_time[1] = 3; priority[1] = 2;
    arrival_time[2] = 6; burst_time[2] = 7; priority[2] = 1;
    arrival_time[3] = 11; burst_time[3] = 4; priority[3] = 3;
    arrival_time[4] = 12; burst_time[4] = 2; priority[4] = 2;
    
    calculateSchedulingParameters();
    
    return 0;
}