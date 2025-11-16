// PROGRAM TO IMPLEMENT BANKER'S ALGORITHM (RESOURCE REQUEST ALGORITHM)
// Each line is explained with WHAT, WHY, and HOW comments

#include <conio.h>   // WHY: For clrscr(), getch() — Turbo C specific
#include <stdio.h>   // WHY: For printf(), scanf()

// ------------------- GLOBAL ARRAYS FOR BANKER'S ALGORITHM -------------------
// WHAT: Process IDs\int processId[10];

// WHAT: Maximum resources each process may need (R1, R2, R3)
int maximum_A[10], maximum_B[10], maximum_C[10];

// WHAT: Resources currently allocated to each process
int allocated_A[10], allocated_B[10], allocated_C[10];

// WHAT: Remaining resources needed = max - allocated (calculated later)
int needed_A[10], needed_B[10], needed_C[10];

// OTHER VARIABLES
int processCount = 0;     // WHY: To give unique process IDs
int available_A, available_B, available_C; // HOW: Stores available resources
int sequence[10];          // WHAT: Safe sequence
char processFinished[10];  // WHAT: 'F' = not finished, 'T' = finished

// ------------------------------ MAIN FUNCTION --------------------------------
void main()
{
    int flag = 0, i, j, k;
    int numProcesses, requestingProcess;
    int request_A, request_B, request_C;

    clrscr();   // WHY: Clear screen

    printf("\nenter the number of process:\n");
    scanf("%d", &numProcesses);

    // Assign process IDs and mark all unfinished
    for(i = 0; i < numProcesses; i++)
    {
        processId[i] = processCount;      // WHAT: Assign unique ID
        processFinished[i] = 'F';         // WHY: Mark as not finished
        processCount++;                    // HOW: Increment ID counter
    }

    // Input allocated matrix
    printf("\nenter the allocation of each process:\n");
    for(i = 0; i < numProcesses; i++)
    {
        scanf("%d%d%d", &allocated_A[i], &allocated_B[i], &allocated_C[i]);
    }

    // Input maximum matrix
    printf("\nenter the maximum need of each process:\n");
    for(i = 0; i < numProcesses; i++)
    {
        scanf("%d%d%d", &maximum_A[i], &maximum_B[i], &maximum_C[i]);
    }

    // Input available resources
    printf("\nenter the available resources:\n");
    scanf("%d%d%d", &available_A, &available_B, &available_C);


    // --------------------- CALCULATE NEED MATRIX ----------------------
    for(i = 0; i < numProcesses; i++)
    {
        needed_A[i] = maximum_A[i] - allocated_A[i];  // WHAT: Remaining need
        needed_B[i] = maximum_B[i] - allocated_B[i];
        needed_C[i] = maximum_C[i] - allocated_C[i];
    }


    // ----------------------- DISPLAY RESOURCE TABLE -----------------------
    printf("\nTHE TABLE IS:\n");
    printf("\nprocess  allocation    maximum      need     available\n");

    for(i = 0; i < numProcesses; i++)
    {
        printf("%5d   %2d %2d %2d    %2d %2d %2d    %2d %2d %2d    %2d %2d %2d\n",
               processId[i], allocated_A[i], allocated_B[i], allocated_C[i],
               maximum_A[i], maximum_B[i], maximum_C[i],
               needed_A[i], needed_B[i], needed_C[i],
               available_A, available_B, available_C);
    }


    // ------------------------- REQUEST SECTION --------------------------
    printf("\nPROCESS REQUESTING\n");
    printf("\nenter the process no:\n");
    scanf("%d", &requestingProcess);

    printf("\nenter the resource requested:\n");
    scanf("%d%d%d", &request_A, &request_B, &request_C);

    // Check if request is valid: Request <= Need AND Request <= Available
    if( request_A <= needed_A[requestingProcess] &&
        request_B <= needed_B[requestingProcess] &&
        request_C <= needed_C[requestingProcess] &&
        available_A >= request_A &&
        available_B >= request_B &&
        available_C >= request_C)
    {
        // Grant request temporarily
        needed_A[requestingProcess] -= request_A;
        needed_B[requestingProcess] -= request_B;
        needed_C[requestingProcess] -= request_C;

        allocated_A[requestingProcess] += request_A;
        allocated_B[requestingProcess] += request_B;
        allocated_C[requestingProcess] += request_C;

        available_A -= request_A;
        available_B -= request_B;
        available_C -= request_C;
    }


    // ------------------ SAFETY ALGORITHM (CHECK SAFE STATE) ------------------
    k = 0;
    for(i = 0; i < numProcesses; i++)
    {
        for(j = 0; j < numProcesses; j++)
        {
            // Condition: If need <= available AND process not finished
            if( available_A >= needed_A[j] &&
                available_B >= needed_B[j] &&
                available_C >= needed_C[j] &&
                processFinished[j] == 'F')
            {
                processFinished[j] = 'T';   // WHAT: Mark as completed
                sequence[k] = j;            // Save sequence
                k++;

                // Add allocated resources back
                available_A += allocated_A[j];
                available_B += allocated_B[j];
                available_C += allocated_C[j];
            }
        }
    }


    // --------------------- CHECK FINAL SAFE STATE -----------------------
    if(k == numProcesses)
    {
        printf("\nthe safe sequence is:\n");
        for(i = 0; i < numProcesses; i++)
            printf("%d ", sequence[i]);
    }
    else
    {
        printf("\nthe system is in deadlock state\n");
    }

    getch();  // wait
}
