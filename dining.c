// ==============================================================
//  DINING PHILOSOPHER PROBLEM (SIMULATION)
//  Deep Explanation + Fully Commented Version (VS Code compatible)
// ==============================================================
//
//  This is NOT the real semaphore-based OS solution.
//  This is a simplified COLLEGE SIMULATION that uses arrays to show:
//      - Philosopher status (Thinking or Eating)
//      - Chopstick availability
//
//  Goal: Understand how resource allocation conflicts can occur.
// ==============================================================

#include <stdio.h>
#include <stdlib.h>

// --------------------------------------------------------------
// Function declarations:
//
void wait_fun(int ph);    // Called when philosopher wants to EAT
void signal_fun(int ph);  // Called when philosopher finishes eating
void display();           // Show system state
// --------------------------------------------------------------


// --------------------------------------------------------------
// GLOBAL ARRAYS
// --------------------------------------------------------------
//
// lchop[i] → left chopstick of philosopher i
// rchop[i] → right chopstick of philosopher i
//
// 1 = chopstick is FREE
// 0 = chopstick is BUSY (someone is using it)
//
int lchop[] = {1,1,1,1,1};
int rchop[] = {1,1,1,1,1};

//
// status[i] → state of philosopher i
//   'T' = Thinking
//   'E' = Eating
//
char status[] = {'T','T','T','T','T'};
// --------------------------------------------------------------



// --------------------------------------------------------------
// MAIN FUNCTION
// --------------------------------------------------------------
int main()
{
    int ph;   // philosopher number selected by user
    int n;    // menu choice

    // Menu loop – keeps showing until user chooses exit
    do
    {
        // Showing menu
        printf("\n\n===== MAIN MENU =====");
        printf("\n1. HUNGRY (philosopher wants to EAT)");
        printf("\n2. THINKING (philosopher stops eating)");
        printf("\n3. EXIT");
        printf("\nEnter your choice: ");
        scanf("%d", &n);

        switch(n)
        {
            // --------------------------------------------------
            // Case 1 – philosopher wants to eat
            // --------------------------------------------------
            case 1:
                printf("\nEnter philosopher number (0–4): ");
                scanf("%d", &ph);

                // Call wait() → try to start eating
                wait_fun(ph);

                // Show updated system state
                display();
                break;

            // --------------------------------------------------
            // Case 2 – philosopher wants to stop eating (think)
            // --------------------------------------------------
            case 2:
                printf("\nEnter philosopher number (0–4): ");
                scanf("%d", &ph);

                // signal() → release chopsticks and think
                signal_fun(ph);

                // Show updated system state
                display();
                break;

            // --------------------------------------------------
            // Case 3 – exit
            // --------------------------------------------------
            case 3:
                printf("\nExiting program...\n");
                return 0;

            // --------------------------------------------------
            default:
                printf("\nInvalid choice, try again.\n");
        }

    }
    while(n != 3);   // loop until exit

    return 0;
}





// ===================================================================
//  WAIT FUNCTION (philosopher wants to EAT)
// ===================================================================
//
//  This function tries to allocate BOTH chopsticks to philosopher ph.
//  If successful → philosopher starts eating.
//  If chopsticks unavailable → philosopher must wait.
//
// ===================================================================
void wait_fun(int ph)
{
    // If philosopher is already eating, no need to allocate chopsticks
    if(status[ph] == 'E')
    {
        printf("\nPhilosopher %d is already eating!", ph);
        return;
    }

    // --------------------------------------------------------------
    // Identify chopstick positions logically:
    //
    //   left chopstick of philosopher ph  → (ph + 1) % 5
    //   right chopstick of philosopher ph → (ph - 1 + 5) % 5
    //
    // Why +5?  
    //   To avoid negative value when ph = 0.
    // --------------------------------------------------------------
    int left  = (ph + 1) % 5;
    int right = (ph - 1 + 5) % 5;

    // --------------------------------------------------------------
    // Check whether both chopsticks are FREE
    // --------------------------------------------------------------
    if(lchop[left] == 1 && rchop[right] == 1)
    {
        printf("\nPhilosopher %d starts eating...", ph);

        // Change philosopher status to Eating
        status[ph] = 'E';

        // ----------------------------------------------------------
        // Mark chopsticks as busy (0 means taken)
        // NOTE:
        // This implementation marks 4 chopsticks "busy".
        // This is NOT the real DP algorithm — it's a teaching version.
        // ----------------------------------------------------------
        lchop[ph] = 0;
        rchop[ph] = 0;
        lchop[left] = 0;
        rchop[right] = 0;
    }
    else
    {
        // If any chopstick is busy → eating not possible
        printf("\nPhilosopher %d CANNOT start eating (chopsticks busy)", ph);
    }
}





// ===================================================================
//  SIGNAL FUNCTION (philosopher stops eating → starts THINKING)
// ===================================================================
//
//  This function releases the chopsticks and sets philosopher state
//  back to Thinking.
//
// ===================================================================
void signal_fun(int ph)
{
    // If philosopher already thinking, nothing to release
    if(status[ph] == 'T')
    {
        printf("\nPhilosopher %d is already thinking!", ph);
        return;
    }

    printf("\nPhilosopher %d stops eating and starts thinking.", ph);

    // Set state back to Thinking
    status[ph] = 'T';

    // Calculate left and right chopstick indexes again
    int left  = (ph + 1) % 5;
    int right = (ph - 1 + 5) % 5;

    // --------------------------------------------------------------
    // Release chopsticks (set to free = 1)
    // --------------------------------------------------------------
    lchop[ph] = 1;
    rchop[ph] = 1;
    lchop[left] = 1;
    rchop[right] = 1;
}





// ===================================================================
//  DISPLAY FUNCTION
// ===================================================================
//
//  Shows the current state of:
//  - each philosopher (Thinking / Eating)
//  - availability of chopsticks
//
//  Helps us visualize resource allocation.
// ===================================================================
void display()
{
    int i;

    printf("\n\n------------------ CURRENT STATE ------------------");
    printf("\nPhno  Status  Lchop  Rchop");

    for(i = 0; i < 5; i++)
    {
        printf("\n%d      %c        %d       %d",
               i,
               status[i],   // Thinking or Eating
               lchop[i],    // left chopstick state
               rchop[i]);   // right chopstick state
    }

    printf("\n----------------------------------------------------\n");
}
