# makefile 
#make lib steps
#1 make a.o
#2 make b.o
#3 make ar cr libstat.a a.o b.o
#4 make gcc -ansi -g -pedantic -Wall -Werror main.c -o main.out -L. -lstat

TARGET= main.out
CC= gcc
CFLAGS= -ansi -g3 -pedantic -Wall -Werror -L. -lstat
OBJS  = main.o 

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)

main.o: main.c 
	$(CC) $(CFLAGS) -c main.c

b.o: b.c 
	$(CC) $(CFLAGS) -c b.c

a.o: a.c 
	$(CC) $(CFLAGS) -c a.c

clean:
	rm -f $(TARGET) $(OBJS)


