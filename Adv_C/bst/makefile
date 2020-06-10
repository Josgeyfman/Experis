# makefile bst test unit 
#-fno-stack-protector 

TARGET= bstTest.out
CC= gcc
CFLAGS= -ansi -g3 -pedantic -Wall -Werror -I../include 
OBJS= bst.o bstUnitTest.o 

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)

bst.o: bst.c 
	$(CC) $(CFLAGS) -c bst.c

bstUnitTest.o: bstUnitTest.c 
	$(CC) $(CFLAGS) -c bstUnitTest.c

clean:
	rm -f $(TARGET) $(OBJS)
