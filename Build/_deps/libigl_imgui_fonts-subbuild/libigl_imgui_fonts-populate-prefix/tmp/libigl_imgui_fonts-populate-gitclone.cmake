
if(NOT "/Users/davidepaollilo/Desktop/Workspace/C++/Thesis/Build/_deps/libigl_imgui_fonts-subbuild/libigl_imgui_fonts-populate-prefix/src/libigl_imgui_fonts-populate-stamp/libigl_imgui_fonts-populate-gitinfo.txt" IS_NEWER_THAN "/Users/davidepaollilo/Desktop/Workspace/C++/Thesis/Build/_deps/libigl_imgui_fonts-subbuild/libigl_imgui_fonts-populate-prefix/src/libigl_imgui_fonts-populate-stamp/libigl_imgui_fonts-populate-gitclone-lastrun.txt")
  message(STATUS "Avoiding repeated git clone, stamp file is up to date: '/Users/davidepaollilo/Desktop/Workspace/C++/Thesis/Build/_deps/libigl_imgui_fonts-subbuild/libigl_imgui_fonts-populate-prefix/src/libigl_imgui_fonts-populate-stamp/libigl_imgui_fonts-populate-gitclone-lastrun.txt'")
  return()
endif()

execute_process(
  COMMAND ${CMAKE_COMMAND} -E rm -rf "/Users/davidepaollilo/Desktop/Workspace/C++/Thesis/Build/_deps/libigl_imgui_fonts-src"
  RESULT_VARIABLE error_code
  )
if(error_code)
  message(FATAL_ERROR "Failed to remove directory: '/Users/davidepaollilo/Desktop/Workspace/C++/Thesis/Build/_deps/libigl_imgui_fonts-src'")
endif()

# try the clone 3 times in case there is an odd git clone issue
set(error_code 1)
set(number_of_tries 0)
while(error_code AND number_of_tries LESS 3)
  execute_process(
    COMMAND "/usr/local/bin/git"  clone --no-checkout --config "advice.detachedHead=false" "https://github.com/libigl/libigl-imgui.git" "libigl_imgui_fonts-src"
    WORKING_DIRECTORY "/Users/davidepaollilo/Desktop/Workspace/C++/Thesis/Build/_deps"
    RESULT_VARIABLE error_code
    )
  math(EXPR number_of_tries "${number_of_tries} + 1")
endwhile()
if(number_of_tries GREATER 1)
  message(STATUS "Had to git clone more than once:
          ${number_of_tries} times.")
endif()
if(error_code)
  message(FATAL_ERROR "Failed to clone repository: 'https://github.com/libigl/libigl-imgui.git'")
endif()

execute_process(
  COMMAND "/usr/local/bin/git"  checkout 7e1053e750b0f4c129b046f4e455243cb7f804f3 --
  WORKING_DIRECTORY "/Users/davidepaollilo/Desktop/Workspace/C++/Thesis/Build/_deps/libigl_imgui_fonts-src"
  RESULT_VARIABLE error_code
  )
if(error_code)
  message(FATAL_ERROR "Failed to checkout tag: '7e1053e750b0f4c129b046f4e455243cb7f804f3'")
endif()

set(init_submodules TRUE)
if(init_submodules)
  execute_process(
    COMMAND "/usr/local/bin/git"  submodule update --recursive --init 
    WORKING_DIRECTORY "/Users/davidepaollilo/Desktop/Workspace/C++/Thesis/Build/_deps/libigl_imgui_fonts-src"
    RESULT_VARIABLE error_code
    )
endif()
if(error_code)
  message(FATAL_ERROR "Failed to update submodules in: '/Users/davidepaollilo/Desktop/Workspace/C++/Thesis/Build/_deps/libigl_imgui_fonts-src'")
endif()

# Complete success, update the script-last-run stamp file:
#
execute_process(
  COMMAND ${CMAKE_COMMAND} -E copy
    "/Users/davidepaollilo/Desktop/Workspace/C++/Thesis/Build/_deps/libigl_imgui_fonts-subbuild/libigl_imgui_fonts-populate-prefix/src/libigl_imgui_fonts-populate-stamp/libigl_imgui_fonts-populate-gitinfo.txt"
    "/Users/davidepaollilo/Desktop/Workspace/C++/Thesis/Build/_deps/libigl_imgui_fonts-subbuild/libigl_imgui_fonts-populate-prefix/src/libigl_imgui_fonts-populate-stamp/libigl_imgui_fonts-populate-gitclone-lastrun.txt"
  RESULT_VARIABLE error_code
  )
if(error_code)
  message(FATAL_ERROR "Failed to copy script-last-run stamp file: '/Users/davidepaollilo/Desktop/Workspace/C++/Thesis/Build/_deps/libigl_imgui_fonts-subbuild/libigl_imgui_fonts-populate-prefix/src/libigl_imgui_fonts-populate-stamp/libigl_imgui_fonts-populate-gitclone-lastrun.txt'")
endif()

