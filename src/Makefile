#
# Makefile for the nofuss compiler. Copied from bug-free-enigme, and
# needs updating
#
basic_1: basic_1.c basic_1.h lexer.l parser.y
	bison -d parser.y
	flex -o lexer.lex.c lexer.l
	gcc -g -o $@ parser.tab.c lexer.lex.c basic_1.c

clean: 
	rm -rf basic_1
	rm -rf lexer.lex.c
	rm -rf parser.tab.c
	rm -rf parser.tab.h
