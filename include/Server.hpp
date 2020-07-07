#pragma once
#include <string>
#include "../include/IO/Net/NetworkHandler.hpp"
#include "../include/IO/Net/Net235.hpp"
#include <string>

namespace sneaky{
    class Server {
    public:
        Server(const std::string& a_name, const int& a_port, const int& a_maxConnections, const IO::Net::Protocol& a_protocol);
        const std::string& getName();

        void start();
    private:
        void loop();
        const std::string m_name{ "default" };
        const IO::Net::Protocol m_protocol;
        std::shared_ptr<IO::Net::NetworkHandler> m_networkHandler{ nullptr };
    };
}