int fun(int);

int fun(int a){
	int b = 1;
	b = a + b;
	return b;
}
int main(){
	int a = 1;
	int b;
	b=fun(a);
	printf("%d",b);
	return 0;
}
	
