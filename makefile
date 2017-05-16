a.out : hw1.l
	lex hw1.l
	g++ lex.yy.c
	
