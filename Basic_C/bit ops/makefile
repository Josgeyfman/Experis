# makefile bitops3
#-fno-stack-protector 

TARGET= bitops3.out
CC= gcc
CFLAGS= -ansi -g3 -pedantic -Wall -Werror  -I../include 
OBJS= bitops3.o -lm

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)

bitops3.o: bitops3.c 
	$(CC) $(CFLAGS) -c bitops3.c

clean:
	rm -f $(TARGET) $(OBJS)
