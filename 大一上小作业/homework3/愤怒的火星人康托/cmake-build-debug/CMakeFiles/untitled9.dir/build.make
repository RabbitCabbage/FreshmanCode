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
CMAKE_SOURCE_DIR = "/mnt/c/Users/lu'ren'jia'd's/CLionProjects/untitled9"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/mnt/c/Users/lu'ren'jia'd's/CLionProjects/untitled9/cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/untitled9.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/untitled9.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/untitled9.dir/flags.make

CMakeFiles/untitled9.dir/main.cpp.o: CMakeFiles/untitled9.dir/flags.make
CMakeFiles/untitled9.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/mnt/c/Users/lu'ren'jia'd's/CLionProjects/untitled9/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/untitled9.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/untitled9.dir/main.cpp.o -c "/mnt/c/Users/lu'ren'jia'd's/CLionProjects/untitled9/main.cpp"

CMakeFiles/untitled9.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/untitled9.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/mnt/c/Users/lu'ren'jia'd's/CLionProjects/untitled9/main.cpp" > CMakeFiles/untitled9.dir/main.cpp.i

CMakeFiles/untitled9.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/untitled9.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/mnt/c/Users/lu'ren'jia'd's/CLionProjects/untitled9/main.cpp" -o CMakeFiles/untitled9.dir/main.cpp.s

# Object files for target untitled9
untitled9_OBJECTS = \
"CMakeFiles/untitled9.dir/main.cpp.o"

# External object files for target untitled9
untitled9_EXTERNAL_OBJECTS =

untitled9: CMakeFiles/untitled9.dir/main.cpp.o
untitled9: CMakeFiles/untitled9.dir/build.make
untitled9: CMakeFiles/untitled9.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/mnt/c/Users/lu'ren'jia'd's/CLionProjects/untitled9/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable untitled9"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/untitled9.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/untitled9.dir/build: untitled9

.PHONY : CMakeFiles/untitled9.dir/build

CMakeFiles/untitled9.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/untitled9.dir/cmake_clean.cmake
.PHONY : CMakeFiles/untitled9.dir/clean

CMakeFiles/untitled9.dir/depend:
	cd "/mnt/c/Users/lu'ren'jia'd's/CLionProjects/untitled9/cmake-build-debug" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/mnt/c/Users/lu'ren'jia'd's/CLionProjects/untitled9" "/mnt/c/Users/lu'ren'jia'd's/CLionProjects/untitled9" "/mnt/c/Users/lu'ren'jia'd's/CLionProjects/untitled9/cmake-build-debug" "/mnt/c/Users/lu'ren'jia'd's/CLionProjects/untitled9/cmake-build-debug" "/mnt/c/Users/lu'ren'jia'd's/CLionProjects/untitled9/cmake-build-debug/CMakeFiles/untitled9.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/untitled9.dir/depend

