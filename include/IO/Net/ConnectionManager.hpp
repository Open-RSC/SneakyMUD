#pragma once
#include "../../external/asio.hpp"
#include "../Net/Connection.hpp"

namespace sneaky {
namespace IO {
namespace Net {
	class ConnectionManager {
	public:
		//TODO: Add this to a config
		static const int MAX_CONNECTIONS = 10;
		explicit ConnectionManager(const int& a_port);
		void start();
		virtual void onConnect(std::shared_ptr<Connection> a_connection) = 0;
		virtual void onDisconnect(std::shared_ptr<Connection> a_connection) = 0;
	protected:
		bool add(std::shared_ptr<Connection> a_connection);
		bool remove(std::shared_ptr<Connection> a_connection);
	private:
		asio::io_service m_ioService;
		asio::ip::tcp::acceptor m_acceptor;
		std::shared_ptr<Connection> m_connections[MAX_CONNECTIONS];
		int m_connectionCount{ 0 };
		std::mutex m_listMutex;
		void listen();
		void await(std::shared_ptr<Connection> a_connection);
	};
}}}