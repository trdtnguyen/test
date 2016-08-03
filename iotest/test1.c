#include <stdio.h>
#include <unistd.h> //for sysconf()

int main(){
	long page_size = sysconf (_SC_PAGESIZE);

	printf("page size method1=%ld\n", page_size);
	return 0;
}
