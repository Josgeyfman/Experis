# makefile mymalloc
#-fno-stack-protector 

TARGET= mymalloc.out
CC= gcc
CFLAGS= -ansi -g3 -pedantic -Wall -Werror -I../include 
OBJS= mymalloc.o mymallocTestUnit.o 

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)

mymalloc.o: mymalloc.c 
	$(CC) $(CFLAGS) -c mymalloc.c

mymallocTestUnit.o: mymallocTestUnit.c 
	$(CC) $(CFLAGS) -c mymallocTestUnit.c

clean:
	rm -f $(TARGET) $(OBJS)
