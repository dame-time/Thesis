# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.22.3)

# We name the project and the target for the ExternalProject_Add() call
# to something that will highlight to the user what we are working on if
# something goes wrong and an error message is produced.

project(libigl_imgui_fonts-populate NONE)


# Pass through things we've already detected in the main project to avoid
# paying the cost of redetecting them again in ExternalProject_Add()
set(GIT_EXECUTABLE [==[/usr/local/bin/git]==])
set(GIT_VERSION_STRING [==[2.35.1]==])
set_property(GLOBAL PROPERTY _CMAKE_FindGit_GIT_EXECUTABLE_VERSION
  [==[/usr/local/bin/git;2.35.1]==]
)


include(ExternalProject)
ExternalProject_Add(libigl_imgui_fonts-populate
                     "UPDATE_DISCONNECTED" "False" "GIT_REPOSITORY" "https://github.com/libigl/libigl-imgui.git" "GIT_TAG" "7e1053e750b0f4c129b046f4e455243cb7f804f3"
                    SOURCE_DIR          "/Users/davidepaollilo/Workspaces/C++/Thesis/_deps/libigl_imgui_fonts-src"
                    BINARY_DIR          "/Users/davidepaollilo/Workspaces/C++/Thesis/_deps/libigl_imgui_fonts-build"
                    CONFIGURE_COMMAND   ""
                    BUILD_COMMAND       ""
                    INSTALL_COMMAND     ""
                    TEST_COMMAND        ""
                    USES_TERMINAL_DOWNLOAD  YES
                    USES_TERMINAL_UPDATE    YES
)


