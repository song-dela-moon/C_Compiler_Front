//struct_definition
struct person {
	char name;
	int age;
	struct person *line; 
};
struct person song;
struct person *p=&song;
void main(int argc, char *argv[]){
		song.age = 23;
		p->name='s';
		printf("%c, %d\n", p->name, song.age);
}		
