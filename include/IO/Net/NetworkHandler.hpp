#pragma once
#include "../../external/asio.hpp"
#include "../Net/Connection.hpp"
#include "../Net/PIDContainer.hpp"
#include <string>

namespace sneaky {
namespace IO {
namespace Net {
	class NetworkHandler {
	public:
		NetworkHandler(const int& a_port, const int& a_maxConnections);
		virtual void onConnect(const std::shared_ptr<Connection>& a_connection) = 0;
		virtual void onDisconnect(const std::shared_ptr<Connection>& a_connection) = 0;

		asio::io_service* getIOService();
		void listen();
	private:
		asio::io_service m_ioService;
		asio::ip::tcp::acceptor m_acceptor;
		PIDContainer m_connections;
		void awaitHeader(const std::shared_ptr<Connection>& a_connection);
		void awaitBody(const std::shared_ptr<Connection>& a_connection, const int& bytes);
	};

	enum class Protocol {
		p204,
		p235
	};
}}}