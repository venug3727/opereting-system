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

void mlfqScheduling(struct Process processes[], int n, int time_quantum[], int num_levels) {
    int current_time = 0;
    int remaining_processes = n;

    // Arrays to track remaining burst time and priority level of processes
    int remaining_time[MAX_PROCESS];
    int current_level[MAX_PROCESS];

    for (int i = 0; i < n; i++) {
        remaining_time[i] = processes[i].burst_time;
        current_level[i] = 0;
    }

    while (remaining_processes > 0) {
        int flag = 0;

        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= current_time && remaining_time[i] > 0) {
                flag = 1;

                // Process is eligible for execution
                if (remaining_time[i] > time_quantum[current_level[i]]) {
                    // Process executes for time quantum of its level
                    current_time += time_quantum[current_level[i]];
                    remaining_time[i] -= time_quantum[current_level[i]];

                    // Move process to lower priority level
                    current_level[i] = (current_level[i] + 1) % num_levels;
                } else {
                    // Process completes execution
                    current_time += remaining_time[i];
                    processes[i].completion_time = current_time;
                    remaining_processes--;
                    remaining_time[i] = 0;
                }
            }
        }

        // If no process was eligible for execution, move time forward
        if (flag == 0) {
            current_time++;
        }
    }

    // Calculate turnaround time and waiting time
    for (int i = 0; i < n; i++) {
        processes[i].turnaround_time = processes[i].completion_time - processes[i].arrival_time;
        processes[i].waiting_time = processes[i].turnaround_time - processes[i].burst_time;
    }
}

int main() {
    int n, num_levels;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    printf("Enter the number of priority levels: ");
    scanf("%d", &num_levels);

    int time_quantum[num_levels];

    printf("Enter time quantum for each level: ");
    for (int i = 0; i < num_levels; i++) {
        printf("Level %d: ", i + 1);
        scanf("%d", &time_quantum[i]);
    }

    struct Process processes[MAX_PROCESS];

    // Input process details
    for (int i = 0; i < n; i++) {
        processes[i].id = i + 1;
        printf("Enter arrival time and burst time for process %d: ", i + 1);
        scanf("%d %d", &processes[i].arrival_time, &processes[i].burst_time);
    }

    mlfqScheduling(processes, n, time_quantum, num_levels);

    // Output process details
    printf("\nProcess ID\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t\t%d\n", processes[i].id, processes[i].arrival_time,
               processes[i].burst_time, processes[i].completion_time, processes[i].turnaround_time,
               processes[i].waiting_time);
    }

    return 0;
}
