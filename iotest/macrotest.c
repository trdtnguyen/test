#include <stdio.h>

#define message_for(a, b) \
	printf(#a " and " #b ": Are received from params\n")

int main(){
	message_for(Dog, Cat);
	return 0;
}
