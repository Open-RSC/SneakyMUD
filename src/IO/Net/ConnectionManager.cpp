#include "../../../include/IO/Net/ConnectionManager.hpp"
#include "../../../include/IO/Net/Connection.hpp"
#include "../../../include/external/asio.hpp"
#include <iostream>

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

 void ConnectionManager::listen() {
    m_acceptor.async_accept(
        [this](error_code ec, ip::tcp::socket socket) {
            if (!ec) {
                std::cout << "New connection" << std::endl;
                std::make_shared<Connection>(std::move(socket));
            }
            listen();
        }
    );
}