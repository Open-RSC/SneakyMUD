#include "../../../include/IO/Net/Net235.hpp"
#include <iostream>
using namespace sneaky::IO::Net;

Net235::Net235(const int& a_port, const int& a_maxConnections) : NetworkHandler(a_port, a_maxConnections) {
}

void Net235::onConnect(std::shared_ptr<Connection> a_connection) {
    std::cout << a_connection->getEndpoint().address().to_string() << std::endl;

}

void Net235::onDisconnect(std::shared_ptr<Connection> a_connection) {

}