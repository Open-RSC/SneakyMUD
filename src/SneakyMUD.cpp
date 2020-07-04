#include <iostream>
#include "../include/Server.hpp"

int main() {
    sneaky::Server server("SneakyMUD", 43594);
    std::cout << server.getName() << " started." << std::endl;
    return 0;
}