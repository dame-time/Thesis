#!/bin/sh
set -e
if test "$CONFIGURATION" = "Debug"; then :
  cd /Users/davidepaollilo/Workspaces/C++/Thesis/_deps
  /usr/local/Cellar/cmake/3.22.3/bin/cmake -P /Users/davidepaollilo/Workspaces/C++/Thesis/_deps/libigl_imgui_fonts-subbuild/libigl_imgui_fonts-populate-prefix/tmp/libigl_imgui_fonts-populate-gitclone.cmake
  /usr/local/Cellar/cmake/3.22.3/bin/cmake -E touch /Users/davidepaollilo/Workspaces/C++/Thesis/_deps/libigl_imgui_fonts-subbuild/libigl_imgui_fonts-populate-prefix/src/libigl_imgui_fonts-populate-stamp/$CONFIGURATION$EFFECTIVE_PLATFORM_NAME/libigl_imgui_fonts-populate-download
fi
if test "$CONFIGURATION" = "Release"; then :
  cd /Users/davidepaollilo/Workspaces/C++/Thesis/_deps
  /usr/local/Cellar/cmake/3.22.3/bin/cmake -P /Users/davidepaollilo/Workspaces/C++/Thesis/_deps/libigl_imgui_fonts-subbuild/libigl_imgui_fonts-populate-prefix/tmp/libigl_imgui_fonts-populate-gitclone.cmake
  /usr/local/Cellar/cmake/3.22.3/bin/cmake -E touch /Users/davidepaollilo/Workspaces/C++/Thesis/_deps/libigl_imgui_fonts-subbuild/libigl_imgui_fonts-populate-prefix/src/libigl_imgui_fonts-populate-stamp/$CONFIGURATION$EFFECTIVE_PLATFORM_NAME/libigl_imgui_fonts-populate-download
fi
if test "$CONFIGURATION" = "MinSizeRel"; then :
  cd /Users/davidepaollilo/Workspaces/C++/Thesis/_deps
  /usr/local/Cellar/cmake/3.22.3/bin/cmake -P /Users/davidepaollilo/Workspaces/C++/Thesis/_deps/libigl_imgui_fonts-subbuild/libigl_imgui_fonts-populate-prefix/tmp/libigl_imgui_fonts-populate-gitclone.cmake
  /usr/local/Cellar/cmake/3.22.3/bin/cmake -E touch /Users/davidepaollilo/Workspaces/C++/Thesis/_deps/libigl_imgui_fonts-subbuild/libigl_imgui_fonts-populate-prefix/src/libigl_imgui_fonts-populate-stamp/$CONFIGURATION$EFFECTIVE_PLATFORM_NAME/libigl_imgui_fonts-populate-download
fi
if test "$CONFIGURATION" = "RelWithDebInfo"; then :
  cd /Users/davidepaollilo/Workspaces/C++/Thesis/_deps
  /usr/local/Cellar/cmake/3.22.3/bin/cmake -P /Users/davidepaollilo/Workspaces/C++/Thesis/_deps/libigl_imgui_fonts-subbuild/libigl_imgui_fonts-populate-prefix/tmp/libigl_imgui_fonts-populate-gitclone.cmake
  /usr/local/Cellar/cmake/3.22.3/bin/cmake -E touch /Users/davidepaollilo/Workspaces/C++/Thesis/_deps/libigl_imgui_fonts-subbuild/libigl_imgui_fonts-populate-prefix/src/libigl_imgui_fonts-populate-stamp/$CONFIGURATION$EFFECTIVE_PLATFORM_NAME/libigl_imgui_fonts-populate-download
fi

