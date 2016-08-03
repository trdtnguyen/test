#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
	printf("Main program pid=%d\n", (int) getpid());

	int child_pid = fork();
	if (child_pid != 0){
		printf ("this is parent pid=%d\n", (int) getpid());
		printf("this is child id=%d\n", child_pid);
	}
	return 0;
}
