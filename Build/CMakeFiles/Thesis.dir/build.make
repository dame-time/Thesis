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
include CMakeFiles/Thesis.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/Thesis.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/Thesis.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Thesis.dir/flags.make

CMakeFiles/Thesis.dir/Core/src/Mesh.cpp.o: CMakeFiles/Thesis.dir/flags.make
CMakeFiles/Thesis.dir/Core/src/Mesh.cpp.o: ../Core/src/Mesh.cpp
CMakeFiles/Thesis.dir/Core/src/Mesh.cpp.o: CMakeFiles/Thesis.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/davidepaollilo/Desktop/Workspace/C++/Thesis/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Thesis.dir/Core/src/Mesh.cpp.o"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Thesis.dir/Core/src/Mesh.cpp.o -MF CMakeFiles/Thesis.dir/Core/src/Mesh.cpp.o.d -o CMakeFiles/Thesis.dir/Core/src/Mesh.cpp.o -c /Users/davidepaollilo/Desktop/Workspace/C++/Thesis/Core/src/Mesh.cpp

CMakeFiles/Thesis.dir/Core/src/Mesh.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Thesis.dir/Core/src/Mesh.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/davidepaollilo/Desktop/Workspace/C++/Thesis/Core/src/Mesh.cpp > CMakeFiles/Thesis.dir/Core/src/Mesh.cpp.i

CMakeFiles/Thesis.dir/Core/src/Mesh.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Thesis.dir/Core/src/Mesh.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/davidepaollilo/Desktop/Workspace/C++/Thesis/Core/src/Mesh.cpp -o CMakeFiles/Thesis.dir/Core/src/Mesh.cpp.s

CMakeFiles/Thesis.dir/Math/Matrix/src/Matrix2.cpp.o: CMakeFiles/Thesis.dir/flags.make
CMakeFiles/Thesis.dir/Math/Matrix/src/Matrix2.cpp.o: ../Math/Matrix/src/Matrix2.cpp
CMakeFiles/Thesis.dir/Math/Matrix/src/Matrix2.cpp.o: CMakeFiles/Thesis.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/davidepaollilo/Desktop/Workspace/C++/Thesis/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/Thesis.dir/Math/Matrix/src/Matrix2.cpp.o"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Thesis.dir/Math/Matrix/src/Matrix2.cpp.o -MF CMakeFiles/Thesis.dir/Math/Matrix/src/Matrix2.cpp.o.d -o CMakeFiles/Thesis.dir/Math/Matrix/src/Matrix2.cpp.o -c /Users/davidepaollilo/Desktop/Workspace/C++/Thesis/Math/Matrix/src/Matrix2.cpp

CMakeFiles/Thesis.dir/Math/Matrix/src/Matrix2.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Thesis.dir/Math/Matrix/src/Matrix2.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/davidepaollilo/Desktop/Workspace/C++/Thesis/Math/Matrix/src/Matrix2.cpp > CMakeFiles/Thesis.dir/Math/Matrix/src/Matrix2.cpp.i

CMakeFiles/Thesis.dir/Math/Matrix/src/Matrix2.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Thesis.dir/Math/Matrix/src/Matrix2.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/davidepaollilo/Desktop/Workspace/C++/Thesis/Math/Matrix/src/Matrix2.cpp -o CMakeFiles/Thesis.dir/Math/Matrix/src/Matrix2.cpp.s

CMakeFiles/Thesis.dir/Math/Matrix/src/Matrix3.cpp.o: CMakeFiles/Thesis.dir/flags.make
CMakeFiles/Thesis.dir/Math/Matrix/src/Matrix3.cpp.o: ../Math/Matrix/src/Matrix3.cpp
CMakeFiles/Thesis.dir/Math/Matrix/src/Matrix3.cpp.o: CMakeFiles/Thesis.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/davidepaollilo/Desktop/Workspace/C++/Thesis/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/Thesis.dir/Math/Matrix/src/Matrix3.cpp.o"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Thesis.dir/Math/Matrix/src/Matrix3.cpp.o -MF CMakeFiles/Thesis.dir/Math/Matrix/src/Matrix3.cpp.o.d -o CMakeFiles/Thesis.dir/Math/Matrix/src/Matrix3.cpp.o -c /Users/davidepaollilo/Desktop/Workspace/C++/Thesis/Math/Matrix/src/Matrix3.cpp

CMakeFiles/Thesis.dir/Math/Matrix/src/Matrix3.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Thesis.dir/Math/Matrix/src/Matrix3.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/davidepaollilo/Desktop/Workspace/C++/Thesis/Math/Matrix/src/Matrix3.cpp > CMakeFiles/Thesis.dir/Math/Matrix/src/Matrix3.cpp.i

CMakeFiles/Thesis.dir/Math/Matrix/src/Matrix3.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Thesis.dir/Math/Matrix/src/Matrix3.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/davidepaollilo/Desktop/Workspace/C++/Thesis/Math/Matrix/src/Matrix3.cpp -o CMakeFiles/Thesis.dir/Math/Matrix/src/Matrix3.cpp.s

CMakeFiles/Thesis.dir/Math/Matrix/src/Matrix4.cpp.o: CMakeFiles/Thesis.dir/flags.make
CMakeFiles/Thesis.dir/Math/Matrix/src/Matrix4.cpp.o: ../Math/Matrix/src/Matrix4.cpp
CMakeFiles/Thesis.dir/Math/Matrix/src/Matrix4.cpp.o: CMakeFiles/Thesis.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/davidepaollilo/Desktop/Workspace/C++/Thesis/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/Thesis.dir/Math/Matrix/src/Matrix4.cpp.o"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Thesis.dir/Math/Matrix/src/Matrix4.cpp.o -MF CMakeFiles/Thesis.dir/Math/Matrix/src/Matrix4.cpp.o.d -o CMakeFiles/Thesis.dir/Math/Matrix/src/Matrix4.cpp.o -c /Users/davidepaollilo/Desktop/Workspace/C++/Thesis/Math/Matrix/src/Matrix4.cpp

CMakeFiles/Thesis.dir/Math/Matrix/src/Matrix4.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Thesis.dir/Math/Matrix/src/Matrix4.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/davidepaollilo/Desktop/Workspace/C++/Thesis/Math/Matrix/src/Matrix4.cpp > CMakeFiles/Thesis.dir/Math/Matrix/src/Matrix4.cpp.i

CMakeFiles/Thesis.dir/Math/Matrix/src/Matrix4.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Thesis.dir/Math/Matrix/src/Matrix4.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/davidepaollilo/Desktop/Workspace/C++/Thesis/Math/Matrix/src/Matrix4.cpp -o CMakeFiles/Thesis.dir/Math/Matrix/src/Matrix4.cpp.s

CMakeFiles/Thesis.dir/Math/Point/src/Point2.cpp.o: CMakeFiles/Thesis.dir/flags.make
CMakeFiles/Thesis.dir/Math/Point/src/Point2.cpp.o: ../Math/Point/src/Point2.cpp
CMakeFiles/Thesis.dir/Math/Point/src/Point2.cpp.o: CMakeFiles/Thesis.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/davidepaollilo/Desktop/Workspace/C++/Thesis/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/Thesis.dir/Math/Point/src/Point2.cpp.o"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Thesis.dir/Math/Point/src/Point2.cpp.o -MF CMakeFiles/Thesis.dir/Math/Point/src/Point2.cpp.o.d -o CMakeFiles/Thesis.dir/Math/Point/src/Point2.cpp.o -c /Users/davidepaollilo/Desktop/Workspace/C++/Thesis/Math/Point/src/Point2.cpp

CMakeFiles/Thesis.dir/Math/Point/src/Point2.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Thesis.dir/Math/Point/src/Point2.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/davidepaollilo/Desktop/Workspace/C++/Thesis/Math/Point/src/Point2.cpp > CMakeFiles/Thesis.dir/Math/Point/src/Point2.cpp.i

CMakeFiles/Thesis.dir/Math/Point/src/Point2.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Thesis.dir/Math/Point/src/Point2.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/davidepaollilo/Desktop/Workspace/C++/Thesis/Math/Point/src/Point2.cpp -o CMakeFiles/Thesis.dir/Math/Point/src/Point2.cpp.s

CMakeFiles/Thesis.dir/Math/Point/src/Point3.cpp.o: CMakeFiles/Thesis.dir/flags.make
CMakeFiles/Thesis.dir/Math/Point/src/Point3.cpp.o: ../Math/Point/src/Point3.cpp
CMakeFiles/Thesis.dir/Math/Point/src/Point3.cpp.o: CMakeFiles/Thesis.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/davidepaollilo/Desktop/Workspace/C++/Thesis/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/Thesis.dir/Math/Point/src/Point3.cpp.o"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Thesis.dir/Math/Point/src/Point3.cpp.o -MF CMakeFiles/Thesis.dir/Math/Point/src/Point3.cpp.o.d -o CMakeFiles/Thesis.dir/Math/Point/src/Point3.cpp.o -c /Users/davidepaollilo/Desktop/Workspace/C++/Thesis/Math/Point/src/Point3.cpp

CMakeFiles/Thesis.dir/Math/Point/src/Point3.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Thesis.dir/Math/Point/src/Point3.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/davidepaollilo/Desktop/Workspace/C++/Thesis/Math/Point/src/Point3.cpp > CMakeFiles/Thesis.dir/Math/Point/src/Point3.cpp.i

CMakeFiles/Thesis.dir/Math/Point/src/Point3.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Thesis.dir/Math/Point/src/Point3.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/davidepaollilo/Desktop/Workspace/C++/Thesis/Math/Point/src/Point3.cpp -o CMakeFiles/Thesis.dir/Math/Point/src/Point3.cpp.s

CMakeFiles/Thesis.dir/Math/Point/src/Point4.cpp.o: CMakeFiles/Thesis.dir/flags.make
CMakeFiles/Thesis.dir/Math/Point/src/Point4.cpp.o: ../Math/Point/src/Point4.cpp
CMakeFiles/Thesis.dir/Math/Point/src/Point4.cpp.o: CMakeFiles/Thesis.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/davidepaollilo/Desktop/Workspace/C++/Thesis/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/Thesis.dir/Math/Point/src/Point4.cpp.o"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Thesis.dir/Math/Point/src/Point4.cpp.o -MF CMakeFiles/Thesis.dir/Math/Point/src/Point4.cpp.o.d -o CMakeFiles/Thesis.dir/Math/Point/src/Point4.cpp.o -c /Users/davidepaollilo/Desktop/Workspace/C++/Thesis/Math/Point/src/Point4.cpp

CMakeFiles/Thesis.dir/Math/Point/src/Point4.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Thesis.dir/Math/Point/src/Point4.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/davidepaollilo/Desktop/Workspace/C++/Thesis/Math/Point/src/Point4.cpp > CMakeFiles/Thesis.dir/Math/Point/src/Point4.cpp.i

CMakeFiles/Thesis.dir/Math/Point/src/Point4.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Thesis.dir/Math/Point/src/Point4.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/davidepaollilo/Desktop/Workspace/C++/Thesis/Math/Point/src/Point4.cpp -o CMakeFiles/Thesis.dir/Math/Point/src/Point4.cpp.s

CMakeFiles/Thesis.dir/Math/Rotation/src/Quaternion.cpp.o: CMakeFiles/Thesis.dir/flags.make
CMakeFiles/Thesis.dir/Math/Rotation/src/Quaternion.cpp.o: ../Math/Rotation/src/Quaternion.cpp
CMakeFiles/Thesis.dir/Math/Rotation/src/Quaternion.cpp.o: CMakeFiles/Thesis.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/davidepaollilo/Desktop/Workspace/C++/Thesis/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/Thesis.dir/Math/Rotation/src/Quaternion.cpp.o"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Thesis.dir/Math/Rotation/src/Quaternion.cpp.o -MF CMakeFiles/Thesis.dir/Math/Rotation/src/Quaternion.cpp.o.d -o CMakeFiles/Thesis.dir/Math/Rotation/src/Quaternion.cpp.o -c /Users/davidepaollilo/Desktop/Workspace/C++/Thesis/Math/Rotation/src/Quaternion.cpp

CMakeFiles/Thesis.dir/Math/Rotation/src/Quaternion.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Thesis.dir/Math/Rotation/src/Quaternion.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/davidepaollilo/Desktop/Workspace/C++/Thesis/Math/Rotation/src/Quaternion.cpp > CMakeFiles/Thesis.dir/Math/Rotation/src/Quaternion.cpp.i

CMakeFiles/Thesis.dir/Math/Rotation/src/Quaternion.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Thesis.dir/Math/Rotation/src/Quaternion.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/davidepaollilo/Desktop/Workspace/C++/Thesis/Math/Rotation/src/Quaternion.cpp -o CMakeFiles/Thesis.dir/Math/Rotation/src/Quaternion.cpp.s

CMakeFiles/Thesis.dir/Math/Vector/src/Vector2.cpp.o: CMakeFiles/Thesis.dir/flags.make
CMakeFiles/Thesis.dir/Math/Vector/src/Vector2.cpp.o: ../Math/Vector/src/Vector2.cpp
CMakeFiles/Thesis.dir/Math/Vector/src/Vector2.cpp.o: CMakeFiles/Thesis.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/davidepaollilo/Desktop/Workspace/C++/Thesis/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/Thesis.dir/Math/Vector/src/Vector2.cpp.o"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Thesis.dir/Math/Vector/src/Vector2.cpp.o -MF CMakeFiles/Thesis.dir/Math/Vector/src/Vector2.cpp.o.d -o CMakeFiles/Thesis.dir/Math/Vector/src/Vector2.cpp.o -c /Users/davidepaollilo/Desktop/Workspace/C++/Thesis/Math/Vector/src/Vector2.cpp

CMakeFiles/Thesis.dir/Math/Vector/src/Vector2.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Thesis.dir/Math/Vector/src/Vector2.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/davidepaollilo/Desktop/Workspace/C++/Thesis/Math/Vector/src/Vector2.cpp > CMakeFiles/Thesis.dir/Math/Vector/src/Vector2.cpp.i

CMakeFiles/Thesis.dir/Math/Vector/src/Vector2.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Thesis.dir/Math/Vector/src/Vector2.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/davidepaollilo/Desktop/Workspace/C++/Thesis/Math/Vector/src/Vector2.cpp -o CMakeFiles/Thesis.dir/Math/Vector/src/Vector2.cpp.s

CMakeFiles/Thesis.dir/Math/Vector/src/Vector3.cpp.o: CMakeFiles/Thesis.dir/flags.make
CMakeFiles/Thesis.dir/Math/Vector/src/Vector3.cpp.o: ../Math/Vector/src/Vector3.cpp
CMakeFiles/Thesis.dir/Math/Vector/src/Vector3.cpp.o: CMakeFiles/Thesis.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/davidepaollilo/Desktop/Workspace/C++/Thesis/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object CMakeFiles/Thesis.dir/Math/Vector/src/Vector3.cpp.o"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Thesis.dir/Math/Vector/src/Vector3.cpp.o -MF CMakeFiles/Thesis.dir/Math/Vector/src/Vector3.cpp.o.d -o CMakeFiles/Thesis.dir/Math/Vector/src/Vector3.cpp.o -c /Users/davidepaollilo/Desktop/Workspace/C++/Thesis/Math/Vector/src/Vector3.cpp

CMakeFiles/Thesis.dir/Math/Vector/src/Vector3.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Thesis.dir/Math/Vector/src/Vector3.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/davidepaollilo/Desktop/Workspace/C++/Thesis/Math/Vector/src/Vector3.cpp > CMakeFiles/Thesis.dir/Math/Vector/src/Vector3.cpp.i

CMakeFiles/Thesis.dir/Math/Vector/src/Vector3.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Thesis.dir/Math/Vector/src/Vector3.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/davidepaollilo/Desktop/Workspace/C++/Thesis/Math/Vector/src/Vector3.cpp -o CMakeFiles/Thesis.dir/Math/Vector/src/Vector3.cpp.s

CMakeFiles/Thesis.dir/Math/Vector/src/Vector4.cpp.o: CMakeFiles/Thesis.dir/flags.make
CMakeFiles/Thesis.dir/Math/Vector/src/Vector4.cpp.o: ../Math/Vector/src/Vector4.cpp
CMakeFiles/Thesis.dir/Math/Vector/src/Vector4.cpp.o: CMakeFiles/Thesis.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/davidepaollilo/Desktop/Workspace/C++/Thesis/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building CXX object CMakeFiles/Thesis.dir/Math/Vector/src/Vector4.cpp.o"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Thesis.dir/Math/Vector/src/Vector4.cpp.o -MF CMakeFiles/Thesis.dir/Math/Vector/src/Vector4.cpp.o.d -o CMakeFiles/Thesis.dir/Math/Vector/src/Vector4.cpp.o -c /Users/davidepaollilo/Desktop/Workspace/C++/Thesis/Math/Vector/src/Vector4.cpp

CMakeFiles/Thesis.dir/Math/Vector/src/Vector4.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Thesis.dir/Math/Vector/src/Vector4.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/davidepaollilo/Desktop/Workspace/C++/Thesis/Math/Vector/src/Vector4.cpp > CMakeFiles/Thesis.dir/Math/Vector/src/Vector4.cpp.i

CMakeFiles/Thesis.dir/Math/Vector/src/Vector4.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Thesis.dir/Math/Vector/src/Vector4.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/davidepaollilo/Desktop/Workspace/C++/Thesis/Math/Vector/src/Vector4.cpp -o CMakeFiles/Thesis.dir/Math/Vector/src/Vector4.cpp.s

CMakeFiles/Thesis.dir/Math/Versor/src/Versor2.cpp.o: CMakeFiles/Thesis.dir/flags.make
CMakeFiles/Thesis.dir/Math/Versor/src/Versor2.cpp.o: ../Math/Versor/src/Versor2.cpp
CMakeFiles/Thesis.dir/Math/Versor/src/Versor2.cpp.o: CMakeFiles/Thesis.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/davidepaollilo/Desktop/Workspace/C++/Thesis/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Building CXX object CMakeFiles/Thesis.dir/Math/Versor/src/Versor2.cpp.o"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Thesis.dir/Math/Versor/src/Versor2.cpp.o -MF CMakeFiles/Thesis.dir/Math/Versor/src/Versor2.cpp.o.d -o CMakeFiles/Thesis.dir/Math/Versor/src/Versor2.cpp.o -c /Users/davidepaollilo/Desktop/Workspace/C++/Thesis/Math/Versor/src/Versor2.cpp

CMakeFiles/Thesis.dir/Math/Versor/src/Versor2.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Thesis.dir/Math/Versor/src/Versor2.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/davidepaollilo/Desktop/Workspace/C++/Thesis/Math/Versor/src/Versor2.cpp > CMakeFiles/Thesis.dir/Math/Versor/src/Versor2.cpp.i

CMakeFiles/Thesis.dir/Math/Versor/src/Versor2.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Thesis.dir/Math/Versor/src/Versor2.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/davidepaollilo/Desktop/Workspace/C++/Thesis/Math/Versor/src/Versor2.cpp -o CMakeFiles/Thesis.dir/Math/Versor/src/Versor2.cpp.s

CMakeFiles/Thesis.dir/Math/Versor/src/Versor3.cpp.o: CMakeFiles/Thesis.dir/flags.make
CMakeFiles/Thesis.dir/Math/Versor/src/Versor3.cpp.o: ../Math/Versor/src/Versor3.cpp
CMakeFiles/Thesis.dir/Math/Versor/src/Versor3.cpp.o: CMakeFiles/Thesis.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/davidepaollilo/Desktop/Workspace/C++/Thesis/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_13) "Building CXX object CMakeFiles/Thesis.dir/Math/Versor/src/Versor3.cpp.o"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Thesis.dir/Math/Versor/src/Versor3.cpp.o -MF CMakeFiles/Thesis.dir/Math/Versor/src/Versor3.cpp.o.d -o CMakeFiles/Thesis.dir/Math/Versor/src/Versor3.cpp.o -c /Users/davidepaollilo/Desktop/Workspace/C++/Thesis/Math/Versor/src/Versor3.cpp

CMakeFiles/Thesis.dir/Math/Versor/src/Versor3.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Thesis.dir/Math/Versor/src/Versor3.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/davidepaollilo/Desktop/Workspace/C++/Thesis/Math/Versor/src/Versor3.cpp > CMakeFiles/Thesis.dir/Math/Versor/src/Versor3.cpp.i

CMakeFiles/Thesis.dir/Math/Versor/src/Versor3.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Thesis.dir/Math/Versor/src/Versor3.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/davidepaollilo/Desktop/Workspace/C++/Thesis/Math/Versor/src/Versor3.cpp -o CMakeFiles/Thesis.dir/Math/Versor/src/Versor3.cpp.s

CMakeFiles/Thesis.dir/Math/Versor/src/Versor4.cpp.o: CMakeFiles/Thesis.dir/flags.make
CMakeFiles/Thesis.dir/Math/Versor/src/Versor4.cpp.o: ../Math/Versor/src/Versor4.cpp
CMakeFiles/Thesis.dir/Math/Versor/src/Versor4.cpp.o: CMakeFiles/Thesis.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/davidepaollilo/Desktop/Workspace/C++/Thesis/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_14) "Building CXX object CMakeFiles/Thesis.dir/Math/Versor/src/Versor4.cpp.o"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Thesis.dir/Math/Versor/src/Versor4.cpp.o -MF CMakeFiles/Thesis.dir/Math/Versor/src/Versor4.cpp.o.d -o CMakeFiles/Thesis.dir/Math/Versor/src/Versor4.cpp.o -c /Users/davidepaollilo/Desktop/Workspace/C++/Thesis/Math/Versor/src/Versor4.cpp

CMakeFiles/Thesis.dir/Math/Versor/src/Versor4.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Thesis.dir/Math/Versor/src/Versor4.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/davidepaollilo/Desktop/Workspace/C++/Thesis/Math/Versor/src/Versor4.cpp > CMakeFiles/Thesis.dir/Math/Versor/src/Versor4.cpp.i

CMakeFiles/Thesis.dir/Math/Versor/src/Versor4.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Thesis.dir/Math/Versor/src/Versor4.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/davidepaollilo/Desktop/Workspace/C++/Thesis/Math/Versor/src/Versor4.cpp -o CMakeFiles/Thesis.dir/Math/Versor/src/Versor4.cpp.s

CMakeFiles/Thesis.dir/main.cpp.o: CMakeFiles/Thesis.dir/flags.make
CMakeFiles/Thesis.dir/main.cpp.o: ../main.cpp
CMakeFiles/Thesis.dir/main.cpp.o: CMakeFiles/Thesis.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/davidepaollilo/Desktop/Workspace/C++/Thesis/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_15) "Building CXX object CMakeFiles/Thesis.dir/main.cpp.o"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Thesis.dir/main.cpp.o -MF CMakeFiles/Thesis.dir/main.cpp.o.d -o CMakeFiles/Thesis.dir/main.cpp.o -c /Users/davidepaollilo/Desktop/Workspace/C++/Thesis/main.cpp

CMakeFiles/Thesis.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Thesis.dir/main.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/davidepaollilo/Desktop/Workspace/C++/Thesis/main.cpp > CMakeFiles/Thesis.dir/main.cpp.i

CMakeFiles/Thesis.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Thesis.dir/main.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/davidepaollilo/Desktop/Workspace/C++/Thesis/main.cpp -o CMakeFiles/Thesis.dir/main.cpp.s

# Object files for target Thesis
Thesis_OBJECTS = \
"CMakeFiles/Thesis.dir/Core/src/Mesh.cpp.o" \
"CMakeFiles/Thesis.dir/Math/Matrix/src/Matrix2.cpp.o" \
"CMakeFiles/Thesis.dir/Math/Matrix/src/Matrix3.cpp.o" \
"CMakeFiles/Thesis.dir/Math/Matrix/src/Matrix4.cpp.o" \
"CMakeFiles/Thesis.dir/Math/Point/src/Point2.cpp.o" \
"CMakeFiles/Thesis.dir/Math/Point/src/Point3.cpp.o" \
"CMakeFiles/Thesis.dir/Math/Point/src/Point4.cpp.o" \
"CMakeFiles/Thesis.dir/Math/Rotation/src/Quaternion.cpp.o" \
"CMakeFiles/Thesis.dir/Math/Vector/src/Vector2.cpp.o" \
"CMakeFiles/Thesis.dir/Math/Vector/src/Vector3.cpp.o" \
"CMakeFiles/Thesis.dir/Math/Vector/src/Vector4.cpp.o" \
"CMakeFiles/Thesis.dir/Math/Versor/src/Versor2.cpp.o" \
"CMakeFiles/Thesis.dir/Math/Versor/src/Versor3.cpp.o" \
"CMakeFiles/Thesis.dir/Math/Versor/src/Versor4.cpp.o" \
"CMakeFiles/Thesis.dir/main.cpp.o"

# External object files for target Thesis
Thesis_EXTERNAL_OBJECTS =

Thesis: CMakeFiles/Thesis.dir/Core/src/Mesh.cpp.o
Thesis: CMakeFiles/Thesis.dir/Math/Matrix/src/Matrix2.cpp.o
Thesis: CMakeFiles/Thesis.dir/Math/Matrix/src/Matrix3.cpp.o
Thesis: CMakeFiles/Thesis.dir/Math/Matrix/src/Matrix4.cpp.o
Thesis: CMakeFiles/Thesis.dir/Math/Point/src/Point2.cpp.o
Thesis: CMakeFiles/Thesis.dir/Math/Point/src/Point3.cpp.o
Thesis: CMakeFiles/Thesis.dir/Math/Point/src/Point4.cpp.o
Thesis: CMakeFiles/Thesis.dir/Math/Rotation/src/Quaternion.cpp.o
Thesis: CMakeFiles/Thesis.dir/Math/Vector/src/Vector2.cpp.o
Thesis: CMakeFiles/Thesis.dir/Math/Vector/src/Vector3.cpp.o
Thesis: CMakeFiles/Thesis.dir/Math/Vector/src/Vector4.cpp.o
Thesis: CMakeFiles/Thesis.dir/Math/Versor/src/Versor2.cpp.o
Thesis: CMakeFiles/Thesis.dir/Math/Versor/src/Versor3.cpp.o
Thesis: CMakeFiles/Thesis.dir/Math/Versor/src/Versor4.cpp.o
Thesis: CMakeFiles/Thesis.dir/main.cpp.o
Thesis: CMakeFiles/Thesis.dir/build.make
Thesis: /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX11.3.sdk/System/Library/Frameworks/OpenGL.framework/OpenGL.tbd
Thesis: libimguizmo.a
Thesis: libimgui.a
Thesis: _deps/glfw-build/src/libglfw3.a
Thesis: _deps/glad-build/libglad.a
Thesis: _deps/triangle-build/libtriangle.a
Thesis: CMakeFiles/Thesis.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/davidepaollilo/Desktop/Workspace/C++/Thesis/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_16) "Linking CXX executable Thesis"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Thesis.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Thesis.dir/build: Thesis
.PHONY : CMakeFiles/Thesis.dir/build

CMakeFiles/Thesis.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Thesis.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Thesis.dir/clean

CMakeFiles/Thesis.dir/depend:
	cd /Users/davidepaollilo/Desktop/Workspace/C++/Thesis/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/davidepaollilo/Desktop/Workspace/C++/Thesis /Users/davidepaollilo/Desktop/Workspace/C++/Thesis /Users/davidepaollilo/Desktop/Workspace/C++/Thesis/build /Users/davidepaollilo/Desktop/Workspace/C++/Thesis/build /Users/davidepaollilo/Desktop/Workspace/C++/Thesis/build/CMakeFiles/Thesis.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Thesis.dir/depend

