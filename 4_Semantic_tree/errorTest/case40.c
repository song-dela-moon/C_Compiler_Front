int main(){
	int i;
	float f;
	int result;
	int *ptri;
	float *ptrf;
	i = 1;
	f = 3.14;
	ptri=&i;
	ptrf=&f;
	result = (ptri<=ptrf);
}