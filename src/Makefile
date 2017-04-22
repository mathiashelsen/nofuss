#
# Makefile for the nofuss compiler. Copied from bug-free-enigme, and
# needs updating
#
# Declaration of variables
CC = gcc
CC_FLAGS = -w
 
# File names
EXEC = nofuss
SOURCES = $(wildcard *.c)
OBJECTS = $(SOURCES:.c=.o)
 
# Main target
$(EXEC): $(OBJECTS) lexer.l parser.y
	bison -d parser.y
	flex -o lexer.lex.c lexer.l
	$(CC) $(OBJECTS) -o $(EXEC)
 
# To obtain object files
%.o: %.c
	$(CC) -c $(CC_FLAGS) $< -o $@
 
# To remove generated files
clean:
	rm -f $(EXEC) $(OBJECTS)

