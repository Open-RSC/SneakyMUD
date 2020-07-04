#pragma once
#include "../../external/asio.hpp"
#include <stdlib.h>

namespace sneaky {
namespace IO {
namespace Net {
	class Connection : public std::enable_shared_from_this<Connection> {
	public:
		Connection(asio::ip::tcp::socket a_socket);
		const asio::ip::tcp::socket& getSocket();
	private:
		const asio::ip::tcp::socket m_socket;
	};
}}}