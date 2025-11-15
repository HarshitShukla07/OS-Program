// PROGRAM TO IMPLEMENT PRODUCER–CONSUMER PROBLEM (SIMULATION IN C)

// Header files required in VS Code / GCC
#include <stdio.h>      // for printf(), scanf()
#include <stdlib.h>     // for exit()

// Function declarations
void consumer();        // function to consume one item
void producer();        // function to produce one item
void display();         // function to show buffer state

// ------------------------------------------------------------
// GLOBAL VARIABLES
// ------------------------------------------------------------

// Buffer of size 10 (symbolic, not storing actual items)
int a[10];

// 'i' stores number of items currently in the buffer
// i = 0  → buffer empty
// i = 10 → buffer full
int i = 0;


// ------------------------------------------------------------
// MAIN FUNCTION
// ------------------------------------------------------------
int main()
{
    int n;

    while(1)    // infinite loop until user selects Exit
    {
        // Display menu
        printf("\n\nMAIN MENU\n");
        printf("1. CONSUMER\n");
        printf("2. PRODUCER\n");
        printf("3. EXIT\n");
        printf("Enter your choice: ");
        scanf("%d", &n);

        switch(n)
        {
            case 1:
                consumer();     // attempt to consume item
                display();      // show buffer state
                break;

            case 2:
                producer();     // attempt to produce item
                display();      // show buffer state
                break;

            case 3:
                printf("\nExiting Program...\n");
                exit(0);        // terminate program

            default:
                printf("\nInvalid choice! Please try again.\n");
        }
    }

    return 0;
}


// ------------------------------------------------------------
// FUNCTION: consumer()
// WHAT:     Consumer tries to remove an item from buffer
// WHY:      In Producer-Consumer problem, consumer can only
//           consume if buffer is NOT empty
// HOW:      If i > 0, decrease 'i'
// ------------------------------------------------------------
void consumer()
{
    if(i == 0)
    {
        // Buffer empty → consumer must wait
        printf("\nConsumer cannot consume (BUFFER EMPTY)");
    }
    else
    {
        // Buffer has items → consume one
        printf("\nConsumer has consumed one data item");
        i--;    // reduce item count
    }
}


// ------------------------------------------------------------
// FUNCTION: producer()
// WHAT:     Producer tries to add an item to buffer
// WHY:      In Producer-Consumer problem, producer can only
//           produce if buffer is NOT full
// HOW:      If i < 10, increase 'i'
// ------------------------------------------------------------
void producer()
{
    if(i == 10)
    {
        // Buffer full → producer must wait
        printf("\nProducer cannot produce (BUFFER FULL)");
    }
    else
    {
        // Buffer has space → produce item
        printf("\nProducer has produced one data item");
        i++;    // increase item count
    }
}


// ------------------------------------------------------------
// FUNCTION: display()
// WHAT:     Shows buffer status after each operation
// WHY:      Helpful to see free space and filled space
// HOW:      j = free slots, i = filled slots
// ------------------------------------------------------------
void display()
{
    int free_slots = 10 - i;    // how many items producer can produce

    printf("\n\nBUFFER STATUS:\n");
    printf("Producer can produce %d more items\n", free_slots);
    printf("Consumer can consume %d items\n", i);
}
