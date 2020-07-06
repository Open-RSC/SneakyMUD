#pragma once
#include "../Net/Connection.hpp"
#include <memory>
#include <vector>
namespace sneaky {
namespace IO {
namespace Net {
	class PIDContainer {
	public:
		PIDContainer(const int& a_maxConnections);
		bool add(std::shared_ptr<Connection> a_connection);
		bool remove(std::shared_ptr<Connection> a_connection);
	private:
		std::mutex m_listMutex;
		const int m_maxConnections{ 0 };
		int m_curConnections{ 0 };
		std::vector<std::shared_ptr<Connection>> m_users;
	};
}
}
}