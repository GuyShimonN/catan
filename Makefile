# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

# Default target executed when no arguments are given to make.
default_target: all
.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/guy/CLionProjects/CPP_EX3_24-main/Catan

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/guy/CLionProjects/CPP_EX3_24-main/Catan/build

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "No interactive CMake dialog available..."
	/usr/bin/cmake -E echo No\ interactive\ CMake\ dialog\ available.
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache
.PHONY : edit_cache/fast

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/bin/cmake --regenerate-during-build -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache
.PHONY : rebuild_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /home/guy/CLionProjects/CPP_EX3_24-main/Catan/build/CMakeFiles /home/guy/CLionProjects/CPP_EX3_24-main/Catan/build//CMakeFiles/progress.marks
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /home/guy/CLionProjects/CPP_EX3_24-main/Catan/build/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean
.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named Catan

# Build rule for target.
Catan: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 Catan
.PHONY : Catan

# fast build rule for target.
Catan/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Catan.dir/build.make CMakeFiles/Catan.dir/build
.PHONY : Catan/fast

src/Board.o: src/Board.cpp.o
.PHONY : src/Board.o

# target to build an object file
src/Board.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Catan.dir/build.make CMakeFiles/Catan.dir/src/Board.cpp.o
.PHONY : src/Board.cpp.o

src/Board.i: src/Board.cpp.i
.PHONY : src/Board.i

# target to preprocess a source file
src/Board.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Catan.dir/build.make CMakeFiles/Catan.dir/src/Board.cpp.i
.PHONY : src/Board.cpp.i

src/Board.s: src/Board.cpp.s
.PHONY : src/Board.s

# target to generate assembly for a file
src/Board.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Catan.dir/build.make CMakeFiles/Catan.dir/src/Board.cpp.s
.PHONY : src/Board.cpp.s

src/Game.o: src/Game.cpp.o
.PHONY : src/Game.o

# target to build an object file
src/Game.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Catan.dir/build.make CMakeFiles/Catan.dir/src/Game.cpp.o
.PHONY : src/Game.cpp.o

src/Game.i: src/Game.cpp.i
.PHONY : src/Game.i

# target to preprocess a source file
src/Game.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Catan.dir/build.make CMakeFiles/Catan.dir/src/Game.cpp.i
.PHONY : src/Game.cpp.i

src/Game.s: src/Game.cpp.s
.PHONY : src/Game.s

# target to generate assembly for a file
src/Game.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Catan.dir/build.make CMakeFiles/Catan.dir/src/Game.cpp.s
.PHONY : src/Game.cpp.s

src/Tile.o: src/Tile.cpp.o
.PHONY : src/Tile.o

# target to build an object file
src/Tile.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Catan.dir/build.make CMakeFiles/Catan.dir/src/Tile.cpp.o
.PHONY : src/Tile.cpp.o

src/Tile.i: src/Tile.cpp.i
.PHONY : src/Tile.i

# target to preprocess a source file
src/Tile.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Catan.dir/build.make CMakeFiles/Catan.dir/src/Tile.cpp.i
.PHONY : src/Tile.cpp.i

src/Tile.s: src/Tile.cpp.s
.PHONY : src/Tile.s

# target to generate assembly for a file
src/Tile.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Catan.dir/build.make CMakeFiles/Catan.dir/src/Tile.cpp.s
.PHONY : src/Tile.cpp.s

src/main.o: src/main.cpp.o
.PHONY : src/main.o

# target to build an object file
src/main.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Catan.dir/build.make CMakeFiles/Catan.dir/src/main.cpp.o
.PHONY : src/main.cpp.o

src/main.i: src/main.cpp.i
.PHONY : src/main.i

# target to preprocess a source file
src/main.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Catan.dir/build.make CMakeFiles/Catan.dir/src/main.cpp.i
.PHONY : src/main.cpp.i

src/main.s: src/main.cpp.s
.PHONY : src/main.s

# target to generate assembly for a file
src/main.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Catan.dir/build.make CMakeFiles/Catan.dir/src/main.cpp.s
.PHONY : src/main.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... edit_cache"
	@echo "... rebuild_cache"
	@echo "... Catan"
	@echo "... src/Board.o"
	@echo "... src/Board.i"
	@echo "... src/Board.s"
	@echo "... src/Game.o"
	@echo "... src/Game.i"
	@echo "... src/Game.s"
	@echo "... src/Tile.o"
	@echo "... src/Tile.i"
	@echo "... src/Tile.s"
	@echo "... src/main.o"
	@echo "... src/main.i"
	@echo "... src/main.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

