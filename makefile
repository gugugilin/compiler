a1.out : hw1.l hw3.y
	yacc hw3.y -d -v
	lex hw1.l
	yacc hw3.y -d -v
	g++ y.tab.c -o a1.out -std=c++11
