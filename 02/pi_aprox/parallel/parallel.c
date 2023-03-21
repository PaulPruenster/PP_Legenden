#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <omp.h>

#define NUM_THREADS 8

long n = 700000000;
int count[NUM_THREADS];

void *approximate_pi_parallel(void *thread_id)
{
    int id = *(int *)thread_id;
    int start = id * (n / NUM_THREADS);
    int end = (id + 1) * (n / NUM_THREADS);
    int local_count = 0;
    double x, y;

    for (int i = start; i < end; i++)
    {
        x = (double)rand() / RAND_MAX;
        y = (double)rand() / RAND_MAX;
        if (x * x + y * y <= 1.0)
        {
            local_count++;
        }
    }

    count[id] = local_count;

    pthread_exit(NULL);
}

int main()
{
    double startTime = omp_get_wtime();

    srand(time(NULL));

    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS];
    for (int i = 0; i < NUM_THREADS; i++)
    {
        thread_ids[i] = i;
        int rc = pthread_create(&threads[i], NULL, approximate_pi_parallel, (void *)&thread_ids[i]);
        if (rc)
        {
            fprintf(stderr, "Error: return code from pthread_create() is %d\n", rc);
            exit(EXIT_FAILURE);
        }
    }

    for (int i = 0; i < NUM_THREADS; i++)
    {
        pthread_join(threads[i], NULL);
    }

    // calculate total count
    int total_count = 0;
    for (int i = 0; i < NUM_THREADS; i++) 
        total_count += count[i];

    // calculate Pi
    double pi = 4.0 * total_count / n;
    printf("Approximate value of pi: %f\n", pi);

    double endTime = omp_get_wtime();
	printf("time: %2.4f seconds\n", endTime-startTime);
    return 0;
}
