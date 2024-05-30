#include <stdio.h>

#define MAX_PROCESS 10

struct Process {
    int id;
    int arrival_time;
    int burst_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
};

void roundRobinScheduling(struct Process processes[], int n, int quantum) {
    int remaining_time[MAX_PROCESS];
    int time = 0;

    // Initialize remaining time for all processes
    for (int i = 0; i < n; i++)
        remaining_time[i] = processes[i].burst_time;

    while (1) {
        int done = 1;

        // Traverse all processes one by one repeatedly
        for (int i = 0; i < n; i++) {
            if (remaining_time[i] > 0) {
                done = 0; // There is still some process remaining

                if (remaining_time[i] > quantum) {
                    time += quantum;
                    remaining_time[i] -= quantum;
                } else {
                    time += remaining_time[i];
                    processes[i].completion_time = time;
                    remaining_time[i] = 0;
                }
            }
        }

        // If all processes are done
        if (done == 1)
            break;
    }

    // Calculate turnaround time and waiting time
    for (int i = 0; i < n; i++) {
        processes[i].turnaround_time = processes[i].completion_time - processes[i].arrival_time;
        processes[i].waiting_time = processes[i].turnaround_time - processes[i].burst_time;
    }
}

int main() {
    int n, quantum;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[MAX_PROCESS];

    // Input process details
    for (int i = 0; i < n; i++) {
        processes[i].id = i + 1;
        printf("Enter arrival time and burst time for process %d: ", i + 1);
        scanf("%d %d", &processes[i].arrival_time, &processes[i].burst_time);
    }

    printf("Enter the time quantum: ");
    scanf("%d", &quantum);

    roundRobinScheduling(processes, n, quantum);

    // Output process details
    printf("\nProcess ID\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t\t%d\n", processes[i].id, processes[i].arrival_time,
               processes[i].burst_time, processes[i].completion_time, processes[i].turnaround_time,
               processes[i].waiting_time);
    }

    return 0;
}
