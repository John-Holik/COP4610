// File   : Q2.c
// Author : John Holik
// Class  : COP4610
// Desc   : In a bustling coffee shop, there are five baristas who need access to three shared coffee machines to
//          make coffee for customers. Baristas can only make coffee if they have exclusive access to all three
//          coffee machines.

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_BARISTAS 5
#define NUM_MACHINES 3

sem_t machines[NUM_MACHINES]; // Semaphores for each machine
pthread_mutex_t print_mutex; // Mutex for outputting


int main() {
    pthread_t baristaThread[NUM_BARISTAS];

    for(int i = 0; i < NUM_MACHINES; i++){ // Create machines and have them unlocked
        sem_init(&machines[i], 0, 1);
    }



    return 0;
}