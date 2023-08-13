#include "settingsParser.h"
#include "settings.h"

namespace {
const char* HOST_IP_KEY = "host_ip";
const char* PORT_KEY = "port";
const char* NUMBER_OF_DATAGRAMS_KEY = "numberOfDatagrams";
const char* DESTINATION_ADDRESSES_KEY = "destinationAddresses";
}

SettingsParser::SettingsParser(std::string filename) {
    file.open(filename);
}

void SettingsParser::readParameters(Settings& settings) {
    std::string tempString;
    while(file.peek() != EOF) {
        getline(file,tempString);
        int equalPose = tempString.find('=');
        std::string value;
        const std::string key = tempString.substr(0, equalPose);
        if(key == HOST_IP_KEY) {
            settings.host_ip = tempString.substr(equalPose+1);
            continue;
        }
        if(key == PORT_KEY) {
            settings.port = std::stoi(tempString.substr(equalPose+1));
            continue;
        }
        if(key == NUMBER_OF_DATAGRAMS_KEY) {
            settings.numberOfDatagrams = std::stoi(tempString.substr(equalPose+1));
            continue;
        }
        if(key == DESTINATION_ADDRESSES_KEY) {
            const int leftBracketPose = tempString.find('[');
            std::string str;
            for(auto character = tempString.begin() + leftBracketPose + 1; character < tempString.end(); ++character) {
                if(*character == ' ' || *character == ']') {
                    settings.destinationAddresses.push_back(str);
                    str.clear();
                    continue;
                }
                str += *character;
            }
            continue;
        }
    }
}

SettingsParser::~SettingsParser() {
    if(file.is_open()) {
        file.close();
    }
}


