#include "../include/Server.hpp"
#include "../include/IO/Net/NetworkHandler.hpp"
#include "../include/IO/Net/Net235.hpp"
#include <iostream>
#include <string>
using namespace sneaky;

Server::Server(const std::string& a_name, const int& a_port, const int& a_maxConnections, const IO::Net::Protocol& a_protocol) : m_name(a_name), m_protocol(a_protocol) {
    if (a_protocol == IO::Net::Protocol::p204) {        
    }
    else if (a_protocol == IO::Net::Protocol::p235) {
        m_networkHandler = std::make_shared<IO::Net::Net235>(a_port, a_maxConnections);
    }
}

void Server::start() {
    if (m_networkHandler == nullptr) {
        std::cerr << "Invalid protocol selected" << std::endl;
        return;
    }
	std::cout << m_name << " starting.." << std::endl;
    try {
        m_networkHandler->listen();
        m_networkHandler->getIOService()->run();
    }
    catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}
const std::string& Server::getName() {
	return m_name;
}