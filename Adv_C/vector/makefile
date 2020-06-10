# makefile vector test unit

TARGET= vecTest.out
CC= gcc
CFLAGS= -ansi -g3 -pedantic -Wall -Werror -I../include
OBJS= vector.o vectorTestUnit.o myStruct.o

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)

vector.o: vector.c 
	$(CC) $(CFLAGS) -c vector.c
	
vectorTestUnit.o: vectorTestUnit.c 
	$(CC) $(CFLAGS) -c vectorTestUnit.c

myStruct.o: ../myStruct.c 
	$(CC) $(CFLAGS) -c ../myStruct.c

clean:
	rm -f $(TARGET) $(OBJS)
