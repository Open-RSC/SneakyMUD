#pragma once
#include "../IOHandler.hpp"
#include "../Net/ConnectionManager.hpp"

namespace sneaky {
namespace IO {
namespace Net {
	class Net235 : IOHandler {
	public:
		Net235(const int& a_port);
	private:
		ConnectionManager m_connectionManager;
	};
}}}