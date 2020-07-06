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
		virtual void onConnect(std::shared_ptr<Connection> a_connection) = 0;
		virtual void onDisconnect(std::shared_ptr<Connection> a_connection) = 0;

		asio::io_service* getIOService();
		void listen();
	private:
		asio::io_service m_ioService;
		asio::ip::tcp::acceptor m_acceptor;
		PIDContainer m_connections;
		void awaitHeader(std::shared_ptr<Connection> a_connection);
		void awaitBody(std::shared_ptr<Connection> a_connection, const int& bytes);
	};

	enum Protocol {
		p204,
		p235
	};
}}}