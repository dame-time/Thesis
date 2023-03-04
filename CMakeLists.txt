cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_COMPILER /usr/bin/clang++)
set(CMAKE_CXX_STANDARD 11)

message("Compiler in use: ${CMAKE_CXX_COMPILER}")

project(Thesis)

option(LIBIGL_WITH_OPENGL_GLFW_IMGUI "Use ImGui" ON)
option(LIBIGL_RESTRICTED_TRIANGLE "Build target igl_restricted::triangle" ON)

list(PREPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

# Libigl
include(libigl)
include_directories(Math Math/Vector/ Math/Versor/ Math/Rotation/ Math/Point/ Math/Matrix/ Core/)

# Enable the target igl::glfw
igl_include(core)
igl_include(glfw)
igl_include(imgui)
igl_include(restricted triangle)

# Add your project files
file(GLOB_RECURSE SOURCES "*.cpp" "*.hpp")

foreach(source ${SOURCES})
    if(source MATCHES "Build/" OR source MATCHES "_deps/" OR source MATCHES ".git/")
        list(REMOVE_ITEM SOURCES ${source})
    endif()
endforeach()

# message("Sources:")
# foreach(source ${SOURCES})
#     message("  ${source}")
# endforeach()

# Retrieve the include directories of the current project
get_property(includes DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY INCLUDE_DIRECTORIES)

# Print each directory
# foreach(include_dir ${includes})
# message("Include directory: ${include_dir}")
# endforeach()
# message(${CMAKE_CURRENT_SOURCE_DIR})

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} PUBLIC igl::glfw igl::imgui igl_restricted::triangle igl::core)
target_include_directories(${PROJECT_NAME} PUBLIC ${includes})
