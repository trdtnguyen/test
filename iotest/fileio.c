#include <stdio.h>
#include <stdlib.h>

#define MAX_BUF			1024

int main(int argc, char *argv[]){
	FILE *ifp;

	char *buf = malloc(100);
	int val;

	ifp = fopen ("input.txt", "r+");

	if (ifp == NULL){
		fprintf(stderr, "Can't open the input file\n");
		exit(1);
	}

	int i = 0;
	while ( fscanf(ifp, "%s %d", buf, &val) != EOF) {
		printf("Line %d: %s %d\n",i++, buf, val);
	}

	return 0;
}
