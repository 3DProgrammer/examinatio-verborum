//
// Created by miles on 13/06/22.
//

#ifndef EXAMINATIO_VERBORUM_WORDCHOOSER_H
#define EXAMINATIO_VERBORUM_WORDCHOOSER_H
#include <bibliotheca.h>
#include <map>
enum class WordChoice {
    None, Noun, Verb, Adjective, Pronoun, Other
};
struct NounChoice {
    bibliotheca::Noun *noun;
    bibliotheca::Case nounCase;
    bibliotheca::Number nounNumber;
    NounChoice();
    NounChoice(bibliotheca::Noun *_noun, bibliotheca::Case _nounCase, bibliotheca::Number _nounNumber);
};
struct VerbOption {
    int person;
    bibliotheca::Number number;
    bibliotheca::Tense tense;
    bibliotheca::Voice voice;
    bibliotheca::Mood mood;
    VerbOption(int _person, bibliotheca::Number _number, bibliotheca::Tense _tense, bibliotheca::Voice _voice, bibliotheca::Mood _mood);
    VerbOption();
};
struct VerbChoice {
    bibliotheca::Verb *verb;
    VerbOption option;
    VerbChoice();
    VerbChoice(bibliotheca::Verb *_verb, VerbOption _option);
};
NounChoice chooseNoun(std::vector<bibliotheca::Noun> *nouns);
VerbChoice chooseVerb(std::vector<bibliotheca::Verb> *verbs, std::vector<std::pair<VerbOption,int>> optionWeights);
#endif //EXAMINATIO_VERBORUM_WORDCHOOSER_H
