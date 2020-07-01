#Top level CMakeLists.txt
cmake_minimum_required (VERSION 3.8)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project ("SneakyMUD")

list(APPEND SOURCE_FILES 
	"include/external/asio.hpp"
	"src/Server.cpp" "include/Server.h"
	"src/IO/IOHandler.cpp" "include/IO/IOHandler.h"
	"src/IO/Net235.cpp" "include/IO/Net235.h"
)

add_library(SneakyLib ${SOURCE_FILES})

add_executable(${CMAKE_PROJECT_NAME} "src/SneakyMUD.cpp" "include/SneakyMUD.h")
target_link_libraries(${CMAKE_PROJECT_NAME} SneakyLib)

add_subdirectory("tests")