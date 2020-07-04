#include "../include/Server.hpp"
#include "../include/IO/Net/Net235.hpp"

using namespace sneaky;

Server::Server(const std::string& a_name, const int& a_port) : m_name(a_name), m_net235(a_port) {
}

const std::string& Server::getName() {
	return m_name;
}