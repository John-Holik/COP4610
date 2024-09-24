// File   : Question1.c
// Author : John Holik
// Class  : COP4610
// Desc   : Using parent and child processes to prove Collatz Principle

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdbool.h>
#include <stdlib.h>

// Main
//****************************************************************************************************************//
int main(int argc, char *argv[])
{
    pid_t pid;
    int collatz;

    // Check if a number is provided as a command-line argument
    if (argc != 2 || (collatz = atoi(argv[1])) <= 0)
    {
        fprintf(stderr, "Usage: %s <positive integer>\n", argv[0]);
        return 1;
    }

    /* fork a child process */
    pid = fork();
    if (pid < 0)
    { /* error occurred */
        fprintf(stderr, "Fork Failed\n");
        return 1;
    }
    else if (pid == 0)
    { /* child process */
        printf("I am the child %d\n", getpid());
        printf("%d ", collatz);
        while (collatz > 1)
        {
            if (collatz % 2 == 0)
            {
                collatz = collatz / 2;
            }
            else
            {
                collatz *= 3;
                collatz += 1;
            }
            printf("%d ", collatz);
        }
        printf("\n");
    }
    else
    { /* parent process */
        /* parent will wait for the child to complete */
        wait(NULL);
        printf("I am the parent %d\n", getpid());
    }
    return 0;
}
