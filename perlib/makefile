
# makefile Periodic Executor shared library

#2 log.o time_funcs.o task.o per_exe.o heap.o vector.o
#3 gcc -shared -o libper_exe.so log.o time_funcs.o task.o per_exe.o heap.o vector.o
#4 LD_LIBRARY_PATH=$LD_LIBRARY_PATH:.
#5 export LD_LIBRARY_PATH
#6 gcc -ansi -g3 -Wall -Werror -Iinclude -lrt -std=gnu99 main.c -o main.out -L. -lper_exe

TARGET = main.out
TARGET1= perexecTest.out
TARGET2= taskTest.out
TARGET3= timeFuncsTest.out

CC= gcc
CFLAGS= -ansi -g3 -Wall -Werror -Iinclude -lrt -std=gnu99
OBJS=main.o log.o time_funcs.o task.o per_exe.o heap.o vector.o
OBJS1=perexecTestUnit.o log.o time_funcs.o task.o per_exe.o heap.o vector.o
OBJS2=taskTestUnit.o  time_funcs.o task.o
OBJS3=timeFuncsTestUnit.o time_funcs.o 

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)

perexecTest : $(OBJS1)
	$(CC) -o $(TARGET1) $(OBJS1)

taskTest: $(OBJS2)
	$(CC) -o $(TARGET2) $(OBJS2)

timeTest: $(OBJS3)
	$(CC) -o $(TARGET3) $(OBJS3)

vector.o: vector.c 
	$(CC) $(CFLAGS) -fPIC -c vector.c

heap.o: heap.c 
	$(CC) $(CFLAGS) -fPIC -c heap.c 
	
per_exe.o: per_exe.c 
	$(CC) $(CFLAGS) -fPIC -c per_exe.c

task.o: task.c 
	$(CC) $(CFLAGS) -fPIC -c task.c

time_funcs.o: time_funcs.c 
	$(CC) $(CFLAGS) -fPIC -c time_funcs.c

log.o: log.c 
	$(CC) $(CFLAGS) -fPIC -c log.c

main.o: main.c 
	$(CC) $(CFLAGS) -c main.c

perexecTestUnit.o: perexecTestUnit.c 
	$(CC) $(CFLAGS) -c perexecTestUnit.c

taskTestUnit.o: taskTestUnit.c 
	$(CC) $(CFLAGS) -c taskTestUnit.c

timeFuncsTestUnit.o: timeFuncsTestUnit.c 
	$(CC) $(CFLAGS) -c timeFuncsTestUnit.c

clean:
	rm -f $(TARGET) $(OBJS)
	rm -f $(TARGET1) $(OBJS1)
	rm -f $(TARGET2) $(OBJS2)
	rm -f $(TARGET3) $(OBJS3)
