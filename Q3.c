// File   : Q3.c
// Author : John Holik
// Class  : COP4610
// Desc   : In FGCU parking lot there are limited spaces. Cars (drivers) arrive throughout the day trying to find a
//          spot. Once a car parks, it stays for a certain amount of time before leaving, freeing up a spot for the next car.
//****************************************************************************************************************//

#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

sem_t parkingSpots;
int numOfParkingSpots = 5; // Number of parking spots
int availableSpots;        // Var to track available parking spots
void parking(void* arg){
    int carId = *((int *)arg);
    printf("Car %d arriving. Available spots: %d\n", carId, availableSpots);

    // Wait for open parking spot
    sem_wait(&parkingSpots);
    availableSpots--;
    printf("Car %d parked. Available spots: %d\n", carId, availableSpots);

    // Simulate amount of time parked
    int parkTime = (rand() % (5 - 3 + 1)) + 3; // Range: 3 to 5 seconds
    sleep(parkTime) ;


    // Leave parking spot
    printf("Car %d leaving. Available spots: %d\n", carId, availableSpots + 1);
    availableSpots++;
    sem_post(&parkingSpots);

    return NULL;
}


// Main
//****************************************************************************************************************//
int main(){
    // Initialize Counting Semaphore to the number of parking spots
    sem_init(&parkingSpots, 0, numOfParkingSpots);
    availableSpots = numOfParkingSpots; // Initialize available spots
    // Generate a random number of cars that want to park, ranging from 6->10
    srand(time(NULL)); // Use the current time as the seed
    int numOfCars = (rand() % (10 - 6 + 1)) + 6; // Range: 6 to 10
    
    // Create Car Threads
    pthread_t cars[numOfCars];
    for (int i = 0; i < numOfCars; i++)
    {
        int *carId = malloc(sizeof(int));
        *carId = i + 1; // Car IDs start from 1
        pthread_create(&cars[i], NULL, parking, carId);
    } // end Car thread creation

    // Wait for all cars to park
    for (int i = 0; i < numOfCars; i++)
    {
        pthread_join(cars[i], NULL);
    }

    sem_destroy(&parkingSpots); // Clean up semaphore

    return 0;
}// end main