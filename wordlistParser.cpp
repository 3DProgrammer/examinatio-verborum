//
// Created by miles on 16/6/22.
//

#include "wordlistParser.h"
#include <iostream>
#include <fstream>
#include <sstream>
std::map<std::string,bibliotheca::Gender> WordList::stringToGender={{"m",bibliotheca::Gender::m},{"f",bibliotheca::Gender::f},{"n",bibliotheca::Gender::n}};
std::map<std::string,int> WordList::stringToDeclension={{"1",1},{"2",2},{"3",3},{"4",4},{"5",5}};
std::vector<std::string> split(const std::string &line, char splitter, char quotes) {
    std::vector<std::string> result;
    if (line.empty()) {
        return result;
    }
    int last_index = 0;
    bool quoting = false;
    for (int i = 0; i < line.size(); ++i) {
        if (line[i] == quotes) {
            if (quoting) {
                quoting = false;
                if (i > last_index) {
                    result.push_back(line.substr(last_index, i - last_index));
                }
                last_index = i + 1;
            } else {
                quoting = true;
                if (i > last_index) {
                    result.push_back(line.substr(last_index, i - last_index));
                }
                last_index = i + 1;
            }
        }
        if (line[i] == splitter && !quoting) {
            if (i > last_index) {
                result.push_back(line.substr(last_index, i - last_index));
            }
            last_index = i + 1;
        }
    }
    if (line.size() > last_index) {
        result.push_back(line.substr(last_index, line.size() - last_index));
    }
    return result;
}

WordList WordList::fromFilename(const std::string &fileName) { // TODO: Error checking for user input and non-ASCII support.
    std::ifstream infile(fileName);
    std::stringstream s;
    s<<infile.rdbuf();
    return WordList::fromData(s.str());
//
//    std::string line;
//    getline(infile, line);
//    std::string versionCheck = line;
//    versionCheck.resize(7);
//    if (versionCheck != "version") {
//        std::cerr << "No version declaration found." << std::endl;
//    } else {
//        std::string versionNum = line;
//        versionNum.erase(0, 8);
//        if (versionNum == "1") {
//            while (getline(infile, line)) {
//                std::cout << "Got new line: \"" << line << "\"" << std::endl;
//                auto lineSplit = split(line, ' ', '"');
//                std::string lineType = lineSplit[0];
//                if (lineType == "name") {
//                    std::cout << "Setting word list name." << std::endl;
//                    name = lineSplit[1];
//                } else if (lineType == "N") {
//                    std::cout << "Inputting new noun." << std::endl;
//                    nouns.emplace_back(lineSplit[1], lineSplit[2], stringToGender[lineSplit[3]], split(lineSplit[5], ';', '\''), stringToDeclension[lineSplit[4]]);
//                } else {
//                    std::cerr << "Unrecognised input type \"" << lineType << "\"" << std::endl;
//                }
//            }
//        } else {
//            std::cerr << versionNum << " is not a valid version." << std::endl;
//        }
//    }
}

WordList WordList::fromData(const std::string &data) {
    return WordList(std::stringstream(data));
}

WordList::WordList(std::stringstream infile) {
    std::string line;
    getline(infile, line);
    std::string versionCheck = line;
    versionCheck.resize(7);
    if (versionCheck != "version") {
        std::cerr << "No version declaration found." << std::endl;
    } else {
        std::string versionNum = line;
        versionNum.erase(0, 8);
        if (versionNum == "1") {
            while (getline(infile, line)) {
                std::cout << "Got new line: \"" << line << "\"" << std::endl;
                auto lineSplit = split(line, ' ', '"');
                std::string lineType = lineSplit[0];
                if (lineType == "name") {
                    std::cout << "Setting word list name." << std::endl;
                    name = lineSplit[1];
                } else if (lineType == "N") {
                    std::cout << "Inputting new noun." << std::endl;
                    nouns.emplace_back(lineSplit[1], lineSplit[2], stringToGender[lineSplit[3]], split(lineSplit[5], ';', '\''), stringToDeclension[lineSplit[4]]);
                } else {
                    std::cerr << "Unrecognised input type \"" << lineType << "\"" << std::endl;
                }
            }
        } else {
            std::cerr << versionNum << " is not a valid version." << std::endl;
        }
    }
}

WordList::WordList() = default;
