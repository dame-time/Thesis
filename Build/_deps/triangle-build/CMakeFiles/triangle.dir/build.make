# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.22.3/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.22.3/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/davidepaollilo/Desktop/Workspace/C++/Thesis

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/davidepaollilo/Desktop/Workspace/C++/Thesis/build

# Include any dependencies generated for this target.
include _deps/triangle-build/CMakeFiles/triangle.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include _deps/triangle-build/CMakeFiles/triangle.dir/compiler_depend.make

# Include the progress variables for this target.
include _deps/triangle-build/CMakeFiles/triangle.dir/progress.make

# Include the compile flags for this target's objects.
include _deps/triangle-build/CMakeFiles/triangle.dir/flags.make

_deps/triangle-build/CMakeFiles/triangle.dir/triangle.cpp.o: _deps/triangle-build/CMakeFiles/triangle.dir/flags.make
_deps/triangle-build/CMakeFiles/triangle.dir/triangle.cpp.o: _deps/triangle-src/triangle.cpp
_deps/triangle-build/CMakeFiles/triangle.dir/triangle.cpp.o: _deps/triangle-build/CMakeFiles/triangle.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/davidepaollilo/Desktop/Workspace/C++/Thesis/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object _deps/triangle-build/CMakeFiles/triangle.dir/triangle.cpp.o"
	cd /Users/davidepaollilo/Desktop/Workspace/C++/Thesis/Build/_deps/triangle-build && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT _deps/triangle-build/CMakeFiles/triangle.dir/triangle.cpp.o -MF CMakeFiles/triangle.dir/triangle.cpp.o.d -o CMakeFiles/triangle.dir/triangle.cpp.o -c /Users/davidepaollilo/Desktop/Workspace/C++/Thesis/Build/_deps/triangle-src/triangle.cpp

_deps/triangle-build/CMakeFiles/triangle.dir/triangle.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/triangle.dir/triangle.cpp.i"
	cd /Users/davidepaollilo/Desktop/Workspace/C++/Thesis/Build/_deps/triangle-build && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/davidepaollilo/Desktop/Workspace/C++/Thesis/Build/_deps/triangle-src/triangle.cpp > CMakeFiles/triangle.dir/triangle.cpp.i

_deps/triangle-build/CMakeFiles/triangle.dir/triangle.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/triangle.dir/triangle.cpp.s"
	cd /Users/davidepaollilo/Desktop/Workspace/C++/Thesis/Build/_deps/triangle-build && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/davidepaollilo/Desktop/Workspace/C++/Thesis/Build/_deps/triangle-src/triangle.cpp -o CMakeFiles/triangle.dir/triangle.cpp.s

# Object files for target triangle
triangle_OBJECTS = \
"CMakeFiles/triangle.dir/triangle.cpp.o"

# External object files for target triangle
triangle_EXTERNAL_OBJECTS =

lib/libtriangle.a: _deps/triangle-build/CMakeFiles/triangle.dir/triangle.cpp.o
lib/libtriangle.a: _deps/triangle-build/CMakeFiles/triangle.dir/build.make
lib/libtriangle.a: _deps/triangle-build/CMakeFiles/triangle.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/davidepaollilo/Desktop/Workspace/C++/Thesis/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library ../../lib/libtriangle.a"
	cd /Users/davidepaollilo/Desktop/Workspace/C++/Thesis/Build/_deps/triangle-build && $(CMAKE_COMMAND) -P CMakeFiles/triangle.dir/cmake_clean_target.cmake
	cd /Users/davidepaollilo/Desktop/Workspace/C++/Thesis/Build/_deps/triangle-build && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/triangle.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
_deps/triangle-build/CMakeFiles/triangle.dir/build: lib/libtriangle.a
.PHONY : _deps/triangle-build/CMakeFiles/triangle.dir/build

_deps/triangle-build/CMakeFiles/triangle.dir/clean:
	cd /Users/davidepaollilo/Desktop/Workspace/C++/Thesis/Build/_deps/triangle-build && $(CMAKE_COMMAND) -P CMakeFiles/triangle.dir/cmake_clean.cmake
.PHONY : _deps/triangle-build/CMakeFiles/triangle.dir/clean

_deps/triangle-build/CMakeFiles/triangle.dir/depend:
	cd /Users/davidepaollilo/Desktop/Workspace/C++/Thesis/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/davidepaollilo/Desktop/Workspace/C++/Thesis /Users/davidepaollilo/Desktop/Workspace/C++/Thesis/Build/_deps/triangle-src /Users/davidepaollilo/Desktop/Workspace/C++/Thesis/build /Users/davidepaollilo/Desktop/Workspace/C++/Thesis/Build/_deps/triangle-build /Users/davidepaollilo/Desktop/Workspace/C++/Thesis/Build/_deps/triangle-build/CMakeFiles/triangle.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : _deps/triangle-build/CMakeFiles/triangle.dir/depend

