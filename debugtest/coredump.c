#include <stdio.h>

int f (int *p);

int main (){
	int *p = 0; //null pointer
	return f (p);
}

int f(int *p){
	int y = *p;
	return y;
}
