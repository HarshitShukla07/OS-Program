#include<stdio.h>

int main()
{
    // p[] stores process IDs
    int p[10];

    // b[] stores burst times (execution time of each process)
    int b[10];

    // w[] stores waiting times of processes
    int w[10];

    // tt[] stores turnaround time of each process
    int tt[10];

    // bt[] stores cumulative burst time used to calculate waiting time
    int bt[10];

    // variables for loops & swapping
    int i, j, n, temp;

    // count is used to assign process IDs sequentially (0,1,2,...)
    int count = 0;

    // variables to store average WT & TT
    float avgw = 0, avgt = 0;

    printf("\nEnter number of processes: ");
    scanf("%d", &n);

    // assigning process IDs
    // p[i] = i (process numbers 0,1,2,…)
    for (i = 0; i < n; i++) {
        p[i] = count;
        count++;
    }

    printf("\nEnter burst times of processes:\n");
    for (i = 0; i < n; i++)
        scanf("%d", &b[i]);

    // Sorting burst times in ascending order
    // Because SJF requires shortest burst time first
    for (i = 0; i < n; i++) {
        for (j = 0; j < n - i; j++) {

            if ((j + 1) == n)
                break;

            // Compare two burst times and swap if greater
            // Also swap corresponding process IDs
            if (b[j] > b[j + 1]) {
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

    // First process waiting time is always 0
    w[0] = 0;

    // bt[i] stores cumulative burst time upto process i
    // bt[0] = burst time of first process
    bt[0] = b[0];

    // Calculate cumulative burst times
    for (i = 1; i < n; i++)
        bt[i] = b[i] + bt[i - 1];

    // waiting time = cumulative burst time of previous process
    for (i = 1; i < n; i++)
        w[i] = bt[i - 1];

    // turnaround time = waiting time + burst time
    for (i = 0; i < n; i++)
        tt[i] = w[i] + b[i];

    // Re-sorting again to display output in original process order
    // Because after SJF sorting, process IDs got rearranged
    // This step restores original order for printing
    for (i = 0; i < n; i++) {
        for (j = 0; j < n - i; j++) {

            if ((j + 1) == n)
                break;

            // Sort based on process IDs (smallest ID first)
            if (p[j] > p[j + 1]) {

                temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;

                temp = b[j];
                b[j] = b[j + 1];
                b[j + 1] = temp;

                temp = w[j];
                w[j] = w[j + 1];
                w[j + 1] = temp;

                temp = tt[j];
                tt[j] = tt[j + 1];
                tt[j + 1] = temp;
            }
        }
    }

    // Display final result
    printf("\nThe result of SJF Scheduling:\n");
    printf("  P  BT  WT  TT\n");

    for (i = 0; i < n; i++)
        printf("%3d%4d%4d%4d\n", p[i], b[i], w[i], tt[i]);

    // Calculate average waiting time & turnaround time
    for (i = 0; i < n; i++) {
        avgw += w[i];
        avgt += tt[i];
    }

    avgw /= n;
    avgt /= n;

    printf("\nAverage WT = %f   Average TT = %f\n", avgw, avgt);

    return 0;
}
