#include <stdio.h>
#include <unistd.h> //for sysconf(), getpagesize()

int main(){
	long page_size = sysconf (_SC_PAGESIZE);

	printf("page size method 1=%ld\n", page_size);
	int page_size_i = getpagesize();

	printf("page size method 2=%d\n", page_size_i);


	return 0;
}
