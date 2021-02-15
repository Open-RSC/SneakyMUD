#include "../../../include/IO/Net/Connection.hpp"
#include <iostream>

using namespace sneaky::IO::Net;
Connection::Connection(asio::ip::tcp::socket a_socket) : m_socket(std::move(a_socket)), m_readBuffer(){
}

char* Connection::getBuffer() {
	return m_readBuffer;
}

asio::ip::tcp::socket* Connection::getSocket() {
	return &m_socket;
}

asio::ip::tcp::endpoint Connection::getEndpoint() {
	return m_socket.remote_endpoint();
}