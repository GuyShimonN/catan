# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -g -Wall -std=c++11 `pkg-config --cflags opencv4` -I/catan_1/image.jpeg
# Linker flags
LDFLAGS = `pkg-config --libs opencv4`

# Source files for the main application
MAIN_SRCS = main.cpp edge.cpp Game.cpp Board.cpp Player.cpp vertex.cpp Tile.cpp Road.cpp DevelopmentCard.cpp

# Source files for the tests
TEST_SRCS = Test.cpp edge.cpp Game.cpp Board.cpp Player.cpp vertex.cpp Tile.cpp Road.cpp DevelopmentCard.cpp

# Object files for the main application
MAIN_OBJS = $(MAIN_SRCS:.cpp=.o)

# Object files for the tests
TEST_OBJS = $(TEST_SRCS:.cpp=.o)

# Executable name for the main application
EXEC = catan

# Test executable name
TEST_EXEC = test_catan

# Valgrind options
VALGRIND_OPTS = --leak-check=full --show-leak-kinds=all

all: $(EXEC)

$(EXEC): $(MAIN_OBJS)
	$(CXX) $(CXXFLAGS) -o $(EXEC) $(MAIN_OBJS) $(LDFLAGS)

test: $(TEST_EXEC)

$(TEST_EXEC): $(TEST_OBJS)
	$(CXX) $(CXXFLAGS) -o $(TEST_EXEC) $(TEST_OBJS) $(LDFLAGS)
	./$(TEST_EXEC)

.cpp.o:
	$(CXX) $(CXXFLAGS) -c $<  -o $@

valgrind: $(EXEC)
	valgrind $(VALGRIND_OPTS) ./$(EXEC)

clean:
	rm -f *.o $(EXEC) $(TEST_EXEC)