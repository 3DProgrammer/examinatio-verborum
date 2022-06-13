//
// Created by miles on 13/06/22.
//

#ifndef EXAMINATIO_VERBORUM_WORDCHOOSER_H
#define EXAMINATIO_VERBORUM_WORDCHOOSER_H
#include <bibliotheca.h>
#include <map>
struct NounChoice {
    bibliotheca::Noun *noun;
    bibliotheca::Case nounCase;
    bibliotheca::Number nounNumber;
    NounChoice();
    NounChoice(bibliotheca::Noun *_noun, bibliotheca::Case _nounCase, bibliotheca::Number _nounNumber);
};
NounChoice chooseNoun(std::vector<bibliotheca::Noun> *nouns, std::map<bibliotheca::Case, std::string> *cases, std::map<bibliotheca::Number, std::string> *numbers);

#endif //EXAMINATIO_VERBORUM_WORDCHOOSER_H
