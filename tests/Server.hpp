#include "../include/external/catch.hpp"
#include "../include/Server.h"

SCENARIO("Server", "[server]") {

    GIVEN("A vector with some items") {
        Server server("test");
        REQUIRE_FALSE(server.name_.empty());
        REQUIRE(server.name_ == "test");
    }
}