#!/bin/sh
set -e
if test "$CONFIGURATION" = "Debug"; then :
  cd /Users/davidepaollilo/Workspaces/C++/Thesis/_deps/glfw-src
  /usr/local/Cellar/cmake/3.22.3/bin/cmake -P /Users/davidepaollilo/Workspaces/C++/Thesis/_deps/glfw-subbuild/glfw-populate-prefix/tmp/glfw-populate-gitupdate.cmake
fi
if test "$CONFIGURATION" = "Release"; then :
  cd /Users/davidepaollilo/Workspaces/C++/Thesis/_deps/glfw-src
  /usr/local/Cellar/cmake/3.22.3/bin/cmake -P /Users/davidepaollilo/Workspaces/C++/Thesis/_deps/glfw-subbuild/glfw-populate-prefix/tmp/glfw-populate-gitupdate.cmake
fi
if test "$CONFIGURATION" = "MinSizeRel"; then :
  cd /Users/davidepaollilo/Workspaces/C++/Thesis/_deps/glfw-src
  /usr/local/Cellar/cmake/3.22.3/bin/cmake -P /Users/davidepaollilo/Workspaces/C++/Thesis/_deps/glfw-subbuild/glfw-populate-prefix/tmp/glfw-populate-gitupdate.cmake
fi
if test "$CONFIGURATION" = "RelWithDebInfo"; then :
  cd /Users/davidepaollilo/Workspaces/C++/Thesis/_deps/glfw-src
  /usr/local/Cellar/cmake/3.22.3/bin/cmake -P /Users/davidepaollilo/Workspaces/C++/Thesis/_deps/glfw-subbuild/glfw-populate-prefix/tmp/glfw-populate-gitupdate.cmake
fi

