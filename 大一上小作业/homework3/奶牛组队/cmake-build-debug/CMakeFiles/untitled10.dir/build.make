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
CMAKE_SOURCE_DIR = "/mnt/c/Users/lu'ren'jia'd's/CLionProjects/homework3/奶牛组队"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/mnt/c/Users/lu'ren'jia'd's/CLionProjects/homework3/奶牛组队/cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/untitled10.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/untitled10.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/untitled10.dir/flags.make

CMakeFiles/untitled10.dir/main.cpp.o: CMakeFiles/untitled10.dir/flags.make
CMakeFiles/untitled10.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/mnt/c/Users/lu'ren'jia'd's/CLionProjects/homework3/奶牛组队/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/untitled10.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/untitled10.dir/main.cpp.o -c "/mnt/c/Users/lu'ren'jia'd's/CLionProjects/homework3/奶牛组队/main.cpp"

CMakeFiles/untitled10.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/untitled10.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/mnt/c/Users/lu'ren'jia'd's/CLionProjects/homework3/奶牛组队/main.cpp" > CMakeFiles/untitled10.dir/main.cpp.i

CMakeFiles/untitled10.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/untitled10.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/mnt/c/Users/lu'ren'jia'd's/CLionProjects/homework3/奶牛组队/main.cpp" -o CMakeFiles/untitled10.dir/main.cpp.s

# Object files for target untitled10
untitled10_OBJECTS = \
"CMakeFiles/untitled10.dir/main.cpp.o"

# External object files for target untitled10
untitled10_EXTERNAL_OBJECTS =

untitled10: CMakeFiles/untitled10.dir/main.cpp.o
untitled10: CMakeFiles/untitled10.dir/build.make
untitled10: CMakeFiles/untitled10.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/mnt/c/Users/lu'ren'jia'd's/CLionProjects/homework3/奶牛组队/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable untitled10"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/untitled10.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/untitled10.dir/build: untitled10

.PHONY : CMakeFiles/untitled10.dir/build

CMakeFiles/untitled10.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/untitled10.dir/cmake_clean.cmake
.PHONY : CMakeFiles/untitled10.dir/clean

CMakeFiles/untitled10.dir/depend:
	cd "/mnt/c/Users/lu'ren'jia'd's/CLionProjects/homework3/奶牛组队/cmake-build-debug" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/mnt/c/Users/lu'ren'jia'd's/CLionProjects/homework3/奶牛组队" "/mnt/c/Users/lu'ren'jia'd's/CLionProjects/homework3/奶牛组队" "/mnt/c/Users/lu'ren'jia'd's/CLionProjects/homework3/奶牛组队/cmake-build-debug" "/mnt/c/Users/lu'ren'jia'd's/CLionProjects/homework3/奶牛组队/cmake-build-debug" "/mnt/c/Users/lu'ren'jia'd's/CLionProjects/homework3/奶牛组队/cmake-build-debug/CMakeFiles/untitled10.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/untitled10.dir/depend

