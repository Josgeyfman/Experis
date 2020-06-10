# makefile list func test unit 
#-fno-stack-protector 

TARGET= listFuncTest.out
CC= gcc
CFLAGS= -ansi -g3 -pedantic -Wall -Werror -I../include 
OBJS= list.o listTestUnit.o myStruct.o list_functions.o

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)

list.o: ../list/list.c 
	$(CC) $(CFLAGS) -c ../list/list.c 

list_functions.o: list_functions.c 
	$(CC) $(CFLAGS) -c list_functions.c

listTestUnit.o: listTestUnit.c 
	$(CC) $(CFLAGS) -c listTestUnit.c

myStruct.o: ../myStruct.c
	$(CC) $(CFLAGS) -c ../myStruct.c

clean:
	rm -f $(TARGET) $(OBJS)
