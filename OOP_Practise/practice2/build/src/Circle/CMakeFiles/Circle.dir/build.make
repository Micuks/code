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
CMAKE_SOURCE_DIR = /home/micuks/code/OOP_Practise/practice2

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/micuks/code/OOP_Practise/practice2/build

# Include any dependencies generated for this target.
include src/Circle/CMakeFiles/Circle.dir/depend.make

# Include the progress variables for this target.
include src/Circle/CMakeFiles/Circle.dir/progress.make

# Include the compile flags for this target's objects.
include src/Circle/CMakeFiles/Circle.dir/flags.make

src/Circle/CMakeFiles/Circle.dir/Circle.cpp.o: src/Circle/CMakeFiles/Circle.dir/flags.make
src/Circle/CMakeFiles/Circle.dir/Circle.cpp.o: ../src/Circle/Circle.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/micuks/code/OOP_Practise/practice2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/Circle/CMakeFiles/Circle.dir/Circle.cpp.o"
	cd /home/micuks/code/OOP_Practise/practice2/build/src/Circle && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Circle.dir/Circle.cpp.o -c /home/micuks/code/OOP_Practise/practice2/src/Circle/Circle.cpp

src/Circle/CMakeFiles/Circle.dir/Circle.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Circle.dir/Circle.cpp.i"
	cd /home/micuks/code/OOP_Practise/practice2/build/src/Circle && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/micuks/code/OOP_Practise/practice2/src/Circle/Circle.cpp > CMakeFiles/Circle.dir/Circle.cpp.i

src/Circle/CMakeFiles/Circle.dir/Circle.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Circle.dir/Circle.cpp.s"
	cd /home/micuks/code/OOP_Practise/practice2/build/src/Circle && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/micuks/code/OOP_Practise/practice2/src/Circle/Circle.cpp -o CMakeFiles/Circle.dir/Circle.cpp.s

# Object files for target Circle
Circle_OBJECTS = \
"CMakeFiles/Circle.dir/Circle.cpp.o"

# External object files for target Circle
Circle_EXTERNAL_OBJECTS =

src/Circle/libCircle.a: src/Circle/CMakeFiles/Circle.dir/Circle.cpp.o
src/Circle/libCircle.a: src/Circle/CMakeFiles/Circle.dir/build.make
src/Circle/libCircle.a: src/Circle/CMakeFiles/Circle.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/micuks/code/OOP_Practise/practice2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libCircle.a"
	cd /home/micuks/code/OOP_Practise/practice2/build/src/Circle && $(CMAKE_COMMAND) -P CMakeFiles/Circle.dir/cmake_clean_target.cmake
	cd /home/micuks/code/OOP_Practise/practice2/build/src/Circle && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Circle.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/Circle/CMakeFiles/Circle.dir/build: src/Circle/libCircle.a

.PHONY : src/Circle/CMakeFiles/Circle.dir/build

src/Circle/CMakeFiles/Circle.dir/clean:
	cd /home/micuks/code/OOP_Practise/practice2/build/src/Circle && $(CMAKE_COMMAND) -P CMakeFiles/Circle.dir/cmake_clean.cmake
.PHONY : src/Circle/CMakeFiles/Circle.dir/clean

src/Circle/CMakeFiles/Circle.dir/depend:
	cd /home/micuks/code/OOP_Practise/practice2/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/micuks/code/OOP_Practise/practice2 /home/micuks/code/OOP_Practise/practice2/src/Circle /home/micuks/code/OOP_Practise/practice2/build /home/micuks/code/OOP_Practise/practice2/build/src/Circle /home/micuks/code/OOP_Practise/practice2/build/src/Circle/CMakeFiles/Circle.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/Circle/CMakeFiles/Circle.dir/depend

