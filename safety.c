#include <stdio.h>

// ---------- Global Arrays ----------
// These arrays store data for each process.
int p[10];                     // Process numbers: P0, P1, P2, ...
int max1[10], max2[10], max3[10];     // MAX requirement of resources R1, R2, R3
int all1[10], all2[10], all3[10];     // ALLOCATION matrix
int need1[10], need2[10], need3[10];  // NEED matrix = MAX - ALLOCATION
int avail1, avail2, avail3;           // AVAILABLE resources of R1, R2, R3
int seq[10];                         // Stores safe sequence order
char finish[10];                     // 'F' = Not finished, 'T' = Finished
int count = 0;                       // Helps assign process IDs

int main()
{
    int i, j, k, n;

    // ---------------- INPUT SECTION ----------------
    printf("\nEnter the number of processes: ");
    scanf("%d", &n);

    // Initialize process IDs and mark processes unfinished
    for(i = 0; i < n; i++)
    {
        p[i] = count;      // Assign P0, P1, P2...
        finish[i] = 'F';   // Initially all processes are unfinished
        count++;           // Update next ID
    }

    // ----------- INPUT ALLOCATION MATRIX --------------
    printf("\nEnter allocation for each process (R1 R2 R3):\n");
    for(i = 0; i < n; i++)
    {
        scanf("%d %d %d", &all1[i], &all2[i], &all3[i]);
    }

    // ------------ INPUT MAXIMUM DEMAND ----------------
    printf("\nEnter maximum demand for each process (R1 R2 R3):\n");
    for(i = 0; i < n; i++)
    {
        scanf("%d %d %d", &max1[i], &max2[i], &max3[i]);
    }

    // ----------- INPUT AVAILABLE RESOURCES -------------
    printf("\nEnter available resources (R1 R2 R3): ");
    scanf("%d %d %d", &avail1, &avail2, &avail3);

    // ----------- CALCULATE NEED MATRIX (Max - Allocation) ------------
    for(i = 0; i < n; i++)
    {
        need1[i] = max1[i] - all1[i];
        need2[i] = max2[i] - all2[i];
        need3[i] = max3[i] - all3[i];
    }

    // ------------ DISPLAY TABLE ----------------
    printf("\nPROCESS   ALLOCATION      MAXIMUM         NEED");
    printf("\n         R1 R2 R3      R1 R2 R3       R1 R2 R3\n");

    for(i = 0; i < n; i++)
    {
        printf("P%d        %2d %2d %2d      %2d %2d %2d      %2d %2d %2d\n",
               p[i],
               all1[i], all2[i], all3[i],
               max1[i], max2[i], max3[i],
               need1[i], need2[i], need3[i]);
    }

    // ------------ SAFETY ALGORITHM --------------
    k = 0;   // Index to store safe sequence

    /*
       WHY TWO LOOPS?
       The outer loop (i) repeats n times so every process gets chance.
       The inner loop (j) checks each process.

       Even if a process becomes runnable after resources updated,
       the next iteration will catch it.
    */

    for(i = 0; i < n; i++)           // Outer loop (repeated passes)
    {
        for(j = 0; j < n; j++)       // Inner loop (check each process)
        {
            // Condition to execute process j:
            // 1. Process not already finished
            // 2. Available resources >= Need
            if(finish[j] == 'F' &&
               avail1 >= need1[j] &&
               avail2 >= need2[j] &&
               avail3 >= need3[j])
            {
                // Mark finished
                finish[j] = 'T';

                // Add process to safe sequence
                seq[k] = j;
                k++;

                // Release allocated resources back to AVAIL
                avail1 += all1[j];
                avail2 += all2[j];
                avail3 += all3[j];
            }
        }
    }

    // ------------ PRINT RESULT --------------
    if(k == n)
    {
        printf("\nSYSTEM IS IN SAFE STATE.\nSafe sequence: ");
        for(i = 0; i < n; i++)
            printf("P%d ", seq[i]);
    }
    else
    {
        printf("\nSYSTEM IS IN UNSAFE STATE (DEADLOCK POSSIBLE)\n");
    }

    return 0;
}
