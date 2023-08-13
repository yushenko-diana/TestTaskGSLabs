#include <iostream>
#include <chrono>
#include "loadBalancer.h"
#include "settings.h"
#include "settingsParser.h"


int main(int argc, char *argv[]) {

    Settings settings;
    if(argv[1] == "") {
        std::cerr << "Path to the settings file must be specified" << std::endl;
        return -1;
    }

    try {
        SettingsParser settingsParser(argv[1]);
        settingsParser.readParameters(settings);
        Server server(settings.host_ip, settings.port);
        LoadBalancer balancer(settings.destinationAddresses,settings.port);

        unsigned long currentTime = std::chrono::duration_cast<std::chrono::milliseconds>(
                                    std::chrono::system_clock::now().time_since_epoch()).count();
        unsigned long previousTime = currentTime;
        int numberOfDatagrams = 0;
        char buffer[4096];
        while(1) {
            const int size = server.read(buffer, true);
            if(numberOfDatagrams < settings.numberOfDatagrams) {
                balancer.balanceLoad(server, buffer, size);
                ++numberOfDatagrams;
            }
            currentTime = std::chrono::duration_cast<std::chrono::milliseconds>(
                                    std::chrono::system_clock::now().time_since_epoch()).count();
            if(currentTime - previousTime >= 1000) {
                previousTime = currentTime;
                numberOfDatagrams = 0;
            }
        }
    }
    catch(const std::ios_base::failure& e) {
        std::cerr << e.what() << std::endl;
        return -1;
    }
    catch(const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
        return -1;
    }

    return 0;
}