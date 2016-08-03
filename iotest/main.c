#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

#define SIZE_BUF 1024

int main(){
  char buf[SIZE_BUF];
	ssize_t nr, nw;

	int fdr = open("test.txt", O_RDONLY);
	//int fdw = open("out.txt", O_WRONLY | O_EXCL | O_CREAT);
	int fdw = open("out.txt", 
			O_WRONLY | O_APPEND | O_CREAT);

	if (fdr == -1){
		/* error */
		printf("Error open file to read\n");
		return 0;
	}

	if(fdw == -1){
		/* error */
		printf("Error open file to write\n");
		return 0;
	}

	nr = read (fdr, buf, SIZE_BUF);
	nw = write (fdw, buf, nr);
	printf("%s\n",buf);	
	printf("fd = %d\n",fdr);

	close(fdr);
	close(fdw);

	return 0;

}
