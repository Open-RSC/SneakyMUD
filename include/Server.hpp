#pragma once
#include <string>
#include "../include/IO/Net/Net235.hpp"

namespace sneaky{
    class Server {
    public:
        Server(const std::string& a_name, const int& a_port);

        const std::string& getName();
    private:
        const std::string m_name{ "default" };
        const IO::Net::Net235 m_net235;
    };
}