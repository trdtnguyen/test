#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <error.h>
#include <string.h>
#include <errno.h>

/*
 *use pthread_cond_timedwait to force current thread wait for x seconds
 * */
#define WAIT_TIME 3 //second

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

int main(void) {
	struct timespec t;
	struct timeval now;
	int ret;
	int wait_time = 5; //second
	gettimeofday(&now, NULL);

	t.tv_sec = now.tv_sec + wait_time;
	
	printf("wait for %d seconds ...\n", wait_time);	
	pthread_mutex_lock(&mutex);
	ret = pthread_cond_timedwait(&cond, &mutex, &t);
	pthread_mutex_unlock(&mutex);
	
	if(ret < 0){
		perror("pthread_cond_timedwait");
		printf("error: %s\n", strerror(errno));
		return -1;
	}
	printf("Done. ret=%d\n", ret);

	return 0;
}
