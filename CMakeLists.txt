cmake_minimum_required (VERSION 3.8)
project ("RayCastProject")

# Define MY_SOURCES to be a list of all the source files for my project
file(GLOB_RECURSE MY_SOURCES CONFIGURE_DEPENDS "${CMAKE_SOURCE_DIR}/src/*.c")
add_executable(RayCast "${MY_SOURCES}")

# This is useful to get an ASSETS_PATH in your IDE during development but you should comment this if you compile a release version and uncomment the next line
# target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC RESOURCES_PATH="${CMAKE_CURRENT_SOURCE_DIR}/resources")

# Uncomment this line to setup the ASSETS_PATH macro to the final assets directory when you share the project
# target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC RESOURCES_PATH="./resources/") 

add_subdirectory(Dependencies/SDL2)


target_link_libraries(RayCast PRIVATE SDL)
