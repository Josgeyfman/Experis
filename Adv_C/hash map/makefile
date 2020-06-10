# makefile hash map test unit 
#-fno-stack-protector 

TARGET= hashTestUnit.out
CC= gcc
CFLAGS= -ansi -g3 -pedantic -Wall -Werror  -I../include 
OBJS= hash.o hashTestUnit.o list.o myStruct.o list_functions.o -lm

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)

hash.o: hash.c 
	$(CC) $(CFLAGS) -c hash.c

hashTestUnit.o: hashTestUnit.c 
	$(CC) $(CFLAGS) -c hashTestUnit.c

list.o: ../list/list.c 
	$(CC) $(CFLAGS) -c ../list/list.c

list_functions.o: ../listFunctions/list_functions.c 
	$(CC) $(CFLAGS) -c ../listFunctions/list_functions.c

myStruct.o: ../myStruct.c 
	$(CC) $(CFLAGS) -c ../myStruct.c

clean:
	rm -f $(TARGET) $(OBJS)
