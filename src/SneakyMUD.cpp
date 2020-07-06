#include <iostream>
#include "../include/Server.hpp"

int main() {
    sneaky::Server server("SneakyMUD", 43594, 2, sneaky::IO::Net::Protocol::p235);
    server.start();    
    return 0;
}