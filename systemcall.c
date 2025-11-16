#include <conio.h>    /* Header for console I/O functions used in Turbo C (clrscr(), getch()).
                           WHAT: provides screen and keyboard helpers.
                           WHY: this old code uses Turbo C functions for clearing screen and pausing.
                           HOW: modern compilers don't have conio.h; if you port, remove/replace these calls. */

#include <stdio.h>     /* Standard I/O: printf, scanf, etc.
                           WHAT: essential for input/output.
                           WHY: used to show menus and read user input.
                           HOW: available in all C compilers. */

#include <dos.h>      /* DOS-specific functions (findfirst/findnext, file attributes).
                          WHAT: provides functions that interact with DOS environment.
                          WHY: findfirst/findnext and _dos_getfileattr are DOS-era APIs.
                          HOW: Not portable — on modern systems you must use POSIX or Win32 APIs. */

#include <dir.h>      /* Directory helpers for Turbo C (getcwd, chdir, mkdir prototypes).
                          WHAT: gives directory manipulation functions for Turbo C.
                          WHY: used to query or change the working directory and create folders.
                          HOW: Replace with <direct.h> on some compilers or use opendir/chdir/mkdir from POSIX. */

/* Function prototypes - declared so main() can call them before their definitions. */
int list_file();             /* Lists files (menu: all files / by extension / by name). */
int directory();             /* Create a new directory with given name. */
int change_dir();            /* Change current working directory (back, root, forward). */
int subfun(char []);         /* Helper function that finds files matching a pattern and prints them. */

/* main() - program entry point */
void main()
{
    int ch;                 /* 'ch' stores user's menu choice (1..4). */

    clrscr();               /* Clear the console screen so menu prints at top.
                               WHAT: removes previous output.
                               WHY: makes output look clean for the user.
                               HOW: Turbo C provides clrscr(); modern systems use system("clear")/system("cls") or don't clear. */

    /* do-while loop to repeatedly show the menu until user chooses EXIT */
    do
    {
        /* Print the main menu to the screen */
        printf("\n***********************************MAIN MENU************************************\n");
        printf("1.TO DISPLAY LIST OF FILES\n");
        printf("2.TO CREATE DIRECTORY\n");
        printf("3.TO CHANGE THE WORKING DIRECTORY\n");
        printf("4.EXIT\n\n");

        printf("enter yr choice:");
        scanf("%d", &ch);   /* Read integer input from the user and store in 'ch'.
                                Note: No input validation here — if user types non-numeric input, behavior is undefined. */

        /* Switch-case directs program flow based on user's choice */
        switch(ch)
        {
            case 1: list_file();    /* If user chose 1, call list_file() to show files. */
                    break;         /* Break returns control back to loop. */

            case 2: directory();    /* Create a directory. */
                    break;

            case 3: change_dir();   /* Change working directory. */
                    break;

            case 4: exit(0);        /* Cleanly exit program with status 0 (success).
                                      HOW: exit() terminates program immediately. */
                    break;

            default: printf("\n invalid choice\n"); /* If none matched, tell user input invalid. */
        }
    }
    while(ch <= 4); /* Loop condition: continues while ch <= 4. NOTE: This is odd — if user enters 0 or negative, loop repeats too.
                        WHY: probably intended to run until EXIT, but better condition is while(1) with break on case 4. */
}

/* ---------------------- FUNCTION: list_file ---------------------- */
int list_file()
{
    int l;                 /* menu choice inside list_file (1..3) */
    char x[] = "*.*";    /* Default pattern: match all files (DOS wildcard).
                              WHAT: pattern passed to findfirst() / findnext().
                              WHY: when user chooses 'list all', use *.* which returns all filenames.
                              HOW: Beware: storing user input into this small array can overflow if user types long string. */

    clrscr();             /* Clear screen before showing list-file menu. */

    printf("\n********************************LIST FILE DETAIL********************************\n");
    printf("\n1.list all files\n");
    printf("2.list of given extension files\n");
    printf("3.list of named files\n");

    scanf("%d", &l);     /* Read which subtype of listing user wants. */

    switch(l)
    {
        case 1:
            printf("\nlist of all (*.*) files\n");
            subfun(x);      /* Call helper with pattern "*.*" to list every file. */
            break;

        case 2:
            printf("\nenter the extention\n");
            scanf("%s", &x); /* Read extension pattern from user (e.g. "*.c" or "*.txt").
                                  CAUTION: '&x' and fixed size are risky; use a larger buffer and bounds check. */
            subfun(x);       /* List files that match the extension. */
            break;

        case 3:
            printf("\nenter the name of file\n");
            scanf("%s", &x); /* Read specific filename (e.g. "readme.txt"). */
            subfun(x);       /* Search by exact filename (or pattern if user used wildcards). */
            break;

        default:
            printf("\ninvalid choice\n\n\n");
    }
    return 0;             /* Return 0 to indicate success; calling code does not use this value. */
}

/* ---------------------- FUNCTION: subfun ---------------------- */
int subfun(char pattern[10])
{
    /* ffblk is a DOS/Turbo C struct used by findfirst/findnext to hold file info */
    struct ffblk fileinfo;

    /* 'done' will be 0 when findfirst/findnext succeed (DOS returns 0 for success) */
    int done, page_count = 0, file_count = 0;

    /* findfirst() finds the first file matching 'pattern' and fills 'fileinfo'.
       Flags = 0 means normal files only.
       It returns 0 when successful, non-zero when no file / error. */
    done = findfirst(pattern, &fileinfo, 0);

    /* Loop while findfirst/findnext find files; when done != 0 loop ends. */
    while (!done)
    {
        printf("%s\n", fileinfo.ff_name); /* Print filename (ff_name member from ffblk). */

        done = findnext(&fileinfo);         /* Find the next matching file. */

        file_count++;                       /* Keep total count of found files. */
        page_count++;                       /* Keep count to paginate output. */

        /* If many files, pause every 32 lines so user can read. */
        if (page_count >= 32)
        {
            printf("\npress any key to continue\n");
            getch();        /* Wait for key press. */
            page_count = 0; /* Reset page counter after pausing. */
        }
    }

    printf("\ntotal no. of files: %d\n", file_count); /* Print final tally. */
    return 0;
}

/* ---------------------- FUNCTION: directory ---------------------- */
int directory()
{
    unsigned attrib;                /* used to hold file attributes returned by DOS call */
    char name[10], buffer[MAXPATH]; /* name: user-given directory name, buffer: used for current path */

    printf("\n enter the directory name\n");
    scanf("%s", &name);            /* Read directory name from user. */

    getcwd(buffer, MAXPATH);        /* Get current working directory path into buffer. */
    printf("\ncurrent directory:%s\n", buffer);

    /* _dos_getfileattr(name, &attrib) returns 0 if file/directory exists (success).
       We check this to avoid creating an already existing directory. */
    if (_dos_getfileattr(name, &attrib) == 0)
    {
        printf("\n%s is already availaible", name);
    }
    else
    {
        mkdir(name);                 /* Create the directory with given name. */
        printf("\n%s directory succesfully created", name);
    }
    return 0;
}

/* ---------------------- FUNCTION: change_dir ---------------------- */
int change_dir()
{
    char buffer[MAXPATH];           /* Buffer to hold current directory path. */
    int d;                          /* Choice for change-dir sub-menu. */

    /* Print current directory using getcwd() before making changes */
    printf("\ncurrent directory=%s\n", getcwd(buffer, MAXPATH));

    printf("\nCHANGE DIRECTORY\n");
    printf("\n1.step by step backward\n");
    printf("2.goto root\n");
    printf("3.forward directory\nenter ur choice:");

    scanf("%d", &d);              /* Read which change mode user wants. */

    switch(d)
    {
        case 1: chdir("..");       /* Move one level up in directory hierarchy.
                                       WHY: commonly used to back out of subfolders.
                                       HOW: chdir("..") changes working dir to parent. */
                break;

        case 2: chdir("\\");      /* Change to root directory (in DOS/Windows root is \ ).
                                       NOTE: escaping backslash is needed in C string \ becomes single backslash. */
                break;

        case 3: printf("\nplease enter the directory name:");
                scanf("%s", &buffer); /* Read subdirectory name to go into (relative name). */
                chdir(buffer);        /* Change into that directory. */
                break;
    }

    /* Show the new current working directory after change */
    printf("\ncurrent directory:%s", getcwd(buffer, MAXPATH));
    return 0;
}
