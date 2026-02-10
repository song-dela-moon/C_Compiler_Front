//Incomplete_Definition_Forward_Reference
void func(int, float, int);
int main(int argc, char *argv[]){
	int a, c;
	float b;
	func(a, b, c);
	return 0;
}

void func(int a, float b, int c) {
	func(a, b, c);
}