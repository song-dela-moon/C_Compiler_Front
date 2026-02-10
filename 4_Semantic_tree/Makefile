a.out : y.tab.c lex.yy.c
	gcc y.tab.c lex.yy.c print.c main.c semantic1.c print_sem.c -m32 -w -g

y.tab.c : song.y
	yacc -d song.y

lex.yy.c : song.l
	lex song.l
