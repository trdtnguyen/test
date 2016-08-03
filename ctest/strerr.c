#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


FILE *open_sesame (char *name);

int main(int argc, char *argv[]){
	if(argc != 2){
		printf("Wrong parameter. Usage:<input_file>\n");
		return -1;
	}
	FILE *fp = open_sesame(argv[1]);
	printf("End program.\n");
	return 0;
}

FILE *open_sesame (char *name)
{
	FILE *stream;
	errno = 0;
	stream = fopen (name, "r");
	if (stream == NULL)
	{
		fprintf (stderr, "Error: Couldn't open file %s; %s\n",
				name, strerror (errno));
		exit (EXIT_FAILURE);
	}
	else
		return stream;
}

