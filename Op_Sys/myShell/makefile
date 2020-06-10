# makefile heap test unit

TARGET= myShell.out
CC= gcc
CFLAGS= -ansi -g -pedantic -Wall -Werror 
OBJS= myShell.o 

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)

myShell.o: myShell.c 
	$(CC) $(CFLAGS) -c myShell.c

clean:
	rm -f $(TARGET) $(OBJS)
