//
// Created by miles on 16/6/22.
//

#ifndef EXAMINATIO_VERBORUM_WORDLISTPARSER_H
#define EXAMINATIO_VERBORUM_WORDLISTPARSER_H
#include <vector>
#include <bibliotheca.h>
#include <map>
class WordList {
public:
    std::vector<bibliotheca::Noun> nouns;
    std::string name;
    explicit WordList(std::stringstream instream);
    WordList();
    static std::map<std::string,bibliotheca::Gender> stringToGender;
    static std::map<std::string,int> stringToDeclension;
    static WordList fromData(const std::string &data);
    static WordList fromFilename(const std::string &fileName);

};
#endif //EXAMINATIO_VERBORUM_WORDLISTPARSER_H
