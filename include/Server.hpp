#pragma once
#include <string>

namespace sneaky{
    class Server {
    public:
        Server(const std::string& a_name);

        const std::string& getName();
    private:
        const std::string m_name{ "default" };
    };
}