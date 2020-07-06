#include "../../../include/IO/Net/NetworkHandler.hpp"
#include "../../../include/external/asio.hpp"
#include <iostream>
#include <forward_list>

using namespace sneaky::IO::Net;
using namespace asio;

NetworkHandler::NetworkHandler(const int& a_port, const int& a_maxConnections)
    : m_acceptor(m_ioService, ip::tcp::endpoint(ip::tcp::v4(), a_port)), m_connections(a_maxConnections) {
}

 void NetworkHandler::listen() {
    m_acceptor.async_accept(
        [this](error_code ec, ip::tcp::socket socket) {
            if (!ec) {
                std::shared_ptr<Connection> newConnection = std::make_shared<Connection>(std::move(socket));
                if (m_connections.add(newConnection)) {
                    onConnect(newConnection);
                    awaitHeader(newConnection);
                }
            }
            listen();
        }
    );
    m_ioService.run();
}

 asio::io_service* NetworkHandler::getIOService() {
     return &m_ioService;
 }

 void NetworkHandler::awaitHeader(const std::shared_ptr<Connection> a_connection) {
     //TODO Config variable for header size?
     asio::async_read(*a_connection->getSocket(), asio::buffer(a_connection->getBuffer(), 4),
         [this, a_connection](asio::error_code ec, std::size_t length) {
             if (ec == asio::error::eof || ec == asio::error::connection_reset) {
                 onDisconnect(a_connection);
                 m_connections.remove(a_connection);
             }
             else {
                 for (int i = 0; i < length; i++)
                     std::cout << std::hex << a_connection->getBuffer()[i] << " ";
                 std::cout << std::endl;
                 awaitBody(a_connection, 4);
             }
         }
     );
 }

 void NetworkHandler::awaitBody(const std::shared_ptr<Connection> a_connection, const int& bytes) {
     asio::async_read(*a_connection->getSocket(), asio::buffer(a_connection->getBuffer(), bytes),
         [this, a_connection](asio::error_code ec, std::size_t length) {
             if (ec == asio::error::eof || ec == asio::error::connection_reset) {
                 onDisconnect(a_connection);
                 m_connections.remove(a_connection);
             }
             else {
                 for (int i = 0; i < length; i++)
                     std::cout << std::hex << a_connection->getBuffer()[i] << " ";
                 std::cout << std::endl;
                 awaitHeader(a_connection);
             }
         }
     );
 }