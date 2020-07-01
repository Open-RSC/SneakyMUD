cmake_minimum_required (VERSION 3.8)

add_executable(TestSuite
	"../include/external/catch.hpp"
	"TestSuite.cpp"
	"Server.hpp"
)

target_link_libraries(TestSuite SneakyLib)