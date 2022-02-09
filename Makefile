CC=gcc
CFLAGS=-Wall -g
CINPUTFILE=src/input/input-text 
CGRAMMARFILE=src/input/grammar-definer
COUTPUTFILE=src/input/output-file

all: slap
	clear
	./bin/slap.out $(CINPUTFILE) $(CGRAMMARFILE) $(COUTPUTFILE)
#	@make clean -s

slap: main.o gram.o
	$(CC) $(CFLAGS) bin/main.o bin/gram.o -o bin/slap.out

main.o: src/main.c
	$(CC) $(CFLAGS) -c src/main.c -o bin/main.o

gram.o: src/gram.c
	$(CC) $(CFLAGS) -c src/gram.c -o bin/gram.o

clean:
	@rm bin/main.o bin/gram.o bin/slap