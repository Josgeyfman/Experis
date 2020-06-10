# makefile hash test unit 
#-fno-stack-protector 

TARGET= hashTest.out
CC= gcc
CFLAGS= -ansi -g3 -pedantic -Wall -Werror  -I../include 
OBJS= hash.o hashTestUnit.o -lm

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)

hash.o: hash.c 
	$(CC) $(CFLAGS) -c hash.c

hashTestUnit.o: hashTestUnit.c 
	$(CC) $(CFLAGS) -c hashTestUnit.c

clean:
	rm -f $(TARGET) $(OBJS)
