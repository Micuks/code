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
CMAKE_SOURCE_DIR = /home/micuks/code/OOP_Practise/practice3

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/micuks/code/OOP_Practise/practice3/build

# Include any dependencies generated for this target.
include src/Shape/CMakeFiles/Shape.dir/depend.make

# Include the progress variables for this target.
include src/Shape/CMakeFiles/Shape.dir/progress.make

# Include the compile flags for this target's objects.
include src/Shape/CMakeFiles/Shape.dir/flags.make

src/Shape/CMakeFiles/Shape.dir/Shape.cpp.o: src/Shape/CMakeFiles/Shape.dir/flags.make
src/Shape/CMakeFiles/Shape.dir/Shape.cpp.o: ../src/Shape/Shape.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/micuks/code/OOP_Practise/practice3/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/Shape/CMakeFiles/Shape.dir/Shape.cpp.o"
	cd /home/micuks/code/OOP_Practise/practice3/build/src/Shape && /usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Shape.dir/Shape.cpp.o -c /home/micuks/code/OOP_Practise/practice3/src/Shape/Shape.cpp

src/Shape/CMakeFiles/Shape.dir/Shape.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Shape.dir/Shape.cpp.i"
	cd /home/micuks/code/OOP_Practise/practice3/build/src/Shape && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/micuks/code/OOP_Practise/practice3/src/Shape/Shape.cpp > CMakeFiles/Shape.dir/Shape.cpp.i

src/Shape/CMakeFiles/Shape.dir/Shape.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Shape.dir/Shape.cpp.s"
	cd /home/micuks/code/OOP_Practise/practice3/build/src/Shape && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/micuks/code/OOP_Practise/practice3/src/Shape/Shape.cpp -o CMakeFiles/Shape.dir/Shape.cpp.s

# Object files for target Shape
Shape_OBJECTS = \
"CMakeFiles/Shape.dir/Shape.cpp.o"

# External object files for target Shape
Shape_EXTERNAL_OBJECTS =

src/Shape/libShape.a: src/Shape/CMakeFiles/Shape.dir/Shape.cpp.o
src/Shape/libShape.a: src/Shape/CMakeFiles/Shape.dir/build.make
src/Shape/libShape.a: src/Shape/CMakeFiles/Shape.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/micuks/code/OOP_Practise/practice3/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libShape.a"
	cd /home/micuks/code/OOP_Practise/practice3/build/src/Shape && $(CMAKE_COMMAND) -P CMakeFiles/Shape.dir/cmake_clean_target.cmake
	cd /home/micuks/code/OOP_Practise/practice3/build/src/Shape && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Shape.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/Shape/CMakeFiles/Shape.dir/build: src/Shape/libShape.a

.PHONY : src/Shape/CMakeFiles/Shape.dir/build

src/Shape/CMakeFiles/Shape.dir/clean:
	cd /home/micuks/code/OOP_Practise/practice3/build/src/Shape && $(CMAKE_COMMAND) -P CMakeFiles/Shape.dir/cmake_clean.cmake
.PHONY : src/Shape/CMakeFiles/Shape.dir/clean

src/Shape/CMakeFiles/Shape.dir/depend:
	cd /home/micuks/code/OOP_Practise/practice3/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/micuks/code/OOP_Practise/practice3 /home/micuks/code/OOP_Practise/practice3/src/Shape /home/micuks/code/OOP_Practise/practice3/build /home/micuks/code/OOP_Practise/practice3/build/src/Shape /home/micuks/code/OOP_Practise/practice3/build/src/Shape/CMakeFiles/Shape.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/Shape/CMakeFiles/Shape.dir/depend

