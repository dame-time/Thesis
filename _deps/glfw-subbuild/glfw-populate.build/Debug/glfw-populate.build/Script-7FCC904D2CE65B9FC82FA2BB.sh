#!/bin/sh
set -e
if test "$CONFIGURATION" = "Debug"; then :
  cd /Users/davidepaollilo/Workspaces/C++/Thesis/_deps/glfw-subbuild
  /usr/local/Cellar/cmake/3.22.3/bin/cmake -E echo_append
  /usr/local/Cellar/cmake/3.22.3/bin/cmake -E touch /Users/davidepaollilo/Workspaces/C++/Thesis/_deps/glfw-subbuild/glfw-populate-prefix/src/glfw-populate-stamp/$CONFIGURATION$EFFECTIVE_PLATFORM_NAME/glfw-populate-patch
fi
if test "$CONFIGURATION" = "Release"; then :
  cd /Users/davidepaollilo/Workspaces/C++/Thesis/_deps/glfw-subbuild
  /usr/local/Cellar/cmake/3.22.3/bin/cmake -E echo_append
  /usr/local/Cellar/cmake/3.22.3/bin/cmake -E touch /Users/davidepaollilo/Workspaces/C++/Thesis/_deps/glfw-subbuild/glfw-populate-prefix/src/glfw-populate-stamp/$CONFIGURATION$EFFECTIVE_PLATFORM_NAME/glfw-populate-patch
fi
if test "$CONFIGURATION" = "MinSizeRel"; then :
  cd /Users/davidepaollilo/Workspaces/C++/Thesis/_deps/glfw-subbuild
  /usr/local/Cellar/cmake/3.22.3/bin/cmake -E echo_append
  /usr/local/Cellar/cmake/3.22.3/bin/cmake -E touch /Users/davidepaollilo/Workspaces/C++/Thesis/_deps/glfw-subbuild/glfw-populate-prefix/src/glfw-populate-stamp/$CONFIGURATION$EFFECTIVE_PLATFORM_NAME/glfw-populate-patch
fi
if test "$CONFIGURATION" = "RelWithDebInfo"; then :
  cd /Users/davidepaollilo/Workspaces/C++/Thesis/_deps/glfw-subbuild
  /usr/local/Cellar/cmake/3.22.3/bin/cmake -E echo_append
  /usr/local/Cellar/cmake/3.22.3/bin/cmake -E touch /Users/davidepaollilo/Workspaces/C++/Thesis/_deps/glfw-subbuild/glfw-populate-prefix/src/glfw-populate-stamp/$CONFIGURATION$EFFECTIVE_PLATFORM_NAME/glfw-populate-patch
fi
