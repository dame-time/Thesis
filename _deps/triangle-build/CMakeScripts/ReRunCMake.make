# Generated by CMake, DO NOT EDIT

TARGETS:= 
empty:= 
space:= $(empty) $(empty)
spaceplus:= $(empty)\ $(empty)

TARGETS += $(subst $(space),$(spaceplus),$(wildcard /Users/davidepaollilo/Workspaces/C++/Thesis/_deps/triangle-src/CMakeLists.txt))
TARGETS += $(subst $(space),$(spaceplus),$(wildcard /Users/davidepaollilo/Workspaces/C++/Thesis/CMakeFiles/cmake.verify_globs))

.NOTPARALLEL:

.PHONY: all VERIFY_GLOBS

all: VERIFY_GLOBS /Users/davidepaollilo/Workspaces/C++/Thesis/CMakeFiles/cmake.check_cache

VERIFY_GLOBS:
	/usr/local/Cellar/cmake/3.22.3/bin/cmake -P /Users/davidepaollilo/Workspaces/C++/Thesis/CMakeFiles/VerifyGlobs.cmake

/Users/davidepaollilo/Workspaces/C++/Thesis/CMakeFiles/cmake.check_cache: $(TARGETS)
	/usr/local/Cellar/cmake/3.22.3/bin/cmake -H/Users/davidepaollilo/Workspaces/C++/Thesis -B/Users/davidepaollilo/Workspaces/C++/Thesis
