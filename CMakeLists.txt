cmake_minimum_required (VERSION 3.8)
project (RayCastProject)

add_subdirectory(Dependencies/SDL2)


# Define MY_SOURCES to be a list of all the source files for my project
file(GLOB_RECURSE MY_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c")
add_executable("${CMAKE_PROJECT_NAME}")
target_sources("${CMAKE_PROJECT_NAME}" PRIVATE ${MY_SOURCES})

# This is useful to get an ASSETS_PATH in your IDE during development but you should comment this if you compile a release version and uncomment the next line
# target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC RESOURCES_PATH="${CMAKE_CURRENT_SOURCE_DIR}/resources")

# Uncomment this line to setup the ASSETS_PATH macro to the final assets directory when you share the project
# target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC RESOURCES_PATH="./resources/") 


target_include_directories("${CMAKE_PROJECT_NAME}" PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")

target_link_libraries("${CMAKE_PROJECT_NAME}" PRIVATE SDL)
