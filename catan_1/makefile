CC = g++
CFLAGS = -Wall -std=c++11

OBJS = main.o Board.o Player.o vertex.o Tile.o edge.o Building.o Road.o DevelopmentCard.o

catan: $(OBJS)
	$(CC) $(CFLAGS) -o catan $(OBJS)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o catan