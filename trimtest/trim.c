#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <fcntl.h> //for Open flags
#include <limits.h> //for ULLONG_MAX
#include <sys/ioctl.h>
#include <unistd.h>
#include <linux/fs.h> //for fstrim_range
#include <string.h>
#include <errno.h>


#define UNIT 1024
int main (void){
	struct fstrim_range range;
	int ret, fd, fd_read;
		
	char buf1[UNIT] = "ABCD";
	char buf2[UNIT] = "EFGH";
	char buf_out[UNIT];

		
	fd = open("/tmp/foo2.txt", O_WRONLY|O_CREAT, 0644);
	//fd = open("/tmp/foo2.txt", O_RDWR|O_CREAT, 0644);
	
	/*1st write*/	
	ret = pwrite(fd, buf1, sizeof(buf1), 0);
	if (ret < 0){
		perror("pwrite");
		return -1;	
	}
	/*2nd write*/
	ret = pwrite(fd, buf2, sizeof(buf2), UNIT*10);
	if (ret < 0){
		perror("pwrite");
		return -1;	
	}

	ret = fsync(fd);
	if (ret < 0) {
		perror("fsync");
		return -1;
	}

	range.start = 0;
	range.len = ULLONG_MAX;
	
	ret = ioctl(fd, FITRIM, &range);
	if (ret < 0){
		perror("ioctl");
		return -1;
	}

	close(fd);

	fd_read = open("/tmp/foo2.txt", O_RDONLY);
	ret = pread(fd_read, buf_out, sizeof(buf1), 0);
	if (ret < 0) {
		perror("pread");
		printf("errno=%d\n", errno);
	}
    printf("buf_out=%s\n", buf_out);	
   
	close(fd_read);	

	return 0;
}
