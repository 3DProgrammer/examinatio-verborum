//
// Created by miles on 16/6/22.
//

#include "wordlistParser.h"
#include <iostream>
#include <fstream>
std::vector<std::string> split(const std::string& line, char splitter, char quotes) {
    std::vector<std::string> result;
    if (line.empty()) {
        return result;
    }
    int last_index=0;
    bool quoting=false;
    for (int i = 0; i < line.size(); ++i) {
        if (line[i]==quotes) {
            if (quoting) {
                quoting=false;
                if(i>last_index) {
                    result.push_back(line.substr(last_index, i-last_index));
                }
                last_index=i+1;
            }
            else {
                quoting=true;
                if (i>last_index) {
                    result.push_back(line.substr(last_index, i-last_index));
                }
                last_index=i+1;
            }
        }
        if (line[i]==splitter&&!quoting) {
            if (i>last_index) {
                result.push_back(line.substr(last_index, i-last_index));
            }
            last_index=i+1;
        }
    }
    if (line.size()>last_index) {
        result.push_back(line.substr(last_index, line.size()-last_index));
    }
    return result;
}
WordList::WordList(const std::string &fileName) {
    std::ifstream infile(fileName);
    std::string line;
    getline(infile, line);
    std::string versionCheck=line;
    versionCheck.resize(7);
    if (versionCheck!="version") {
        std::cerr<<"No version declaration found."<<std::endl;
    }
    else {
        std::string versionNum=line;
        versionNum.erase(0,8);
        if (versionNum=="1") {
            while (getline(infile,line)) {
                std::cout<<"Got new line: \""<<line<<"\""<<std::endl;
                std::string lineType=line;
                auto lineSplit= split(line, ' ', '"');
                for (int i = 0; i < lineType.size(); ++i) {
                    if (lineType[i]==' ') {
                        lineType.erase(i, lineType.size());
                        break;
                    }
                }
                if (lineType=="name") {
                    std::cout<<"Setting word list name."<<std::endl;
                }
                else if (lineType=="N") {
                    std::cout<<"Inputting new noun."<<std::endl;
                }
                else {
                    std::cerr<<"Unrecognised input type \""<<lineType<<"\""<<std::endl;
                }
            }
        }
        else {
            std::cerr<<versionNum<<" is not a valid version."<<std::endl;
        }
    }
}

WordList::WordList() = default;
