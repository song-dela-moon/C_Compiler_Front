int func(int **); // abstract declarator
// pointer가 한번만 출력 됨
int main(){
	int** a;
	int* p;
	a=&p;
}
