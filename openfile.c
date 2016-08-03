#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main () {
	int fd;
	fd = open("",O_RDONLY );
	prinf("%d",fd);
	return 0;
}
