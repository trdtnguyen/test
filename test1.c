#include <stdio.h>
#include <stdlib.h>


#define MAX(A,B) ( (A > B) ? A : B )

typedef enum {MON, TUE, WED, THU, FRI, SAT, SUN} days_t ;

int main(int argc, char* argv[]){
	days_t day = WED;
	printf("%d\n", day);
	return 0;
}
