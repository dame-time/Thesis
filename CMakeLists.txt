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

# FetchContent module
include(FetchContent)

# YAML-CPP
FetchContent_Declare(
  yaml_cpp
  GIT_REPOSITORY https://github.com/jbeder/yaml-cpp.git
  GIT_TAG yaml-cpp-0.7.0
)

FetchContent_MakeAvailable(yaml_cpp)

# Add your project files
file(GLOB_RECURSE SOURCES "*.cpp" "*.hpp")

foreach(source ${SOURCES})
    if(source MATCHES "Build/" OR source MATCHES "_deps/" OR source MATCHES ".git/")
        list(REMOVE_ITEM SOURCES ${source})
    endif()
endforeach()

add_executable(${PROJECT_NAME} ${SOURCES})
target_compile_options(${PROJECT_NAME} PUBLIC -g -O2)
target_link_libraries(${PROJECT_NAME} PUBLIC igl::glfw igl::imgui igl_restricted::triangle igl::core yaml-cpp)
target_include_directories(${PROJECT_NAME} PUBLIC ${includes} ${yaml_cpp_SOURCE_DIR}/include)
