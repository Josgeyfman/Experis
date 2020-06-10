# makefile heap test unit

TARGET= pthread.out
CC= gcc
CFLAGS= -ansi -g -pedantic -Wall -Werror 
OBJS= pthread.o -lpthread

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)

pthread.o: pthread.c 
	$(CC) $(CFLAGS) -c pthread.c

clean:
	rm -f $(TARGET) $(OBJS)
