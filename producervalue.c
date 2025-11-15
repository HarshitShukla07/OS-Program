// Program to implement Producer–Consumer Problem using values
// Written without Turbo C functions (works in VS Code / modern compilers)

#include <stdio.h>
#include <stdlib.h>

// Function declarations
void consumer();
void producer();
void display();

// Global buffer of size 10
int a[10];      // Shared buffer storing produced values
int i = 0;      // Number of items currently in buffer
int j = 0;      // Index for inserting new data (tracks last inserted position)

int main()      // main function begins program
{
    int n;

    printf("Producer–Consumer Problem (Buffer size = 10)\n");

    // Menu runs until the user presses EXIT
    do
    {
        printf("\n\nMAIN MENU\n");
        printf("1. CONSUMER\n");
        printf("2. PRODUCER\n");
        printf("3. EXIT\n");
        printf("Enter your choice: ");
        scanf("%d", &n);

        switch(n)
        {
            case 1:
                consumer();   // Remove item from buffer
                display();    // Show buffer status
                break;

            case 2:
                producer();   // Add item to buffer
                display();    // Show buffer status
                break;

            case 3:
                exit(0);      // Proper exit function for modern compilers

            default:
                printf("\nInvalid choice\n");
        }

    } while(n <= 3 && n != 0);

    return 0;
}


// ------------------------- CONSUMER FUNCTION -------------------------

// Purpose: Consumer tries to remove a given value from the buffer
void consumer()
{
    int num, count = 0, l;

    // If no items are in the buffer
    if(i == 0)
    {
        printf("\nConsumer cannot consume — buffer is EMPTY");
    }
    else
    {
        printf("\nEnter the value you want to consume: ");
        scanf("%d", &num);

        // Searching the value in buffer
        for(l = 1; l <= j; l++)
        {
            if(a[l] == num)
            {
                count = 1;    // Value found
                break;
            }
        }

        // If value was never produced
        if(count == 0)
        {
            printf("Producer has NOT produced the value %d", num);
        }
        else
        {
            printf("\nConsumer consumed %d", num);
            i--;             // Reduce buffer item count
        }
    }
}


// ------------------------- PRODUCER FUNCTION -------------------------

// Purpose: Producer inserts a value into the buffer
void producer()
{
    int num;

    // Buffer full check
    if(i == 10)
    {
        printf("\nProducer cannot produce — buffer is FULL");
    }
    else
    {
        printf("\nEnter the data to insert in buffer: ");
        scanf("%d", &num);

        j++;         // Move index forward
        a[j] = num;  // Store value in buffer

        printf("\nProducer produced %d", num);

        i++;         // Increase count of items in buffer
    }
}


// ------------------------- DISPLAY FUNCTION -------------------------

// Purpose: Shows how many items can still be produced/consumed
//          Displays all buffer content
void display()
{
    int k = 10 - i;   // Remaining free slots in buffer
    int l;

    printf("\n\nProducer can produce %d more items", k);
    printf("\nConsumer can consume %d items", i);

    printf("\nData in buffer: ");

    for(l = 1; l <= j; l++)
    {
        printf("%d ", a[l]);
    }
}
