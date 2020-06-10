# makefile sample

TARGET= hearts.out
CC= gcc
CFLAGS= -ansi -g -Wall -Werror -Iinclude
OBJS= deck.o player.o ui.o round.o game.o main.o log.o

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)

deck.o: deck.c 
	$(CC) $(CFLAGS) -c deck.c
	
player.o: player.c 
	$(CC) $(CFLAGS) -c player.c

ui.o: ui.c 
	$(CC) $(CFLAGS) -c ui.c

round.o: round.c 
	$(CC) $(CFLAGS) -c round.c

game.o: game.c 
	$(CC) $(CFLAGS) -c game.c

main.o: main.c 
	$(CC) $(CFLAGS) -c main.c
	
log.o: log.c 
	$(CC) $(CFLAGS) -c log.c
clean:
	rm -f $(TARGET) $(OBJS)
