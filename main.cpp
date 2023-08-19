#include <iostream>
#include <chrono>
#include "loadBalancer.h"
#include "settings.h"
#include "settingsParser.h"
#include <deque>


int main(int argc, char *argv[]) {

    Settings settings;
    if(argc == 1 || argv[1] == "") {
        std::cerr << "Path to the settings file must be specified" << std::endl;
        return -1;
    }

    try {
        SettingsParser settingsParser(argv[1]);
        settingsParser.readParameters(settings);
        Server server(settings.host_ip, settings.port);
        LoadBalancer balancer(settings.destinationAddresses);
        uint64_t currentTime;
        std::deque<uint64_t> timeStamp;
        char buffer[4096];
        bool blockingRead = true;
        while(1) {
            const int size = server.read(buffer, blockingRead);
            if(blockingRead == false && size < 0) { continue; }
            currentTime = std::chrono::duration_cast<std::chrono::milliseconds>(
                                    std::chrono::system_clock::now().time_since_epoch()).count();
            if(timeStamp.size() <= settings.numberOfDatagrams) {
                timeStamp.push_back(currentTime);
                balancer.balanceLoad(server, buffer, size, settings.port);
            }
            if(!timeStamp.empty() && (currentTime - timeStamp.front() >= 1000)) {
                timeStamp.pop_front();
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
    catch(const std::invalid_argument& e) {
        std::cerr << e.what() << std::endl;
        return -1;
    }

    return 0;
}
