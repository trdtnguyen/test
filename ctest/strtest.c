#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]){
	const char *p = "ABC";
//	printf("1. val =%s\n", p);

//	*p++;
	p++;
	printf("2. val =%s\n", p);
	printf("%c\n",*p);
	return 0;
}
