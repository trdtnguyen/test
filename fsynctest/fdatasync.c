/* Test if write(2) blocks when an fdatasync() in the same file is in progress
 ** in another thread.
 **
 ** Compile with: gcc fdatasync.c -Wall -W -O2 -lpthread -o fdatasynctest
 **
 ** For feedbacks drop an email to antirez at gmail
 **/

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/time.h>
#include <stdlib.h>

static long long microseconds(void) {
	struct timeval tv;
	long long mst;

	gettimeofday(&tv, NULL);
	mst = ((long long)tv.tv_sec)*1000000;
	mst += tv.tv_usec;
	return mst;
}

void *IOThreadEntryPoint(void *arg) {
	int fd, retval;
	long long start;
	arg = arg;

	while(1) {
		start = microseconds();
		fd = open("/tmp/foo.txt",O_RDONLY);
		retval = fdatasync(fd);
		close(fd);
		printf("Sync in %lld microseconds (%d)\n", microseconds()-start,retval);
		usleep(1000000);
	}
	return NULL;
}

int main(void) {
	pthread_t thread;
	int fd = open("/tmp/foo.txt",O_WRONLY|O_CREAT,0644);
	long long start;

	pthread_create(&thread,NULL,IOThreadEntryPoint,NULL);
	while(1) {
		start = microseconds();
		if (write(fd,"x",1) == -1) {
			perror("write");
			exit(1);
		}
		printf("Write in %lld microseconds\n", microseconds()-start);
		usleep(100000);
	}
	close(fd);
	exit(0);
}
