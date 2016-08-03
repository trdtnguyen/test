#include <stdio.h>
#include <errno.h>
#include <string.h>

extern int errno;

int main(){
	FILE *fp;
	int errnum;

	fp = fopen("notexistfile.txt", "rb");
	if (fp == NULL){
		errnum = errno;
		fprintf(stderr, "Value of errno: %d\n", errno);
		perror("Error pritned by perror");
		fprintf(stderr, "Error open file: %s\n", strerror(errnum));
	}
	else{
		fclose(fp);
	}

	return 0;
}
