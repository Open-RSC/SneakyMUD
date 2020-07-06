#include "../include/Server.hpp"
using namespace sneaky;

Server::Server(const std::string& a_name) : m_name(a_name) {
}

const std::string& Server::getName() {
	return m_name;
}