#pragma once
#include "../../external/asio.hpp"
#include <stdlib.h>

namespace sneaky {
namespace IO {
namespace Net {
	class Connection {
	public:
		explicit Connection(asio::ip::tcp::socket a_socket);
		asio::ip::tcp::endpoint getEndpoint();
		asio::ip::tcp::socket* getSocket();
		char* getBuffer();
	private:
		asio::ip::tcp::socket m_socket;
		char m_readBuffer[5000];
	};
}}}