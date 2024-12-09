cmake_minimum_required (VERSION 3.8)
project (SDL)

add_library(SDL INTERFACE)

target_include_directories(SDL INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/include")

target_link_libraries(SDL INTERFACE
	"${CMAKE_CURRENT_SOURCE_DIR}/lib/x64/SDL2main.lib"
	"${CMAKE_CURRENT_SOURCE_DIR}/lib/x64/SDL2.lib")