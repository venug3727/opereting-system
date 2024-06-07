#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_TASKS 10

typedef struct {
    int id;
    int execution_time; // in milliseconds (capacity)
    int deadline; // in milliseconds
    int period; // in milliseconds
    int remaining_time; // in milliseconds
    int next_deadline; // in milliseconds
} Task;

void simulateEDFScheduling(Task tasks[], int num_tasks, int hyper_period) {
    printf("Time(ms) | Task\n");
    printf("---------|-----\n");

    for (int time = 0; time < hyper_period; ++time) {
        int earliest_deadline_task = -1;
        int earliest_deadline = INT_MAX;

        for (int i = 0; i < num_tasks; ++i) {
            if (time % tasks[i].period == 0) {
                tasks[i].remaining_time = tasks[i].execution_time;
                tasks[i].next_deadline = time + tasks[i].deadline;
            }
            if (tasks[i].remaining_time > 0 && tasks[i].next_deadline < earliest_deadline) {
                earliest_deadline = tasks[i].next_deadline;
                earliest_deadline_task = i;
            }
        }

        if (earliest_deadline_task != -1) {
            printf(" %7d |  T%d\n", time, tasks[earliest_deadline_task].id);
            tasks[earliest_deadline_task].remaining_time--;
        } else {
            printf(" %7d |  IDLE\n", time);
        }
    }
}

int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

int lcm(int a, int b) {
    return (a * b) / gcd(a, b);
}

int main() {
    int num_tasks;
    printf("Enter the number of tasks: ");
    scanf("%d", &num_tasks);

    if (num_tasks > MAX_TASKS) {
        printf("Maximum number of tasks exceeded!\n");
        return 1;
    }

    Task tasks[MAX_TASKS];
    int hyper_period = 1;

    for (int i = 0; i < num_tasks; ++i) {
        tasks[i].id = i + 1;
        printf("Enter execution time (ms), deadline (ms), and period (ms) for Task %d: ", tasks[i].id);
        scanf("%d %d %d", &tasks[i].execution_time, &tasks[i].deadline, &tasks[i].period);
        tasks[i].remaining_time = tasks[i].execution_time;
        tasks[i].next_deadline = tasks[i].deadline;

        hyper_period = lcm(hyper_period, tasks[i].period);
    }

    simulateEDFScheduling(tasks, num_tasks, hyper_period);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_TASKS 10

typedef struct {
    int id;
    int tickets; // Number of tickets
    int execution_time; // in milliseconds
    int remaining_time; // in milliseconds
} Task;

void simulateLotteryScheduling(Task tasks[], int num_tasks, int total_tickets, int total_execution_time) {
    printf("Time(ms) | Task\n");
    printf("---------|-----\n");

    srand(time(NULL)); // Seed for random number generation

    for (int time = 0; time < total_execution_time; ++time) {
        int winning_ticket = rand() % total_tickets;
        int cumulative_tickets = 0;

        for (int i = 0; i < num_tasks; ++i) {
            cumulative_tickets += tasks[i].tickets;
            if (winning_ticket < cumulative_tickets && tasks[i].remaining_time > 0) {
                printf(" %7d |  T%d\n", time, tasks[i].id);
                tasks[i].remaining_time--;
                if (tasks[i].remaining_time == 0) {
                    total_tickets -= tasks[i].tickets;
                }
                break;
            }
        }
    }
}

int main() {
    int num_tasks;
    printf("Enter the number of tasks: ");
    scanf("%d", &num_tasks);

    if (num_tasks > MAX_TASKS) {
        printf("Maximum number of tasks exceeded!\n");
        return 1;
    }

    Task tasks[MAX_TASKS];
    int total_tickets = 0;
    int total_execution_time = 0;

    for (int i = 0; i < num_tasks; ++i) {
        tasks[i].id = i + 1;
        printf("Enter execution time (ms) and number of tickets for Task %d: ", tasks[i].id);
        scanf("%d %d", &tasks[i].execution_time, &tasks[i].tickets);
        tasks[i].remaining_time = tasks[i].execution_time;
        total_tickets += tasks[i].tickets;
        total_execution_time += tasks[i].execution_time;
    }

    simulateLotteryScheduling(tasks, num_tasks, total_tickets, total_execution_time);

    return 0;
}
