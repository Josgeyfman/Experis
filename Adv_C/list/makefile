# makefile list test unit 
#-fno-stack-protector 

TARGET= listTest.out
CC= gcc
CFLAGS= -ansi -g3 -pedantic -Wall -Werror -I../include 
OBJS= list.o listTestUnit.o myStruct.o

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)

list.o: list.c 
	$(CC) $(CFLAGS) -c list.c

listTestUnit.o: listTestUnit.c 
	$(CC) $(CFLAGS) -c listTestUnit.c

myStruct.o: ../myStruct.c
	$(CC) $(CFLAGS) -c ../myStruct.c

clean:
	rm -f $(TARGET) $(OBJS)
