CC=gcc
CFLAGS=-Wall -g
CINPUTFILE=src/input/input-text 
CGRAMMARFILE=src/input/grammar-definer
COUTPUTFILE=src/input/output-file

all: slap
	clear
	./bin/slap.out $(CINPUTFILE) $(CGRAMMARFILE) $(COUTPUTFILE)
#	@make clean -s
# 	I needed to clean up directories when I was compiling and working in the parent folder, but now I can just keep it in the bin folder

genrules: gram.o token.o
	gcc -g -c src/genrules.c -o bin/genrules.o
	gcc -g bin/genrules.o bin/gram.o bin/token.o -o bin/genrules.out

slap: main.o gram.o token.o
	$(CC) $(CFLAGS) bin/main.o bin/gram.o bin/token.o -o bin/slap.out

main.o: src/main.c
	$(CC) $(CFLAGS) -c src/main.c -o bin/main.o

gram.o: src/gram.c
	$(CC) $(CFLAGS) -c src/gram.c -o bin/gram.o

token.o: src/token.c
	$(CC) $(CFLAGS) -c src/token.c -o bin/token.o

clean:
	@rm bin/main.o bin/gram.o bin/slap