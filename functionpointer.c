#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int cmp1(int a, int b){
	if(a > b)
		return 1;
	else if(a < b)
		return -1;
	else 
		return 0;
}
int cmp2(int a, int b){
	return -cmp1(a, b);
}
typedef int (*cmpfunc) (int a, int b);

int generalcmp(int a, int b, cmpfunc cmp){
	return cmp(a, b);
}

int main(int argc, char** argv){
	int a = atoi(argv[1]);
	int b = atoi(argv[2]);

	int res = generalcmp(a, b, cmp2);

	printf("%d\n", res);	
	return 0;
}
