#include <stdio.h>
#include <stdlib.h>
#include "type.h"

extern int syntax_err;
extern int semantic_err;
extern int gen_err;

extern A_NODE *root;
FILE *fout;

void initialize();
void semantic_analysis();

void print_ast();
void print_sem_ast();

void main(int argc, char *argv[]){
	initialize();
	yyparse();	
	printf("[syntax analysis start]\n");
	if (syntax_err)
		 exit(1);
	else {
		//printf("*** syntax analysis Done with no error\n\n");
		//print_ast(root);
	}
	printf("[semantic analysis start]\n");
	semantic_analysis(root);
	if (semantic_err)
		exit(1);
	else
		//print_sem_ast(root);
	if ((fout=fopen("a.asm","w+")) == NULL) {
		printf("can not open output file: a.asm\n"); 
		exit(1);
	}
	printf("[code generation start]\n");
	code_generation(root);
	if (gen_err)
		exit(1);
	exit(0);
}
