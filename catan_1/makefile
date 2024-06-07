# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -g -Wall -std=c++11 `pkg-config --cflags opencv4` -I/catan_1/image.jpeg
# Linker flags
LDFLAGS = `pkg-config --libs opencv4`

# Source files
SRCS = main.cpp edge.cpp Game.cpp Board.cpp Player.cpp vertex.cpp Tile.cpp Building.cpp Road.cpp DevelopmentCard.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# Executable name
EXEC = catan

# Valgrind options
VALGRIND_OPTS = --leak-check=full --show-leak-kinds=all

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(EXEC) $(OBJS) $(LDFLAGS)

.cpp.o:
	$(CXX) $(CXXFLAGS) -c $<  -o $@

valgrind: $(EXEC)
	valgrind $(VALGRIND_OPTS) ./$(EXEC)

clean:
	rm -f *.o $(EXEC)