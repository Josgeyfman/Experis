# makefile heap test unit

TARGET= heapTest.out
CC= gcc
CFLAGS= -ansi -g -pedantic -Wall -Werror -I../include 
OBJS= heap.o heapTestUnit.o vector.o

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)

vector.o: ../vector/vector.c 
	$(CC) $(CFLAGS) -c ../vector/vector.c

heap.o: heap.c 
	$(CC) $(CFLAGS) -c heap.c
	
heapTestUnit.o: heapTestUnit.c 
	$(CC) $(CFLAGS) -c heapTestUnit.c

clean:
	rm -f $(TARGET) $(OBJS)
