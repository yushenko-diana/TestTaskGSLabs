#include "loadBalancer.h"
#include <algorithm>

LoadBalancer::LoadBalancer(const std::vector<std::string>& destinationAddresses):destinationAddresses(destinationAddresses) {
    if(destinationAddresses.empty()) {
        throw std::invalid_argument("Bad destination addresses");
    }
    currentIt = this->destinationAddresses.cbegin();
}

void LoadBalancer::balanceLoad(const Server& server, const char* buffer, int size, const int port) {

    server.write(buffer, size, true, *currentIt, port);
    ++currentIt;
    if(currentIt == destinationAddresses.cend()) {
        currentIt = destinationAddresses.cbegin();
    }
}