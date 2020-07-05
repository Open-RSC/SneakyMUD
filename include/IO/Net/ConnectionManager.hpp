#pragma once
#include "../../external/asio.hpp"
#include "../Net/Connection.hpp"
#include <forward_list>

namespace sneaky {
namespace IO {
namespace Net {
	class ConnectionManager {
	public:
		explicit ConnectionManager(const int& a_port);
		void start();
		virtual void onConnect(std::shared_ptr<Connection> a_connection) = 0;
		virtual void onTimeout(std::shared_ptr<Connection> a_connection) = 0;
	protected:
		bool add(std::shared_ptr<Connection> a_connection);
		void remove(std::shared_ptr<Connection> a_connection);
	private:
		asio::io_service m_ioService;
		asio::ip::tcp::acceptor m_acceptor;
		std::forward_list<std::shared_ptr<Connection>> m_connections;
		std::mutex m_listMutex;
		void listen();
		void await(std::shared_ptr<Connection> a_connection);
	};
}}}