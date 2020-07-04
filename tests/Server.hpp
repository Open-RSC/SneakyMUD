#include "../include/external/catch.hpp"
#include "../include/Server.hpp"

SCENARIO("Server", "[server]") {

    GIVEN("A server with name test") {
        sneaky::Server server("test", 54000);
        REQUIRE_FALSE(server.getName().empty());
        REQUIRE(server.getName() == "test");
    }
}