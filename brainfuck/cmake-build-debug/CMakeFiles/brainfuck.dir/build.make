# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
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
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/mnt/c/Users/lu'ren'jia'd's/CLionProjects/brainfuck"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/mnt/c/Users/lu'ren'jia'd's/CLionProjects/brainfuck/cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/brainfuck.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/brainfuck.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/brainfuck.dir/flags.make

CMakeFiles/brainfuck.dir/interpreter.c.o: CMakeFiles/brainfuck.dir/flags.make
CMakeFiles/brainfuck.dir/interpreter.c.o: ../interpreter.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/mnt/c/Users/lu'ren'jia'd's/CLionProjects/brainfuck/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/brainfuck.dir/interpreter.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/brainfuck.dir/interpreter.c.o   -c "/mnt/c/Users/lu'ren'jia'd's/CLionProjects/brainfuck/interpreter.c"

CMakeFiles/brainfuck.dir/interpreter.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/brainfuck.dir/interpreter.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/mnt/c/Users/lu'ren'jia'd's/CLionProjects/brainfuck/interpreter.c" > CMakeFiles/brainfuck.dir/interpreter.c.i

CMakeFiles/brainfuck.dir/interpreter.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/brainfuck.dir/interpreter.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/mnt/c/Users/lu'ren'jia'd's/CLionProjects/brainfuck/interpreter.c" -o CMakeFiles/brainfuck.dir/interpreter.c.s

# Object files for target brainfuck
brainfuck_OBJECTS = \
"CMakeFiles/brainfuck.dir/interpreter.c.o"

# External object files for target brainfuck
brainfuck_EXTERNAL_OBJECTS =

brainfuck: CMakeFiles/brainfuck.dir/interpreter.c.o
brainfuck: CMakeFiles/brainfuck.dir/build.make
brainfuck: CMakeFiles/brainfuck.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/mnt/c/Users/lu'ren'jia'd's/CLionProjects/brainfuck/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable brainfuck"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/brainfuck.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/brainfuck.dir/build: brainfuck

.PHONY : CMakeFiles/brainfuck.dir/build

CMakeFiles/brainfuck.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/brainfuck.dir/cmake_clean.cmake
.PHONY : CMakeFiles/brainfuck.dir/clean

CMakeFiles/brainfuck.dir/depend:
	cd "/mnt/c/Users/lu'ren'jia'd's/CLionProjects/brainfuck/cmake-build-debug" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/mnt/c/Users/lu'ren'jia'd's/CLionProjects/brainfuck" "/mnt/c/Users/lu'ren'jia'd's/CLionProjects/brainfuck" "/mnt/c/Users/lu'ren'jia'd's/CLionProjects/brainfuck/cmake-build-debug" "/mnt/c/Users/lu'ren'jia'd's/CLionProjects/brainfuck/cmake-build-debug" "/mnt/c/Users/lu'ren'jia'd's/CLionProjects/brainfuck/cmake-build-debug/CMakeFiles/brainfuck.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/brainfuck.dir/depend

