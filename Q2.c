// File   : Q2.c
// Author : John Holik
// Class  : COP4610
// Desc   : In a bustling coffee shop, there are five baristas who need access to three shared coffee machines to
//          make coffee for customers. Baristas can only make coffee if they have exclusive access to all three
//          coffee machines.


#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

// Define mutex locks for the three coffee machines
//****************************************************************************************************************//
pthread_mutex_t leftMachine = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t centerMachine = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t rightMachine = PTHREAD_MUTEX_INITIALIZER;


// Barista function to make coffee
//****************************************************************************************************************//
void *barista(void *arg)
{
    int id = *(int *)arg; // Barista ID

    printf("Barista %d is waiting for machines.\n", id);

    // Acquire locks for all three machines (left, center, right)
    pthread_mutex_lock(&leftMachine);
    pthread_mutex_lock(&centerMachine);
    pthread_mutex_lock(&rightMachine);

    // Now the barista has access to all machines
    printf("Barista %d has acquired all machines and is making coffee.\n", id);
    sleep(2); // Simulate time taken to make coffee

    // Release the locks after making coffee
    pthread_mutex_unlock(&rightMachine);
    pthread_mutex_unlock(&centerMachine);
    pthread_mutex_unlock(&leftMachine);

    printf("Barista %d has finished making coffee and released the machines.\n", id);

    return NULL;
}// end barista



// Main
//****************************************************************************************************************//
int main()
{
    // Create an array of 5 threads
    pthread_t baristas[5];
    int baristaIds[5];

    // Create threads representing 5 baristas
    for (int i = 0; i < 5; i++)
    {
        baristaIds[i] = i + 1;
        pthread_create(&baristas[i], NULL, barista, &baristaIds[i]);
    }

    // Wait for all baristas to finish
    for (int i = 0; i < 5; i++)
    {
        pthread_join(baristas[i], NULL);
    }

    return 0;
} // end main
