#include "../include/external/catch.hpp"
#include "../include/IO/Net/PIDContainer.hpp"
#include "../include/IO/Net/Connection.hpp"
#include <memory>

using namespace sneaky::IO::Net;
SCENARIO("PIDContainer", "[pidcontainer]") {

    GIVEN("A PIDContainer") {
        PIDContainer pidContainer(2);

        //Test max connections
        REQUIRE(pidContainer.getMaxConn() == 2);

        //Test connections
        asio::io_context io_context;
        asio::ip::tcp::socket mocket1(io_context);
        asio::ip::tcp::socket mocket2(io_context);
        asio::ip::tcp::socket mocket3(io_context);
        std::shared_ptr<Connection> conn1 = std::make_shared<Connection>(std::move(mocket1));
        std::shared_ptr<Connection> conn2 = std::make_shared<Connection>(std::move(mocket2));
        std::shared_ptr<Connection> conn3 = std::make_shared<Connection>(std::move(mocket3));

        //Test limited capacity
        REQUIRE(pidContainer.getCurrentConn() == 0);
        REQUIRE(pidContainer.add(conn1));
        REQUIRE(pidContainer.add(conn2));
        REQUIRE_FALSE(pidContainer.add(conn3));
        REQUIRE(pidContainer.getCurrentConn() == 2);

        //Test remove
        REQUIRE(pidContainer.remove(conn1));
        REQUIRE(pidContainer.getCurrentConn() == 1);
        REQUIRE(pidContainer.getUserByPID(0) == nullptr);
        REQUIRE(pidContainer.getUserByPID(1) == conn2);

        //Test add to a previously removed spot
        REQUIRE(pidContainer.add(conn3));
        REQUIRE(pidContainer.getCurrentConn() == 2);
        REQUIRE(pidContainer.getUserByPID(0) == conn3);
        REQUIRE(pidContainer.getUserByPID(1) == conn2);

        //Test clear
        REQUIRE(pidContainer.remove(conn2));
        REQUIRE(pidContainer.getUserByPID(1) == nullptr);
        REQUIRE(pidContainer.remove(conn3));
        REQUIRE(pidContainer.getUserByPID(0) == nullptr);
        REQUIRE(pidContainer.getCurrentConn() == 0);
    }
}