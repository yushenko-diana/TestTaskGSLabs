#include "settingsParser.h"
#include "settings.h"
#include "unordered_map"
#include <exception>
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
    std::unordered_map<std::string, std::string> tempSettings;
    while(file.peek() != EOF) {
        getline(file,tempString);
        int equalPose = tempString.find('=');
        std::string value;
        const std::string key = tempString.substr(0, equalPose);
        tempSettings[key] = tempString.substr(equalPose+1);
    }
    if(tempSettings.find(HOST_IP_KEY) == tempSettings.end() || tempSettings.find(PORT_KEY) == tempSettings.end() ||
       tempSettings.find(NUMBER_OF_DATAGRAMS_KEY) == tempSettings.end() || tempSettings.find(NUMBER_OF_DATAGRAMS_KEY) == tempSettings.end() ||
       tempSettings.find(DESTINATION_ADDRESSES_KEY) == tempSettings.end()) {
        throw std::invalid_argument("Bad file");
    }

    tempString = tempSettings[DESTINATION_ADDRESSES_KEY];
    const int leftBracketPose = tempString.find('[');
    std::string str;
    for(auto character = tempString.begin() + leftBracketPose + 1; character < tempString.end(); ++character) {
        if(*character == ' ' || *character == ']') {
            if(!str.empty()) {
                settings.destinationAddresses.push_back(str);
            }
            str.clear();
            continue;
        }
        str += *character;
    }
    settings.host_ip = tempSettings[HOST_IP_KEY];
    settings.port = std::stoi(tempSettings[PORT_KEY]);
    settings.numberOfDatagrams = std::stoi(tempSettings[NUMBER_OF_DATAGRAMS_KEY]);
    if(settings.destinationAddresses.empty()) {
        throw std::invalid_argument("There are no nodes adresses");
    }
}

SettingsParser::~SettingsParser() {
    if(file.is_open()) {
        file.close();
    }
}


