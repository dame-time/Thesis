#!/bin/sh
set -e
if test "$CONFIGURATION" = "Debug"; then :
  cd /Users/davidepaollilo/Workspaces/C++/Thesis/_deps/glad-subbuild
  make -f /Users/davidepaollilo/Workspaces/C++/Thesis/_deps/glad-subbuild/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "Release"; then :
  cd /Users/davidepaollilo/Workspaces/C++/Thesis/_deps/glad-subbuild
  make -f /Users/davidepaollilo/Workspaces/C++/Thesis/_deps/glad-subbuild/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "MinSizeRel"; then :
  cd /Users/davidepaollilo/Workspaces/C++/Thesis/_deps/glad-subbuild
  make -f /Users/davidepaollilo/Workspaces/C++/Thesis/_deps/glad-subbuild/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "RelWithDebInfo"; then :
  cd /Users/davidepaollilo/Workspaces/C++/Thesis/_deps/glad-subbuild
  make -f /Users/davidepaollilo/Workspaces/C++/Thesis/_deps/glad-subbuild/CMakeScripts/ReRunCMake.make
fi

