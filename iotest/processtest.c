#include <stdio.h>
#include <unistd.h> /* for process system calls*/

int main(){
	printf ("The pid is %d\n", (int) getpid());
	printf ("The ppid is %d\n", (int) getppid());
	return 0;
}
