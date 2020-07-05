#include "../../../include/IO/Net/ConnectionManager.hpp"
#include "../../../include/external/asio.hpp"
#include <iostream>
#include <forward_list>

using namespace sneaky::IO::Net;
using namespace asio;

ConnectionManager::ConnectionManager(const int& a_port) : m_acceptor(m_ioService, ip::tcp::endpoint(ip::tcp::v4(), a_port)){
    for (int i = 0; i < MAX_CONNECTIONS; ++i)
        m_connections[i] = nullptr;
}

void ConnectionManager::start() {
    try {
        listen();
        m_ioService.run();
    }
    catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}

bool ConnectionManager::add(std::shared_ptr<Connection> a_connection)
{
    //TODO: MAX_CONNECTIONS needs to be moved to a config
    if (m_connectionCount == MAX_CONNECTIONS)
        return false;

    std::lock_guard<std::mutex> lock(m_listMutex);
    for (int i = 0; i < MAX_CONNECTIONS; ++i) {
        if (m_connections[i] == nullptr) {
            m_connections[i] = a_connection;
            m_connectionCount += 1;
            std::cout << m_connectionCount << std::endl;
            return true;
        }
    }

    std::cerr << "An error has occurred in ConnectionManager::add";
    return false;
}

bool ConnectionManager::remove(std::shared_ptr<Connection> a_connection) {
    std::lock_guard<std::mutex> lock(m_listMutex);
    for (int i = 0; i < MAX_CONNECTIONS; ++i) {
        if (m_connections[i] == a_connection) {
            m_connections[i] = nullptr;
            m_connectionCount -= 1;
            std::cout << m_connectionCount << std::endl;
            return true;
        }
    }

    return false;
}

 void ConnectionManager::listen() {
    m_acceptor.async_accept(
        [this](error_code ec, ip::tcp::socket socket) {
            if (!ec) {
                std::shared_ptr<Connection> newConnection = std::make_shared<Connection>(std::move(socket));
                if (add(newConnection)) {
                    onConnect(newConnection);
                    await(newConnection);
                }
            }
            listen();
        }
    );
}

 void ConnectionManager::await(const std::shared_ptr<Connection> a_connection) {
     asio::async_read(*a_connection->getSocket(), asio::buffer(a_connection->getBuffer() , 4),
         [this, a_connection](asio::error_code ec, std::size_t length) {
             if (ec == asio::error::eof || ec == asio::error::connection_reset) {
                 onDisconnect(a_connection);
                 remove(a_connection);
             }
             else {
                 for (int i = 0; i < length; i++)
                     std::cout << std::hex << a_connection->getBuffer()[i] << " ";
                 std::cout << std::endl;
                 await(a_connection);
             }
         }
     );
 }