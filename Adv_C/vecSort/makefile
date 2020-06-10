# makefile sample

TARGET= vecSort.out
CC= gcc
CFLAGS= -ansi -g -pedantic -Wall -Werror -I../include
OBJS= vector.o vecSort.o sortMain.o

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)

vector.o: vector.c 
	$(CC) $(CFLAGS) -c vector.c
	
vecSort.o: vecSort.c 
	$(CC) $(CFLAGS) -c vecSort.c

sortMain.o: sortMain.c 
	$(CC) $(CFLAGS) -c sortMain.c

clean:
	rm -f $(TARGET) $(OBJS)
