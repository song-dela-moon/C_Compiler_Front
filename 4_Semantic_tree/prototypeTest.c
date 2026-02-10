#include <stdio.h>

void hello();

void hello(int i, int j){
	printf("hello to %d\n",i);
	printf("hello to %d\n",j);
}
int main(){
	int i=1;
	int j=2;
	hello(i,j);
	return 0;
}
