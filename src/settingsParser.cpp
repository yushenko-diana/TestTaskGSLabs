#include "settingsParser.h"
#include "settings.h"
#include <sstream>
#include <algorithm>
#include <exception>
#include <stack>

namespace {
const char* HOST_IP_KEY = "host_ip";
const char* PORT_KEY = "port";
const char* NUMBER_OF_DATAGRAMS_KEY = "numberOfDatagrams";
const char* DESTINATION_ADDRESSES_KEY = "destinationAddresses";
}

SettingsParser::SettingsParser(std::string filename) {
    file.open(filename);
    if(!file.is_open()) {
        throw std::runtime_error("Unable to open file");
    }
}

void SettingsParser::readParameters(Settings& settings) {
    std::string str;
    std::vector<std::string> data;
    while(file.peek() != EOF) {

        getline(file, str);
        if(str.empty()) { continue; };
        str.erase(remove(str.begin(),str.end(),' '),str.end());
        int equalPose = str.find('=');
        if(equalPose == -1 || str.empty() || str.substr(0, equalPose).empty() || str.substr(equalPose+1).empty()) {
            continue;
        }
        const std::string key = str.substr(0, equalPose);
        std::string value = str.substr(equalPose+1);
        if(key == PORT_KEY && isNumberValid(value)) {
            settings.port = std::stoi(value);
        }
        if(key == NUMBER_OF_DATAGRAMS_KEY && isNumberValid(value)) {
            settings.numberOfDatagrams = std::stoi(value);
        }
        if(key == HOST_IP_KEY && isIPAddressCorrect(value)) {
            settings.host_ip = value;
        }
        if(key == DESTINATION_ADDRESSES_KEY && isItArray(value)) {
            parseArray(data, value);
            if(!data.empty() && isIPAdressesCorrect(data)) { 
                settings.destinationAddresses = data;
            }
        }
        if(key == NUMBER_OF_DATAGRAMS_KEY && isNumberValid(value)) {
            settings.numberOfDatagrams = std::stoi(value);
        }
    }
}



void SettingsParser::splitString(std::vector<std::string>& array, const std::string& str, const char delimiter) {
    if(str.empty()) { return; }
    std::stringstream sstream(str);
    std::string item;
    while (getline(sstream, item, delimiter))
    {   if(item.empty()) { continue; }
        array.push_back(item);
    }
}

bool SettingsParser::isBracketSequenceRight(const std::string& str) {
    if(str.empty()) { return false; }
    std::stack<char> brackets;
    for(auto c: str) {
        if(c == ']' && brackets.empty()) {
            return false;
        }
        if(c == '[') { 
            brackets.push(c);
        }
        if(c == ']' && !brackets.empty() && brackets.top() == '[') {
            brackets.pop();
        }
    }
    if(brackets.size() == 0) { return true; }
    else { return false; }
}
void SettingsParser::parseArray(std::vector<std::string>& array, const std::string& str) {
    if(str.empty()) { return; }
    if(!isBracketSequenceRight(str)) { return; } 
    int openBracketPose = str.find_last_of('[');
    int closeBracketPose = str.find_first_of(']');
    std::string line = str.substr(openBracketPose+1, closeBracketPose-1);
    splitString(array, line,',');
}

bool SettingsParser::isItIPAddress(const std::string& str) {
    if(str.empty()) { return false; }
    size_t numOfPoints = std::count(str.begin(), str.end(), '.');
    if(numOfPoints == 3) { return true; }
    return false;
}

bool SettingsParser::isIPAddressCorrect(const std::string& str) {
    if(!isItIPAddress(str) || str.size() < 7 || str.size() > 15) { return false; }
    std::vector<std::string> octets;
    splitString(octets, str,'.');
    for(auto octet: octets) {
        if(!std::all_of(octet.begin(), octet.end(), ::isdigit)) { return false; }
        if(std::stoi(octet) > 255) { return false; }
    }
        
    return true;
}

bool SettingsParser::isItArray(const std::string& str) {
    if(str.empty()) { return false; }
    if(str.find('[') != -1 && str.find(']') != -1) {
        return true;
    }
    return false;
}

bool SettingsParser::isIPAdressesCorrect(std::vector<std::string> array) {
    if(array.empty()) { return false; }
    for(auto c: array) {
        if(!isIPAddressCorrect(c)) { return false; }
    }
    return true;    
}

bool SettingsParser::isNumberValid(const std::string str) {
    if((!std::all_of(str.begin(), str.end(), ::isdigit)) || str.empty()) { return false; }
    return true;
}


SettingsParser::~SettingsParser() {
    if(file.is_open()) {
        file.close();
    }
}


