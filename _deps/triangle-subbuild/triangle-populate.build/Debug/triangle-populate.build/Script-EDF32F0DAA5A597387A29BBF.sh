#!/bin/sh
set -e
if test "$CONFIGURATION" = "Debug"; then :
  cd /Users/davidepaollilo/Workspaces/C++/Thesis/_deps/triangle-subbuild
  /usr/local/Cellar/cmake/3.22.3/bin/cmake -E make_directory /Users/davidepaollilo/Workspaces/C++/Thesis/_deps/triangle-src
  /usr/local/Cellar/cmake/3.22.3/bin/cmake -E make_directory /Users/davidepaollilo/Workspaces/C++/Thesis/_deps/triangle-build
  /usr/local/Cellar/cmake/3.22.3/bin/cmake -E make_directory /Users/davidepaollilo/Workspaces/C++/Thesis/_deps/triangle-subbuild/triangle-populate-prefix
  /usr/local/Cellar/cmake/3.22.3/bin/cmake -E make_directory /Users/davidepaollilo/Workspaces/C++/Thesis/_deps/triangle-subbuild/triangle-populate-prefix/tmp
  /usr/local/Cellar/cmake/3.22.3/bin/cmake -E make_directory /Users/davidepaollilo/Workspaces/C++/Thesis/_deps/triangle-subbuild/triangle-populate-prefix/src/triangle-populate-stamp/$CONFIGURATION$EFFECTIVE_PLATFORM_NAME
  /usr/local/Cellar/cmake/3.22.3/bin/cmake -E make_directory /Users/davidepaollilo/Workspaces/C++/Thesis/_deps/triangle-subbuild/triangle-populate-prefix/src
  /usr/local/Cellar/cmake/3.22.3/bin/cmake -E make_directory /Users/davidepaollilo/Workspaces/C++/Thesis/_deps/triangle-subbuild/triangle-populate-prefix/src/triangle-populate-stamp
  /usr/local/Cellar/cmake/3.22.3/bin/cmake -E touch /Users/davidepaollilo/Workspaces/C++/Thesis/_deps/triangle-subbuild/triangle-populate-prefix/src/triangle-populate-stamp/$CONFIGURATION$EFFECTIVE_PLATFORM_NAME/triangle-populate-mkdir
fi
if test "$CONFIGURATION" = "Release"; then :
  cd /Users/davidepaollilo/Workspaces/C++/Thesis/_deps/triangle-subbuild
  /usr/local/Cellar/cmake/3.22.3/bin/cmake -E make_directory /Users/davidepaollilo/Workspaces/C++/Thesis/_deps/triangle-src
  /usr/local/Cellar/cmake/3.22.3/bin/cmake -E make_directory /Users/davidepaollilo/Workspaces/C++/Thesis/_deps/triangle-build
  /usr/local/Cellar/cmake/3.22.3/bin/cmake -E make_directory /Users/davidepaollilo/Workspaces/C++/Thesis/_deps/triangle-subbuild/triangle-populate-prefix
  /usr/local/Cellar/cmake/3.22.3/bin/cmake -E make_directory /Users/davidepaollilo/Workspaces/C++/Thesis/_deps/triangle-subbuild/triangle-populate-prefix/tmp
  /usr/local/Cellar/cmake/3.22.3/bin/cmake -E make_directory /Users/davidepaollilo/Workspaces/C++/Thesis/_deps/triangle-subbuild/triangle-populate-prefix/src/triangle-populate-stamp/$CONFIGURATION$EFFECTIVE_PLATFORM_NAME
  /usr/local/Cellar/cmake/3.22.3/bin/cmake -E make_directory /Users/davidepaollilo/Workspaces/C++/Thesis/_deps/triangle-subbuild/triangle-populate-prefix/src
  /usr/local/Cellar/cmake/3.22.3/bin/cmake -E make_directory /Users/davidepaollilo/Workspaces/C++/Thesis/_deps/triangle-subbuild/triangle-populate-prefix/src/triangle-populate-stamp
  /usr/local/Cellar/cmake/3.22.3/bin/cmake -E touch /Users/davidepaollilo/Workspaces/C++/Thesis/_deps/triangle-subbuild/triangle-populate-prefix/src/triangle-populate-stamp/$CONFIGURATION$EFFECTIVE_PLATFORM_NAME/triangle-populate-mkdir
fi
if test "$CONFIGURATION" = "MinSizeRel"; then :
  cd /Users/davidepaollilo/Workspaces/C++/Thesis/_deps/triangle-subbuild
  /usr/local/Cellar/cmake/3.22.3/bin/cmake -E make_directory /Users/davidepaollilo/Workspaces/C++/Thesis/_deps/triangle-src
  /usr/local/Cellar/cmake/3.22.3/bin/cmake -E make_directory /Users/davidepaollilo/Workspaces/C++/Thesis/_deps/triangle-build
  /usr/local/Cellar/cmake/3.22.3/bin/cmake -E make_directory /Users/davidepaollilo/Workspaces/C++/Thesis/_deps/triangle-subbuild/triangle-populate-prefix
  /usr/local/Cellar/cmake/3.22.3/bin/cmake -E make_directory /Users/davidepaollilo/Workspaces/C++/Thesis/_deps/triangle-subbuild/triangle-populate-prefix/tmp
  /usr/local/Cellar/cmake/3.22.3/bin/cmake -E make_directory /Users/davidepaollilo/Workspaces/C++/Thesis/_deps/triangle-subbuild/triangle-populate-prefix/src/triangle-populate-stamp/$CONFIGURATION$EFFECTIVE_PLATFORM_NAME
  /usr/local/Cellar/cmake/3.22.3/bin/cmake -E make_directory /Users/davidepaollilo/Workspaces/C++/Thesis/_deps/triangle-subbuild/triangle-populate-prefix/src
  /usr/local/Cellar/cmake/3.22.3/bin/cmake -E make_directory /Users/davidepaollilo/Workspaces/C++/Thesis/_deps/triangle-subbuild/triangle-populate-prefix/src/triangle-populate-stamp
  /usr/local/Cellar/cmake/3.22.3/bin/cmake -E touch /Users/davidepaollilo/Workspaces/C++/Thesis/_deps/triangle-subbuild/triangle-populate-prefix/src/triangle-populate-stamp/$CONFIGURATION$EFFECTIVE_PLATFORM_NAME/triangle-populate-mkdir
fi
if test "$CONFIGURATION" = "RelWithDebInfo"; then :
  cd /Users/davidepaollilo/Workspaces/C++/Thesis/_deps/triangle-subbuild
  /usr/local/Cellar/cmake/3.22.3/bin/cmake -E make_directory /Users/davidepaollilo/Workspaces/C++/Thesis/_deps/triangle-src
  /usr/local/Cellar/cmake/3.22.3/bin/cmake -E make_directory /Users/davidepaollilo/Workspaces/C++/Thesis/_deps/triangle-build
  /usr/local/Cellar/cmake/3.22.3/bin/cmake -E make_directory /Users/davidepaollilo/Workspaces/C++/Thesis/_deps/triangle-subbuild/triangle-populate-prefix
  /usr/local/Cellar/cmake/3.22.3/bin/cmake -E make_directory /Users/davidepaollilo/Workspaces/C++/Thesis/_deps/triangle-subbuild/triangle-populate-prefix/tmp
  /usr/local/Cellar/cmake/3.22.3/bin/cmake -E make_directory /Users/davidepaollilo/Workspaces/C++/Thesis/_deps/triangle-subbuild/triangle-populate-prefix/src/triangle-populate-stamp/$CONFIGURATION$EFFECTIVE_PLATFORM_NAME
  /usr/local/Cellar/cmake/3.22.3/bin/cmake -E make_directory /Users/davidepaollilo/Workspaces/C++/Thesis/_deps/triangle-subbuild/triangle-populate-prefix/src
  /usr/local/Cellar/cmake/3.22.3/bin/cmake -E make_directory /Users/davidepaollilo/Workspaces/C++/Thesis/_deps/triangle-subbuild/triangle-populate-prefix/src/triangle-populate-stamp
  /usr/local/Cellar/cmake/3.22.3/bin/cmake -E touch /Users/davidepaollilo/Workspaces/C++/Thesis/_deps/triangle-subbuild/triangle-populate-prefix/src/triangle-populate-stamp/$CONFIGURATION$EFFECTIVE_PLATFORM_NAME/triangle-populate-mkdir
fi

