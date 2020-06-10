# makefile heap test unit

TARGET= fork.out
CC= gcc
CFLAGS= -ansi -g -pedantic -Wall -Werror 
OBJS= fork.o 

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)

fork.o: fork.c 
	$(CC) $(CFLAGS) -c fork.c

clean:
	rm -f $(TARGET) $(OBJS)
