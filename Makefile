# this is my target
TARGET = StackUnitTest.out

# The compiler will be gcc("CC" is MAKE variable)
CC = gcc

# General compilation flags

# The compiler flags will be... ("CFLAGS" is MAKE variable)
CFLAGS = -ansi -pedantic -Wall -Werror 
# The debugger flags will be... ("LDFLAGS" is MAKE variable)
LDFLAGS = -g

# Include directorys  
# for each additional include add 
# INC_DIRx  and CFLAGS += -I$(INC_DIRx)
INC_DIR1 = ../vector
CFLAGS += -I$(INC_DIR1)
#INC_DIR12 = ../Stack
#CFLAGS += -I$(INC_DIR2)


# All .c files in this directory are my sources
SOURCES = StackUnitTest.c Stack.c ../vector/vector.c
# All .o files in this directory are my objects
OBJECTS = $(SOURCES:.c=.o)

# The default command, compile all the sources
$(TARGET): $(OBJECTS) 
	$(CC) $(OBJECTS) -o $(TARGET)  

#build dependency roule for ech file  in SOURCES  
StackUnitTest.o: StackUnitTest.c stack.h 
	$(CC) -c StackUnitTest.c

Stack.o: stack.c stack.h ../vector.h
	$(CC) -c stack.c

Vector.o: ../vector/vector.c ../vector.h
	$(CC) -c ../vector/vector.c.c

clean:
	-rm $(TARGET) *.o 

run:  $(TARGET)
	 ./$(TARGET)

gdb:  $(TARGET)
	 gdb -q ./$(TARGET)
	  
	
