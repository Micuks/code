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
CMAKE_SOURCE_DIR = /home/micuks/code/OOP_Practise/practice5.2

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/micuks/code/OOP_Practise/practice5.2/build

# Include any dependencies generated for this target.
include src/Point/CMakeFiles/Point.dir/depend.make

# Include the progress variables for this target.
include src/Point/CMakeFiles/Point.dir/progress.make

# Include the compile flags for this target's objects.
include src/Point/CMakeFiles/Point.dir/flags.make

src/Point/CMakeFiles/Point.dir/Point.cpp.o: src/Point/CMakeFiles/Point.dir/flags.make
src/Point/CMakeFiles/Point.dir/Point.cpp.o: ../src/Point/Point.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/micuks/code/OOP_Practise/practice5.2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/Point/CMakeFiles/Point.dir/Point.cpp.o"
	cd /home/micuks/code/OOP_Practise/practice5.2/build/src/Point && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Point.dir/Point.cpp.o -c /home/micuks/code/OOP_Practise/practice5.2/src/Point/Point.cpp

src/Point/CMakeFiles/Point.dir/Point.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Point.dir/Point.cpp.i"
	cd /home/micuks/code/OOP_Practise/practice5.2/build/src/Point && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/micuks/code/OOP_Practise/practice5.2/src/Point/Point.cpp > CMakeFiles/Point.dir/Point.cpp.i

src/Point/CMakeFiles/Point.dir/Point.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Point.dir/Point.cpp.s"
	cd /home/micuks/code/OOP_Practise/practice5.2/build/src/Point && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/micuks/code/OOP_Practise/practice5.2/src/Point/Point.cpp -o CMakeFiles/Point.dir/Point.cpp.s

# Object files for target Point
Point_OBJECTS = \
"CMakeFiles/Point.dir/Point.cpp.o"

# External object files for target Point
Point_EXTERNAL_OBJECTS =

src/Point/libPoint.a: src/Point/CMakeFiles/Point.dir/Point.cpp.o
src/Point/libPoint.a: src/Point/CMakeFiles/Point.dir/build.make
src/Point/libPoint.a: src/Point/CMakeFiles/Point.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/micuks/code/OOP_Practise/practice5.2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libPoint.a"
	cd /home/micuks/code/OOP_Practise/practice5.2/build/src/Point && $(CMAKE_COMMAND) -P CMakeFiles/Point.dir/cmake_clean_target.cmake
	cd /home/micuks/code/OOP_Practise/practice5.2/build/src/Point && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Point.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/Point/CMakeFiles/Point.dir/build: src/Point/libPoint.a

.PHONY : src/Point/CMakeFiles/Point.dir/build

src/Point/CMakeFiles/Point.dir/clean:
	cd /home/micuks/code/OOP_Practise/practice5.2/build/src/Point && $(CMAKE_COMMAND) -P CMakeFiles/Point.dir/cmake_clean.cmake
.PHONY : src/Point/CMakeFiles/Point.dir/clean

src/Point/CMakeFiles/Point.dir/depend:
	cd /home/micuks/code/OOP_Practise/practice5.2/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/micuks/code/OOP_Practise/practice5.2 /home/micuks/code/OOP_Practise/practice5.2/src/Point /home/micuks/code/OOP_Practise/practice5.2/build /home/micuks/code/OOP_Practise/practice5.2/build/src/Point /home/micuks/code/OOP_Practise/practice5.2/build/src/Point/CMakeFiles/Point.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/Point/CMakeFiles/Point.dir/depend

