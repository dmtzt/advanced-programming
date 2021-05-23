/*
 * Multiprocessing pthreads
 * Computes the row sum of a matrix in parallel using the pthreads library
 * David Alejandro Martinez Tristan
 * A01610267
 * 
*/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#define MATRIX_SIZE 5

/*
 * Function used by all threads
 * Receives pointer to beginning of each row to compute sum of all of its values
 * Prints all added values and result
*/
void* threadFunction(void* arg)
{
    int* row = (int*) arg;
    int sum = row[0];

    printf("%i", row[0]);

    for (int i = 1; i < MATRIX_SIZE; i++)
    {
        printf(" + %i", row[i]);
        sum += row[i];
    }
        
    printf(" = %i\n", sum);
    return NULL;
}

int main()
{
    // Create matrix
    int matrix[MATRIX_SIZE][MATRIX_SIZE];
    // Create thread array
    pthread_t thread_array[MATRIX_SIZE];

    // Fill matrix
    for (int i = 0; i < MATRIX_SIZE; i++)
        for (int j = 0; j < MATRIX_SIZE; j++)
            matrix[i][j] = (rand() % 10 + 1);

    // Compute row sum in parallel
    for (int i = 0; i < MATRIX_SIZE; i++)
    {
        printf("Sum from thread %i: ", i);
        pthread_create(&thread_array[i], NULL, threadFunction, (void*) matrix[i]);
        pthread_join(thread_array[i], NULL);
    }

    return 0;
}