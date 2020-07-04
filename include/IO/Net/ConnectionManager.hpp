#pragma once
#include "../../external/asio.hpp"
#include "../../IO/Net/Connection.hpp"

namespace sneaky {
namespace IO {
namespace Net {
	class ConnectionManager {
	public:
		ConnectionManager(const int& a_port);
		void start();
	private:
		asio::io_service m_ioService;
		asio::ip::tcp::acceptor m_acceptor;
		const std::list<std::shared_ptr<Connection>> m_connections;
		
		void listen();
	};
}}}