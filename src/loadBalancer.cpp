#include "loadBalancer.h"
#include <algorithm>
#include <chrono>

LoadBalancer::LoadBalancer(const std::vector<std::string>& destinationAddresses, int port):destinationAddresses(destinationAddresses), port(port) {
    currentIt = this->destinationAddresses.cbegin();
}

void LoadBalancer::balanceLoad(const Server& server, const char* buffer, int size) {

    server.write(buffer, size, true, *currentIt, port);
    ++currentIt;
    if(currentIt == destinationAddresses.cend()) {
        currentIt = destinationAddresses.cbegin();
    }
}