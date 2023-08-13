#include "server.h"
#include <stdexcept>

Server::Server(const std::string ipAddress, const int port) {

    serverSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if(serverSocket == -1) {
        throw std::runtime_error(std::string("unable to create server socket: ") + strerror(errno));
    }

    struct sockaddr_in serverAddr;
    serverAddr.sin_addr.s_addr = inet_addr(ipAddress.c_str());
    serverAddr.sin_port = htons(port);
    serverAddr.sin_family = AF_INET;

    const int bindRes = bind(serverSocket,(sockaddr*)&serverAddr,sizeof(serverAddr));
    if(bindRes == -1) {
        throw std::runtime_error(std::string("unable to bind server socket: ") + strerror(errno));
    }
}

int Server::read(char* buffer, bool blockRead) {
    socklen_t addrLen = sizeof(senderAddr);
    int readRes;
    if(!blockRead) {
        readRes = recvfrom(serverSocket, buffer, sizeof(buffer), 0, (struct sockaddr*)&senderAddr, &addrLen);
    } else {
        readRes = recvfrom(serverSocket, buffer, sizeof(buffer), MSG_DONTWAIT, (struct sockaddr*)&senderAddr, &addrLen);
    }

    if(readRes == -1) {
        std::cerr << "unable to read" << strerror(errno) << std::endl;
    }
    return readRes;

}

int Server::write(const char* buffer, int datagramaSize, bool blockWrite, std::string ipAddr, int port) const {
    int writeRes;
    struct sockaddr_in sendAddr;
    memset(&sendAddr, 0, sizeof(sendAddr));
    if(ipAddr.empty()) {
        writeRes =  send(serverSocket,(void*)buffer, datagramaSize,0);
    } else {
        sendAddr.sin_addr.s_addr = inet_addr(ipAddr.c_str());
        sendAddr.sin_port = htons(port);
        sendAddr.sin_family = AF_INET;
        writeRes = sendto(serverSocket,(void*)buffer, datagramaSize,0,(sockaddr*)&sendAddr,sizeof(sendAddr));
    }
    if(writeRes == -1) {
        std::cerr << "unable to write" << strerror(errno) << std::endl;
    }
    return writeRes;
}