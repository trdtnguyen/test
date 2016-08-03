#include <stdio.h>
#include <stdlib.h>
#include "add.h"
#include "sub.h"
#include "mul.h"
#include "div.h"

int main(int argc, char* argv[]){
	if(argc != 3){
		printf("Please input a, b\n");
		return 1;
	}
	int a = atoi(argv[1]);
	int b = atoi(argv[2]);

	int r1 = add(a, b);
	int r2 = sub(a, b);
	int r3 = mul(a, b);
	int r4 = div1(a, b);

	printf("add(a,b)=%d\n", r1);
	printf("sub(a,b)=%d\n", r2);
	printf("mul(a,b)=%d\n", r3);
	printf("div(a,b)=%d\n", r4);
	return 0;
}

