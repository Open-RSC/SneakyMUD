#include "../../../include/IO/Net/ConnectionManager.hpp"
#include "../../../include/external/asio.hpp"
#include <iostream>
#include <forward_list>

using namespace sneaky::IO::Net;
using namespace asio;

ConnectionManager::ConnectionManager(const int& a_port) : m_acceptor(m_ioService, ip::tcp::endpoint(ip::tcp::v4(), a_port)){
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
    //TODO: Add a check on max # of allowed connections
    if (false)
        return false;

    std::forward_list<std::shared_ptr<Connection>> tempList;
    tempList.push_front(a_connection);

    std::lock_guard<std::mutex> lock(m_listMutex);
    m_connections.splice_after(m_connections.before_begin(), tempList);
    return true;
}

void ConnectionManager::remove(std::shared_ptr<Connection> a_connection) {
    std::cout << "Removing connection...";
    std::lock_guard<std::mutex> lock(m_listMutex);
    m_connections.remove(a_connection);
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
                 //Forced disconnect
                 remove(a_connection);
                 onTimeout(a_connection);
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