#pragma once
#include "../Net/NetworkHandler.hpp"

namespace sneaky {
namespace IO {
namespace Net {
	class Net235 : public NetworkHandler {
	public:
		Net235(const int& a_port, const int& a_maxConnections);
		virtual void onConnect(std::shared_ptr<Connection> a_connection);
		virtual void onDisconnect(std::shared_ptr<Connection> a_connection);
	private:
		
	};
}}}