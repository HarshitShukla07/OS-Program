// program to implement sleeping barber problem (Simulation in C with explanation)


//#include <conio.h>
#include<process.h>
#include <stdio.h>
#include<stdlib.h>

// Function declarations
void customerentry();
void customerexit();
void display();

// ----------------------
// GLOBAL VARIABLES
// ----------------------

// c[] : Array to store customers in barber shop (index 0 = being served, rest = waiting room)
int c[11];      

// mutex : acts like a lock (0 = barber free/sleeping, 1 = barber busy)
// Here it's only used to indicate barber is serving someone.
int mutex = 0;

// i : number of customers currently inside shop (being served + waiting)
int i = 0;


int main()
{
    int n;
    //clrscr();   // clear screen (Turbo C)

    // Initial message
    printf("\nBarber is sleeping and the capacity of the waiting room is 10\n");

    // Menu loop
    do
    {
        printf("\n\nMAIN MENU\n1.INSERT CUSTOMER\n2.EXIT CUSTOMER\n3.EXIT\nenter ur choice:");
        scanf("%d", &n);

        switch(n)
        {
            case 1:
                customerentry();   // Insert a new customer
                display();        // Display the shop status
                break;

            case 2:
                customerexit();   // Remove the customer being served first
                display();
                break;

            case 3:
                exit(0);          // Exit program

            default:
                printf("\n\nInvalid choice\n\n");
        }
    }
    while(n <= 3 && n != 0);

   // getch();
   return 0;
}


// -------------------------------------------
// FUNCTION: customerentry()
// WHAT : Adds a new customer to the barber shop
// WHY  : To simulate customer arrival
// HOW  : Add number in array and increase count
// -------------------------------------------
void customerentry()
{
    int num;

    // If shop is empty or has space (< 11 total)
    if(i == 0 || i < 11)
    {
        mutex = 1; // barber is now busy (customer entering)

        printf("\nEnter the customer/process number to enter: ");
        scanf("%d", &num);

        // add customer to array
        // c[0] will be served, c[1..10] will wait
        c[i] = num;

        i++; // increase count of customers inside
    }
    else
        printf("\nProcess can't enter (waiting room full)\n");
}


// -------------------------------------------
// FUNCTION: customerexit()
// WHAT : Removes the customer being served
// WHY  : To simulate service completion & next customer moves
// HOW  : Shift array left and reduce count
// -------------------------------------------
void customerexit()
{
    int l;

    if(i != 0) // if shop not empty
    {
        // Customer at position 0 is being served → remove him
        printf("\n\nThe process exited is: %d", c[0]);

        // Shift waiting customers forward
        for(l = 0; l < i - 1; l++)
            c[l] = c[l + 1];

        i--; // reduce total customers

        // If no customer left → barber sleeps
        if(i == 0)
        {
            mutex = 0; // barber sleeping
        }
    }
}


// -------------------------------------------
// FUNCTION: display()
// WHAT : Shows barber shop status
// WHY  : To know how many customers, who is waiting, etc.
// HOW  : Print array & conditions
// -------------------------------------------
void display()
{
    // k = number of empty seats in waiting room
    // capacity = 10 seats, so seats empty = 10 - (i-1)
    int k = 10 - i + 1;
    int l;

    if(i == 0)
        printf("\n\n10 processes can enter in waiting room\n0 processes are already in waiting room");
    else
        printf("\n%d more processes can enter in the waiting room\n%d processes are already in waiting room",
               k, i - 1);

    // SHOW WHETHER BARBER IS SLEEPING OR SERVING SOMEONE
    if(mutex == 1)
        printf("\n%d process is being served by barber", c[0]);
    else
        printf("\nBarber is sleeping\n");

    // SHOW WAITING ROOM CUSTOMERS
    if(i > 1)
    {
        printf("\nProcesses in waiting room:\n");
        for(l = 1; l < i; l++)
            printf("%d ", c[l]);
    }
}
