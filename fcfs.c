#include <stdio.h>   // Required for input/output functions like printf and scanf

int main() {
    int p[10], i, j, n;// p[] stores process IDs; i, j are loop counters; n is number of processes
    int b[10], a[10]; // b[] stores burst times; a[] stores arrival times
    int w[10], tt[10];// w[] stores waiting times; tt[] stores turnaround times
    int bt[10]; // bt[] stores cumulative burst times (used for calculating waiting time)
    int temp, count = 0; // temp is used for swapping; count assigns process IDs
    float avgw = 0, avgt = 0;// avgw and avgt store average waiting and turnaround times

    printf("Enter the number of processes: ");
    scanf("%d", &n);              // Input total number of processes

    for (i = 0; i < n; i++) {
        p[i] = count++;           // Assign unique process IDs starting from 0
    }

    printf("\nEnter the arrival time of each process:\n");
    for (i = 0; i < n; i++) {
        scanf("%d", &a[i]);       // Input arrival time for each process
    }

    printf("\nEnter the burst time of each process:\n");
    for (i = 0; i < n; i++) {
        scanf("%d", &b[i]);       // Input burst time for each process
    }

    // Sort processes by arrival time to simulate FCFS scheduling
    for (i = 0; i < n; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (a[j] > a[j + 1]) {
                // Swap arrival times
                temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;

                // Swap burst times
                temp = b[j];
                b[j] = b[j + 1];
                b[j + 1] = temp;

                // Swap process IDs to maintain correct mapping
                temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }

    w[0] = 0;                     // First process has zero waiting time
    bt[0] = b[0];                 // First process finishes after its burst time

    // Calculate cumulative burst times for each process
    for (i = 1; i < n; i++) {
        bt[i] = b[i] + bt[i - 1]; // bt[i] = total time elapsed till process i finishes
    }

    // Calculate waiting time: time before process starts execution
    for (i = 1; i < n; i++) {
        w[i] = bt[i - 1] - a[i];  // Waiting time = time when previous process finished - arrival time
    }

    // Calculate turnaround time: total time from arrival to completion
    for (i = 0; i < n; i++) {
        tt[i] = w[i] + b[i];      // Turnaround time = waiting time + burst time
    }

    // Reorder results by original process IDs for final display
    for (i = 0; i < n; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (p[j] > p[j + 1]) {
                // Swap process IDs
                temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;

                // Swap burst times
                temp = b[j];
                b[j] = b[j + 1];
                b[j + 1] = temp;

                // Swap arrival times
                temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;

                // Swap waiting times
                temp = w[j];
                w[j] = w[j + 1];
                w[j + 1] = temp;

                // Swap turnaround times
                temp = tt[j];
                tt[j] = tt[j + 1];
                tt[j + 1] = temp;
            }
        }
    }

    // Display final scheduling results
    printf("\nFCFS Scheduling Results:\n");
    printf("   P   AT   BT   WT   TT\n");
    for (i = 0; i < n; i++) {
        printf("%4d%4d%4d%4d%4d\n", p[i], a[i], b[i], w[i], tt[i]);
    }

    // Calculate average waiting and turnaround times
    for (i = 0; i < n; i++) {
        avgw += w[i];
        avgt += tt[i];
    }

    avgw /= n;
    avgt /= n;

    // Display averages
    printf("\nAverage Waiting Time = %.2f", avgw);
    printf("\nAverage Turnaround Time = %.2f\n", avgt);

    return 0;
}

