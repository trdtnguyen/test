#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <error.h>
#include <errno.h>
#include <string.h>

#define MAX_COUNT 1000
#define WAIT_TIME 3 //second
pthread_mutex_t count_lock;
pthread_cond_t count_cond = PTHREAD_COND_INITIALIZER;

int count; //shared variable

typedef struct _thread_data_t {
	int tid;
	int stuff;
} thread_data_t;


/*thread that wait 
 *(1) lock the mutex
 (2) use while loop to wait for signal
 (3) unlock the mutex
 (4) do work
 * */
void *thr_func1( void *arg) {
	thread_data_t* data = (thread_data_t*) arg;

	printf("Create thread %d\n", data->tid);
	pthread_mutex_lock(&count_lock);
	while (count < MAX_COUNT){
		pthread_cond_wait(&count_cond, &count_lock);
		printf("Reach here after wait\n");
	}	
	pthread_mutex_unlock(&count_lock);

	// Do your work here
	
	printf("Exit wait thread %d\n", data->tid);
	pthread_exit(NULL);
}

/*
 * Increase count from 0 to arg
 * If count >= a threashold then signal waiting thread
 * */
void *thr_func2(void *arg) {
	thread_data_t* data = (thread_data_t*) arg;
	int repeat = data->stuff;
	int i;
	
	printf("Create thread %d\n", data->tid);

	pthread_mutex_lock(&count_lock);
	/*some useful code here that modify shared var count */	
	for (i = 0; i < repeat; i++){
		count++;
		if ((i % (repeat / 10)) == 0){
			printf("i = %d\n", i);
		}
	}

	if (count >= MAX_COUNT) {
		pthread_mutex_unlock(&count_lock);
		pthread_cond_signal(&count_cond);
	} else {
		pthread_mutex_unlock(&count_lock);
	}
	
	printf("Exit signal thread %d\n", data->tid);
	pthread_exit(NULL);
}
/*
 * Wait for WAIT_TIME seconds, then signal waiting thread
 * */
void *thr_func3(void *arg) {
	thread_data_t* data = (thread_data_t*) arg;
	struct timespec t;
	struct timeval now;
	int ret;
	int wait_time = WAIT_TIME;

	printf("Create thread %d\n", data->tid);

	gettimeofday(&now, NULL);

	t.tv_sec = now.tv_sec + wait_time;

	printf("wait for %d seconds ...\n", wait_time);	
	pthread_mutex_lock(&count_lock);
	ret = pthread_cond_timedwait(&count_cond, &count_lock, &t);
	/* wait...*/
	pthread_mutex_unlock(&count_lock);

	if(ret < 0){
		perror("pthread_cond_timedwait");
		printf("error: %d\n", strerror(errno));
	}
	count = MAX_COUNT;
//	pthread_cond_signal(&count_cond);	
	pthread_cond_broadcast(&count_cond);

	printf("Exit wait-signal thread %d\n", data->tid);
	pthread_exit(NULL);
}

int main (int argc, char** argv){
#define NUM_THREADS  3
	pthread_t w_thr1, w_thr2, s_thr;
	thread_data_t thr_data[NUM_THREADS];
	int ret, i;
	int repeat = 3000;

	for (i=0; i < NUM_THREADS; i++){
		thr_data[i].tid = i;
	}
	pthread_mutex_init(&count_lock, NULL);
	
	ret = pthread_create(&w_thr1, NULL, thr_func1, &thr_data[0]);
	ret = pthread_create(&w_thr2, NULL, thr_func1, &thr_data[1]);
	if(ret){
		perror("pthread_create");
		return -1;
	}

	//ret = pthread_create(&s_thr, NULL, thr_func2, &repeat);
	thr_data[2].stuff = repeat;
	ret = pthread_create(&s_thr, NULL, thr_func3, &thr_data[2]);
	if(ret){
		perror("pthread_create");
		return -1;
	}
	pthread_join(w_thr1, NULL);
	pthread_join(w_thr2, NULL);
	pthread_join(s_thr, NULL);
	


	return EXIT_SUCCESS;
}
