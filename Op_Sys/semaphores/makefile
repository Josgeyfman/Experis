# makefile heap test unit

TARGET= semaphores.out
CC= gcc
CFLAGS= -ansi -g -pedantic -Wall -Werror 
OBJS= semaphores.o -lpthread

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)

semaphores.o: semaphores.c 
	$(CC) $(CFLAGS) -c semaphores.c

clean:
	rm -f $(TARGET) $(OBJS)
