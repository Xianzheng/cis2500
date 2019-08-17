CC=gcc
GFLAGS=-Wall -ansi
fleschIndex : fleschIndex.o
	$(CC) -o fleschIndex fleschIndex.o

fleschIndex.o : fleschIndex.c
	$(CC) $(CFLAGS) -c fleschIndex.c
clean :
	rm fleschIndex fleschIndex.o
