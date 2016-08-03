#include <stdio.h>

int main(int argc, char* argv[]){
	if(argc != 3){
		printf("Please input a, b\n");
		return 1;
	}
	int a = atoi(argv[1]);
	int b = atoi(argv[2]);
	
	int r1 = add( a, b );
	int r2= sub( a, b );

	printf("sum=%d, sub=%d\n", r1, r2);
	return 0;
}
