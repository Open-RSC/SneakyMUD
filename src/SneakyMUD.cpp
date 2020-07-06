#include <iostream>
#include "../include/Server.hpp"

int main() {
    sneaky::Server server("SneakyMUD");
    std::cout << server.getName() << " started." << std::endl;
    return 0;
}