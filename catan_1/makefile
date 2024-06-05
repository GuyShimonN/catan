# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -g -Wall -std=c++11

# Source files
SRCS = main.cpp edge.cpp Game.cpp Board.cpp Player.cpp vertex.cpp Tile.cpp Building.cpp Road.cpp DevelopmentCard.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# Executable name
EXEC = catan

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(EXEC) $(OBJS)

.cpp.o:
	$(CXX) $(CXXFLAGS) -c $<  -o $@

clean:
	rm -f *.o $(EXEC)