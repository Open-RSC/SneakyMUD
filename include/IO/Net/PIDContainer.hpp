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
		bool remove(const std::shared_ptr<Connection>& a_connection);

		const int& getMaxConn();
		const int& getCurrentConn();
		const std::shared_ptr<Connection>& getUserByPID(const int& a_PID);
	private:
		std::mutex m_listMutex;
		const int m_maxConnections{ 0 };
		int m_curConnections{ 0 };
		std::vector<std::shared_ptr<Connection>> m_users;
	};
}
}
}