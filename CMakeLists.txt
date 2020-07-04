#Top level CMakeLists.txt
cmake_minimum_required (VERSION 3.8)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project ("SneakyMUD")

list(APPEND SOURCE_FILES 
	"include/external/asio.hpp"
	"src/Server.cpp" "include/Server.hpp"
	"src/IO/IOHandler.cpp" "include/IO/IOHandler.hpp"
	"src/IO/Net/Net235.cpp" "include/IO/Net/Net235.hpp"
	"src/IO/Net/Connection.cpp" "include/IO/Net/Connection.hpp"
	"src/IO/Net/ConnectionManager.cpp" "include/IO/Net/ConnectionManager.hpp"
)

add_library(SneakyLib ${SOURCE_FILES})

add_executable(${CMAKE_PROJECT_NAME} "src/SneakyMUD.cpp" "include/SneakyMUD.hpp")
target_link_libraries(${CMAKE_PROJECT_NAME} SneakyLib)

add_subdirectory("tests")