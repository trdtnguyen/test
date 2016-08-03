#include <stdio.h>

int f (int a, int b);

int main(){
	int a = 1;
	int *ip = &a;
	int b =2;

	*ip++;
	b = a + 2;
	int d = f(a, b);
	printf("value of d is %d\n", d);
	d++;
	int len = 16;
	int *arr = (int*) malloc (len * sizeof(int));
	arr[1] = 5;
	arr[3] = 7;

	return 0;
}

int f (int a, int b){
	int c = a + b;
	int d = a * b;
	return c + d;
}

