//
// Created by miles on 16/6/22.
//

#ifndef EXAMINATIO_VERBORUM_WORDLISTPARSER_H
#define EXAMINATIO_VERBORUM_WORDLISTPARSER_H
#include <vector>
#include <bibliotheca.h>
class WordList {
public:
    std::vector<bibliotheca::Noun> nouns;
    explicit WordList(const std::string& fileName);
    WordList();
};
#endif //EXAMINATIO_VERBORUM_WORDLISTPARSER_H
