#include "../../../include/IO/Net/Net235.hpp"
using namespace sneaky::IO::Net;

Net235::Net235(const int& a_port) : m_connectionManager(a_port) {
	m_connectionManager.start();
}