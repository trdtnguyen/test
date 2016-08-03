#include <stdio.h>

typedef struct List_ {
	struct List_ *next;
	int data;
} List;

int main(int argc, const char* argv[]) {
	List l;
	l.data = 1;

	printf("%d\n", l.data);
	return 0;
} 
