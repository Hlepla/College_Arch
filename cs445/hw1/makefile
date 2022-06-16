all: g0

lex.yy.c: clex.l main.c ytab.h linked.h
	flex clex.l

g0: lex.yy.c
	gcc lex.yy.c -g -o g0

clean:
	rm lex.yy.c
