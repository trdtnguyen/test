#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 16 

typedef struct _thread_data_t {
	int tid;
	double stuff;
} thread_data_t;

/* shared data between threads */
int shared_x;
pthread_mutex_t lock_x;

/* thread function */
void* thread_func(void *arg) {
	thread_data_t* data = (thread_data_t*) arg;

	/*acquire the lock and release after modifying shared data*/
	pthread_mutex_lock(&lock_x);
		printf("In thread_func, thread id: %d\n", data->tid);
		shared_x += data->stuff;
		printf("shared_x=%d\n", shared_x);
	pthread_mutex_unlock(&lock_x);

	pthread_exit(NULL);
}

int main(int argc, char** argv){
	pthread_t thr[NUM_THREADS];
	int i, rc;
	/* create a thread_data_t arugment array */
	thread_data_t thr_data[NUM_THREADS];

	/* initialize shared data */
	shared_x = 0;

	/* initialize pthread mutex*/
	pthread_mutex_init(&lock_x, NULL);
	

	/* create threads */
	for (i = 0; i < NUM_THREADS; i++){
		thr_data[i].tid = i;
		thr_data[i].stuff = i + 1;

		if ((rc = pthread_create(&thr[i], NULL, thread_func, &thr_data[i]))){
			fprintf(stderr, "error: pthread_create, rc: %d\n", rc);
			return EXIT_FAILURE;
		}
	}
	
	/* block until all threads complete */
	for (i = 0; i < NUM_THREADS; ++i){
		pthread_join(thr[i], NULL);
	}
	return EXIT_SUCCESS;
}
