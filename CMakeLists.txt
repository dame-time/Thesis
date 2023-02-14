cmake_minimum_required(VERSION 3.16)
project(Thesis)

list(PREPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

# Libigl
include(libigl)
include_directories(Math Math/Vector/ Math/Versor/ Math/Rotation/ Math/Point/ Math/Matrix/)

# Enable the target igl::glfw
igl_include(glfw)

# Add your project files
file(GLOB_RECURSE SOURCES "*.cpp" "*.hpp")

foreach(source ${SOURCES})
    if(source MATCHES "Build/" OR source MATCHES "_deps/" OR source MATCHES ".git/")
        list(REMOVE_ITEM SOURCES ${source})
    endif()
endforeach()

message("Sources:")
foreach(source ${SOURCES})
    message("  ${source}")
endforeach()

# Retrieve the include directories of the current project
get_property(includes DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY INCLUDE_DIRECTORIES)

# Print each directory
foreach(include_dir ${includes})
    message("Include directory: ${include_dir}")
endforeach()

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} PUBLIC igl::glfw)
target_include_directories(${PROJECT_NAME} PUBLIC ${includes})
