# makefile 
#make dynamic lib steps
#1 make a.o
#2 make b.o
#3 make gcc -shared -o libtest.so a.o b.o 
#4 make LD_LIBRARY_PATH=$LD_LIBRARY_PATH:.
#5 make export LD_LIBRARY_PATH
#6 make gcc -ansi -g -pedantic -Wall -Werror main.c -o main.out -L. -ltest

TARGET= main.out
CC= gcc
CFLAGS= -ansi -g -pedantic -Wall -Werror -L. -ltest
OBJS  = main.o 

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)

main.o: main.c 
	$(CC) $(CFLAGS) -c main.c

b.o: b.c 
	$(CC) $(CFLAGS) -fPIC -c b.c

a.o: a.c 
	$(CC) $(CFLAGS) -fPIC -c a.c

clean:
	rm -f $(TARGET) $(OBJS)


