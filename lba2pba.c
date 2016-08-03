#include <stdio.h>
#include <stdlib.h>
#include <stdint.h> //for uint64_t
#include <inttypes.h> //for PRI64
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <linux/fs.h>
/*
 * * get_block - for the file associated with the given fd, returns
 * * the physical block mapping to logical_block
 * */
uint64_t get_block (int fd, uint64_t logical_block)
{
	int ret;
	ret = ioctl (fd, FIBMAP, &logical_block);
	if (ret < 0) {
		perror ("ioctl");
		return -1;
	}
	return logical_block;
}
/*
 * * get_nr_blocks - returns the number of logical blocks
 * * consumed by the file associated with fd
 * */
int get_nr_blocks (int fd)
{
	struct stat buf;
	int ret;
	ret = fstat (fd, &buf);
	if (ret < 0) {
		perror ("fstat");
		return -1;
	}
	return buf.st_blocks;
}
/*
 * * print_blocks - for each logical block consumed by the file
 * * associated with fd, prints to standard out the tuple
 * * "(logical block, physical block)"
 * */
void print_blocks (int fd)
{
	int nr_blocks, i;
	nr_blocks = get_nr_blocks (fd);
	if (nr_blocks < 0) {
		fprintf (stderr, "get_nr_blocks failed!\n");
		return;
	}
	if (nr_blocks == 0) {
		printf ("no allocated blocks\n");
		return;
	} else if (nr_blocks == 1)
		printf ("1 block\n\n");
	else
		printf ("%d blocks\n\n", nr_blocks);
	for (i = 0; i < nr_blocks; i++) {
		uint64_t phys_block;
		phys_block = get_block (fd, i);
		if (phys_block < 0) {
			fprintf (stderr, "get_block failed!\n");
			return;
		}
		if (i >= 15600){
			i = i + 1; //debug
			i = i - 1;
		}
		if (!phys_block)
			continue;
		printf ("%u %"PRIu64"\n ", i, phys_block);
	}
}
int main (int argc, char *argv[])
{
	int fd;
	if (argc < 2) {
		fprintf (stderr, "usage: %s <file>\n", argv[0]);
		return 1;
	}
	fd = open (argv[1], O_RDONLY);
	if (fd < 0) {
		perror ("open");
		return 1;

	}
	print_blocks (fd);
	return 0;
}
