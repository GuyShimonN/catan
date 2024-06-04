# Variables
CXX = g++
CXXFLAGS = -Wall -std=c++11
OBJS = main.o Board.o Player.o vertex.o Tile.o edge.o
TARGET = catan

# Default target
all: $(TARGET)

# Linking target
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Object files
main.o: main.cpp Board.h catan.hpp
	$(CXX) $(CXXFLAGS) -c main.cpp -o main.o

Board.o: Board.cpp Board.h Tile.h vertex.h edge.h
	$(CXX) $(CXXFLAGS) -c Board.cpp -o Board.o

Player.o: Player.cpp Player.hpp Resource.hpp Building.h Road.h DevelopmentCard.h
	$(CXX) $(CXXFLAGS) -c Player.cpp -o Player.o



vertex.o: vertex.cpp vertex.h Tile.h edge.h
	$(CXX) $(CXXFLAGS) -c vertex.cpp -o vertex.o

Tile.o: Tile.cpp Tile.h vertex.h edge.h
	$(CXX) $(CXXFLAGS) -c Tile.cpp -o Tile.o

edge.o: edge.cpp edge.h
	$(CXX) $(CXXFLAGS) -c edge.cpp -o edge.o

# Clean up build files
clean:
	rm -f $(TARGET) $(OBJS)

# Phony targets
.PHONY: all clean
