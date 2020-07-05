#pragma once
#include "../IOHandler.hpp"
#include "../Net/Connection.hpp"
#include "../Net/ConnectionManager.hpp"

namespace sneaky {
namespace IO {
namespace Net {
	class Net235 : IOHandler, ConnectionManager {
	public:
		Net235(const int& a_port);
		virtual void onConnect(std::shared_ptr<Connection> a_connection);
		virtual void onDisconnect(std::shared_ptr<Connection> a_connection);
	private:
		
	};
}}}