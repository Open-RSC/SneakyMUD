#include "../../../include/IO/Net/PIDContainer.hpp"
#include <iostream>

using namespace sneaky::IO::Net;

PIDContainer::PIDContainer(const int& a_maxConnections) : m_users(5, nullptr), m_maxConnections(a_maxConnections) {
}


bool PIDContainer::add(std::shared_ptr<Connection> a_connection)
{
    std::lock_guard<std::mutex> lock(m_listMutex);

    if (m_curConnections == m_maxConnections)
        return false;

    for (int i = 0; i < m_maxConnections; ++i) {
        if (m_users[i] == nullptr) {
            m_users[i] = a_connection;
            m_curConnections += 1;
            return true;
        }
    }

    std::cerr << "An error has occurred in PIDContainer::add";
    return false;
}

bool PIDContainer::remove(std::shared_ptr<Connection> a_connection) {
    std::lock_guard<std::mutex> lock(m_listMutex);
    int size = std::min(m_maxConnections, (int)m_users.size());
    for (int i = 0; i < size; ++i) {
        if (m_users[i] == a_connection) {
            m_users[i] = nullptr;
            m_curConnections -= 1;
            return true;
        }
    }

    return false;
}
