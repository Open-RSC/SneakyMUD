#include "../../../include/IO/Net/Connection.hpp"
#include "../../../include/external/asio.hpp"

using namespace sneaky::IO::Net;
Connection::Connection(asio::ip::tcp::socket a_socket) : m_socket(std::move(a_socket)){

}
const asio::ip::tcp::socket& Connection::getSocket() {
	return m_socket;
}