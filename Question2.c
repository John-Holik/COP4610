// File   : Question2.c
// Author : John Holik
// Class  : COP4610
// Desc   : Using multithreading in order to preform various mathematical computations on numbers provided via CLI

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Global Vars
//****************************************************************************************************************//
int RANGE     = 0;
double STD_DEV = 0;
double INTQ_R    = 0;

int *nums;
int count;

// Functions
//****************************************************************************************************************//

void *find_range(void *arg){
    RANGE = nums[count-1] - nums[0];
    pthread_exit(0);
} // end of find_range


void *find_std_dev(void *arg){
    // find sum
    int sum = 0;
    for(int i = 0; i < count; i++){
        sum += nums[i];
    } // end of sum
    double mean = sum / count;

    // find varience 
    double varience = 0;
    for(int i = 0; i < count; i++){
        varience += pow(nums[i]- mean,2);
    } // end of varience
    varience = varience / count;

    STD_DEV = sqrt(varience);
    pthread_exit(0);
} // end of find_std_dev


void *find_intq_r(void *arg){
    int q1_index = count / 4; // q1 is at the 25% mark of the array
    int q3_index = (count * 3) / 4; // q3 is at the 75% mark of the array
    double q1 = 0;
    double q3 = 0;
    if(count % 4 == 0){
        q1 = (nums[q1_index] + nums[q1_index - 1]) / 2.0;
        q3 = (nums[q3_index] + nums[q3_index - 1]) / 2.0;
    } else{
        q1 = nums[q1_index];
        q3 = nums[q3_index];
    }

    INTQ_R = q3 - q1;
    pthread_exit(0);
} // end of find_intq_r



// Used for qsort()
int compare(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
} // end of compare


// Main
//****************************************************************************************************************//
int main(int argc, char *argv[])
{     

    // error checking
//****************************************************************************************************************//
    if (argc < 2){
        fprintf(stderr, "usage: %s <list of numbers>\n", argv[0]);
        return -1;
    } // end of error checking
    
    // Create Array
//****************************************************************************************************************//
    count  = argc - 1; // argv[0] is the name of the program

    nums = (int*)malloc(count * sizeof(int)); // dyanmically allocate array size based off the amount of numbers provided

    // Transform string numbers provided into ints and implement into array
    for(int i = 0; i < count; i++){
        nums[i] = atoi(argv[i+1]);
    }

    qsort(nums, count, sizeof(int), compare);
/* ***Testing if array is working***
    for(int i = 0; i < count; i++){
        printf("%d", nums[i]);
        printf(" %d", i);
        printf("\n");
    }
*/

    // create threads
//****************************************************************************************************************//
    pthread_t rangeThread, stdDevThread, intqRThread;

    pthread_create(&rangeThread,NULL,find_range, NULL);
    pthread_create(&stdDevThread, NULL, find_std_dev, NULL);
    pthread_create(&intqRThread, NULL, find_intq_r, NULL);

    // Wait for thread to finish
    pthread_join(rangeThread, NULL);
    pthread_join(stdDevThread, NULL);
    pthread_join(intqRThread, NULL);

    // print output 
    printf("The range value is %d\n", RANGE);
    printf("The standard deviation is = %.2f\n", STD_DEV);
    printf("The interquartile range is = %.2f\n", INTQ_R);

}