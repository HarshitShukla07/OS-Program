#include <stdio.h>

int main()
{
    int p[10];       // Stores process IDs (0,1,2... so we can track each process)
    int b[10];       // Burst time of each process (how long each process needs CPU)
    int pp[10];      // Priority of each process (lower number = higher priority)
    int w[10];       // Waiting time array
    int tt[10];      // Turnaround time array
    int bt[10];      // Cumulative burst time to compute waiting time

    int i, j, n, temp;
    int count = 0;   // To assign process IDs sequentially
    float avgw = 0, avgt = 0;

    // ------------------------------
    // INPUT: Number of processes
    // ------------------------------
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    // Assign unique process IDs
    // WHY? → After sorting by priority, original order is lost.
    //       So we need IDs to recognize original processes.
    for (i = 0; i < n; i++)
        p[i] = count++;

    // ------------------------------
    // INPUT: Burst time of each process
    // WHY? → CPU execution time needed for each process
    // ------------------------------
    printf("\nEnter burst times of processes:\n");
    for (i = 0; i < n; i++)
        scanf("%d", &b[i]);

    // ------------------------------
    // INPUT: Priority of each process
    // WHY? → Priority Scheduling picks process with *highest priority first*
    //        Here, **lower number = higher priority**
    // ------------------------------
    printf("\nEnter priority of processes:\n");
    for (i = 0; i < n; i++)
        scanf("%d", &pp[i]);

    // =============================================
    // STEP 1: SORT PROCESSES BY PRIORITY
    // =============================================
    // WHY?  → CPU must execute highest priority first.
    // HOW?  → Simple Bubble Sort based on priority array.
    // WHAT? → When we swap priority, we must also swap
    //         corresponding burst time and process ID.
    // =============================================
    for (i = 0; i < n; i++) {
        for (j = 0; j < n - i - 1; j++) {

            if (pp[j] > pp[j + 1]) { // lower priority number = higher priority

                // Swap burst times
                temp = b[j];
                b[j] = b[j + 1];
                b[j + 1] = temp;

                // Swap priority numbers
                temp = pp[j];
                pp[j] = pp[j + 1];
                pp[j + 1] = temp;

                // Swap process IDs (important to track original process)
                temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }

    // =============================================
    // STEP 2: CALCULATE WAITING TIME
    // =============================================

    // First process in sorted order gets CPU immediately
    // WHY? → No waiting for first process
    w[0] = 0;

    // Compute cumulative burst time
    // bt[i] = total time taken by all previous processes
    bt[0] = b[0];

    for (i = 1; i < n; i++)
        bt[i] = b[i] + bt[i - 1];

    // Waiting time = completion time of previous process
    for (i = 1; i < n; i++)
        w[i] = bt[i - 1];

    // =============================================
    // STEP 3: CALCULATE TURNAROUND TIME
    // TAT = Waiting Time + Burst Time
    // =============================================
    for (i = 0; i < n; i++)
        tt[i] = w[i] + b[i];

    // ===========================================================
    // STEP 4: RE-SORT BACK INTO ORIGINAL PROCESS ORDER
    // WHY? → After sorting by priority, P0,P1,P2 order is lost.
    //        But final output must show results according to
    //        original process numbering.
    // ===========================================================
    for (i = 0; i < n; i++) {
        for (j = 0; j < n - i - 1; j++) {
            
            if (p[j] > p[j + 1]) {  // sort by original process ID

                temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;

                temp = b[j];
                b[j] = b[j + 1];
                b[j + 1] = temp;

                temp = pp[j];
                pp[j] = pp[j + 1];
                pp[j + 1] = temp;

                temp = w[j];
                w[j] = w[j + 1];
                w[j + 1] = temp;

                temp = tt[j];
                tt[j] = tt[j + 1];
                tt[j + 1] = temp;
            }
        }
    }

    // =============================================
    // STEP 5: PRINT FINAL RESULT TABLE
    // =============================================
    printf("\nPriority Scheduling Result:\n");
    printf("   P   BT  PR  WT  TT\n");

    for (i = 0; i < n; i++)
        printf("%4d%4d%4d%4d%4d\n", p[i], b[i], pp[i], w[i], tt[i]);

    // =============================================
    // STEP 6: CALCULATE AVERAGE TIMES
    // =============================================
    for (i = 0; i < n; i++) {
        avgw += w[i];
        avgt += tt[i];
    }

    avgw /= n;
    avgt /= n;

    printf("\nAverage Waiting Time = %f", avgw);
    printf("\nAverage Turnaround Time = %f\n", avgt);

    return 0;
}
