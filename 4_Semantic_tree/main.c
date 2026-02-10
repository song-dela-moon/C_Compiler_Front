#include <stdio.h>
#include <stdlib.h>
#include "type.h"

extern int syntax_err;
extern int semantic_err;
extern A_NODE *root;

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
		print_ast(root);
	}
	printf("[semantic analysis start]\n");
	semantic_analysis(root);
	if (semantic_err)
		exit(1);
	else
		print_sem_ast(root);
	exit(0);
}
