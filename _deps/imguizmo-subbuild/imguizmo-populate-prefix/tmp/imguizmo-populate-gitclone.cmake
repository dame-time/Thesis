
if(NOT "/Users/davidepaollilo/Workspaces/C++/Thesis/_deps/imguizmo-subbuild/imguizmo-populate-prefix/src/imguizmo-populate-stamp/imguizmo-populate-gitinfo.txt" IS_NEWER_THAN "/Users/davidepaollilo/Workspaces/C++/Thesis/_deps/imguizmo-subbuild/imguizmo-populate-prefix/src/imguizmo-populate-stamp/imguizmo-populate-gitclone-lastrun.txt")
  message(STATUS "Avoiding repeated git clone, stamp file is up to date: '/Users/davidepaollilo/Workspaces/C++/Thesis/_deps/imguizmo-subbuild/imguizmo-populate-prefix/src/imguizmo-populate-stamp/imguizmo-populate-gitclone-lastrun.txt'")
  return()
endif()

execute_process(
  COMMAND ${CMAKE_COMMAND} -E rm -rf "/Users/davidepaollilo/Workspaces/C++/Thesis/_deps/imguizmo-src"
  RESULT_VARIABLE error_code
  )
if(error_code)
  message(FATAL_ERROR "Failed to remove directory: '/Users/davidepaollilo/Workspaces/C++/Thesis/_deps/imguizmo-src'")
endif()

# try the clone 3 times in case there is an odd git clone issue
set(error_code 1)
set(number_of_tries 0)
while(error_code AND number_of_tries LESS 3)
  execute_process(
    COMMAND "/usr/local/bin/git"  clone --no-checkout --config "advice.detachedHead=false" "https://github.com/CedricGuillemet/ImGuizmo.git" "imguizmo-src"
    WORKING_DIRECTORY "/Users/davidepaollilo/Workspaces/C++/Thesis/_deps"
    RESULT_VARIABLE error_code
    )
  math(EXPR number_of_tries "${number_of_tries} + 1")
endwhile()
if(number_of_tries GREATER 1)
  message(STATUS "Had to git clone more than once:
          ${number_of_tries} times.")
endif()
if(error_code)
  message(FATAL_ERROR "Failed to clone repository: 'https://github.com/CedricGuillemet/ImGuizmo.git'")
endif()

execute_process(
  COMMAND "/usr/local/bin/git"  checkout a23567269f6617342bcc112394bdad937b54b2d7 --
  WORKING_DIRECTORY "/Users/davidepaollilo/Workspaces/C++/Thesis/_deps/imguizmo-src"
  RESULT_VARIABLE error_code
  )
if(error_code)
  message(FATAL_ERROR "Failed to checkout tag: 'a23567269f6617342bcc112394bdad937b54b2d7'")
endif()

set(init_submodules TRUE)
if(init_submodules)
  execute_process(
    COMMAND "/usr/local/bin/git"  submodule update --recursive --init 
    WORKING_DIRECTORY "/Users/davidepaollilo/Workspaces/C++/Thesis/_deps/imguizmo-src"
    RESULT_VARIABLE error_code
    )
endif()
if(error_code)
  message(FATAL_ERROR "Failed to update submodules in: '/Users/davidepaollilo/Workspaces/C++/Thesis/_deps/imguizmo-src'")
endif()

# Complete success, update the script-last-run stamp file:
#
execute_process(
  COMMAND ${CMAKE_COMMAND} -E copy
    "/Users/davidepaollilo/Workspaces/C++/Thesis/_deps/imguizmo-subbuild/imguizmo-populate-prefix/src/imguizmo-populate-stamp/imguizmo-populate-gitinfo.txt"
    "/Users/davidepaollilo/Workspaces/C++/Thesis/_deps/imguizmo-subbuild/imguizmo-populate-prefix/src/imguizmo-populate-stamp/imguizmo-populate-gitclone-lastrun.txt"
  RESULT_VARIABLE error_code
  )
if(error_code)
  message(FATAL_ERROR "Failed to copy script-last-run stamp file: '/Users/davidepaollilo/Workspaces/C++/Thesis/_deps/imguizmo-subbuild/imguizmo-populate-prefix/src/imguizmo-populate-stamp/imguizmo-populate-gitclone-lastrun.txt'")
endif()

