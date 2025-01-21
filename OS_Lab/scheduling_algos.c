#include <stdio.h>
#include <limits.h>

void calculate_metrics(int arrival_times[], int burst_times[], int finish_times[], int num_processes, int wait_times[], int response_times[], int turnaround_times[]) {
    for (int i = 0; i < num_processes; i++) {
        turnaround_times[i] = finish_times[i] - arrival_times[i];
        wait_times[i] = turnaround_times[i] - burst_times[i];
        response_times[i] = wait_times[i];
    }
}

void first_come_first_served(int arrival_times[], int burst_times[], int num_processes, int wait_times[], int response_times[], int turnaround_times[]) {
    int finish_times[num_processes];
    finish_times[0] = arrival_times[0] + burst_times[0];

    for (int i = 1; i < num_processes; i++) {
        finish_times[i] = (arrival_times[i] > finish_times[i - 1]) ? arrival_times[i] + burst_times[i] : finish_times[i - 1] + burst_times[i];
    }

    calculate_metrics(arrival_times, burst_times, finish_times, num_processes, wait_times, response_times, turnaround_times);
}

void shortest_job_first(int arrival_times[], int burst_times[], int num_processes, int wait_times[], int response_times[], int turnaround_times[]) {
    int finish_times[num_processes];
    int completed[num_processes];
    int current_time = 0;

    for (int i = 0; i < num_processes; i++) completed[i] = 0;

    for (int count = 0; count < num_processes;) {
        int idx = -1;
        int min_burst = INT_MAX;
        for (int i = 0; i < num_processes; i++) {
            if (!completed[i] && arrival_times[i] <= current_time && burst_times[i] < min_burst) {
                min_burst = burst_times[i];
                idx = i;
            }
        }

        if (idx != -1) {
            current_time += burst_times[idx];
            finish_times[idx] = current_time;
            completed[idx] = 1;
            count++;
        } else {
            current_time++;
        }
    }

    calculate_metrics(arrival_times, burst_times, finish_times, num_processes, wait_times, response_times, turnaround_times);
}

void round_robin(int arrival_times[], int burst_times[], int num_processes, int quantum, int wait_times[], int response_times[], int turnaround_times[]) {
    int remaining_burst[num_processes];
    int finish_times[num_processes];
    int current_time = 0;

    for (int i = 0; i < num_processes; i++) remaining_burst[i] = burst_times[i];

    while (1) {
        int all_done = 1;
        for (int i = 0; i < num_processes; i++) {
            if (remaining_burst[i] > 0) {
                all_done = 0;
                if (arrival_times[i] <= current_time) {
                    int execution_time = (remaining_burst[i] > quantum) ? quantum : remaining_burst[i];
                    current_time += execution_time;
                    remaining_burst[i] -= execution_time;
                    if (remaining_burst[i] == 0) {
                        finish_times[i] = current_time;
                    }
                }
            }
        }
        if (all_done) break;
    }

    calculate_metrics(arrival_times, burst_times, finish_times, num_processes, wait_times, response_times, turnaround_times);
}

void priority_scheduling(int arrival_times[], int burst_times[], int priorities[], int num_processes, int wait_times[], int response_times[], int turnaround_times[]) {
    int finish_times[num_processes];
    int completed[num_processes];
    int current_time = 0;

    for (int i = 0; i < num_processes; i++) completed[i] = 0;

    for (int count = 0; count < num_processes;) {
        int idx = -1;
        int highest_priority = INT_MAX;
        for (int i = 0; i < num_processes; i++) {
            if (!completed[i] && arrival_times[i] <= current_time && priorities[i] < highest_priority) {
                highest_priority = priorities[i];
                idx = i;
            }
        }

        if (idx != -1) {
            current_time += burst_times[idx];
            finish_times[idx] = current_time;
            completed[idx] = 1;
            count++;
        } else {
            current_time++;
        }
    }

    calculate_metrics(arrival_times, burst_times, finish_times, num_processes, wait_times, response_times, turnaround_times);
}

void shortest_remaining_time_first(int arrival_times[], int burst_times[], int num_processes, int wait_times[], int response_times[], int turnaround_times[]) {
    int remaining_burst[num_processes];
    int finish_times[num_processes];
    int current_time = 0;
    int count = 0;

    for (int i = 0; i < num_processes; i++) remaining_burst[i] = burst_times[i];

    while (count < num_processes) {
        int idx = -1;
        int min_remaining = INT_MAX;
        for (int i = 0; i < num_processes; i++) {
            if (arrival_times[i] <= current_time && remaining_burst[i] > 0 && remaining_burst[i] < min_remaining) {
                min_remaining = remaining_burst[i];
                idx = i;
            }
        }

        if (idx != -1) {
            remaining_burst[idx]--;
            current_time++;
            if (remaining_burst[idx] == 0) {
                finish_times[idx] = current_time;
                count++;
            }
        } else {
            current_time++;
        }
    }

    calculate_metrics(arrival_times, burst_times, finish_times, num_processes, wait_times, response_times, turnaround_times);
}

int main() {
    int choice;
    printf("Choose the scheduling algorithm:\n1. First Come First Served\n2. Shortest Job First\n3. Shortest Remaining Time First\n4. Priority Scheduling\n5. Round Robin\n");
    scanf("%d", &choice);

    int num_processes;
    printf("Enter number of processes: ");
    scanf("%d", &num_processes);

    int arrival_times[num_processes], burst_times[num_processes];
    printf("Enter arrival times of the processes: ");
    for (int i = 0; i < num_processes; i++) {
        scanf("%d", &arrival_times[i]);
    }
    printf("Enter the CPU burst times of the processes: ");
    for (int i = 0; i < num_processes; i++) {
        scanf("%d", &burst_times[i]);
    }

    int wait_times[num_processes], response_times[num_processes], turnaround_times[num_processes];

    if (choice == 4) {
        int priorities[num_processes];
        printf("Enter priorities of each process: ");
        for (int i = 0; i < num_processes; i++) {
            scanf("%d", &priorities[i]);
        }
        priority_scheduling(arrival_times, burst_times, priorities, num_processes, wait_times, response_times, turnaround_times);
    } else if (choice == 5) {
        int quantum;
        printf("Enter time quantum: ");
        scanf("%d", &quantum);
        round_robin(arrival_times, burst_times, num_processes, quantum, wait_times, response_times, turnaround_times);
    } else if (choice == 3) {
        shortest_remaining_time_first(arrival_times, burst_times, num_processes, wait_times, response_times, turnaround_times);
    } else if (choice == 2) {
        shortest_job_first(arrival_times, burst_times, num_processes, wait_times, response_times, turnaround_times);
    } else {
        first_come_first_served(arrival_times, burst_times, num_processes, wait_times, response_times, turnaround_times);
    }

    printf("Waiting times: ");
    for (int i = 0; i < num_processes; i++) {
        printf("%d ", wait_times[i]);
    }
    printf("\nResponse times: ");
    for (int i = 0; i < num_processes; i++) {
        printf("%d ", response_times[i]);
    }
    printf("\nTurnaround times: ");
    for (int i = 0; i < num_processes; i++) {
        printf("%d ", turnaround_times[i]);
    }

    float throughput = (float)num_processes / turnaround_times[num_processes - 1];
    printf("\nThroughput: %.2f\n", throughput);

    return 0;
}
