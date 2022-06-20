//
// Created by miles on 13/06/22.
//

#include "wordChooser.h"
#include <map>

NounChoice chooseNoun(std::vector<bibliotheca::Noun> *nouns, std::map<bibliotheca::Case, std::string> *cases, std::map<bibliotheca::Number, std::string> *numbers) {
    if (nouns->empty()) {
        return {};
    }
    auto casesIterator = cases->begin();
    std::advance(casesIterator, rand() % cases->size());
    bibliotheca::Case aCase = casesIterator->first;
    auto numberIterator = numbers->begin();
    std::advance(numberIterator, rand() % numbers->size());
    bibliotheca::Number aNumber = numberIterator->first;
    return {&(*nouns)[rand() % nouns->size()], aCase, aNumber};
}
VerbChoice chooseVerb(std::vector<bibliotheca::Verb> *verbs, std::vector<std::pair<VerbOption, int>> optionWeights) {
    if (verbs->empty()) {
        return {};
    }
    int weightsSum = 0;
    for (auto option: optionWeights) {
        weightsSum += option.second;
    }
    VerbOption chosen = {};
    for (auto option: optionWeights) {
        if (rand() % weightsSum < option.second) {
            chosen = option.first;
            break;
        }
        weightsSum-=option.second;
    }
    return {&((*verbs)[rand()%verbs->size()]),chosen};
}

NounChoice::NounChoice() {
    noun = nullptr;
    nounCase = bibliotheca::Case::nom;
    nounNumber = bibliotheca::Number::singular;
}

NounChoice::NounChoice(bibliotheca::Noun *_noun, bibliotheca::Case _nounCase, bibliotheca::Number _nounNumber) {
    noun = _noun;
    nounCase = _nounCase;
    nounNumber = _nounNumber;
}
VerbChoice::VerbChoice() {
    verb = nullptr;
    option = {1, bibliotheca::Number::singular, bibliotheca::Tense::present, bibliotheca::Voice::active, bibliotheca::Mood::indicative};
}
VerbChoice::VerbChoice(bibliotheca::Verb *_verb, VerbOption _option) {
    verb = _verb;
    option = _option;
}
VerbOption::VerbOption() {
    person=1;
    tense=bibliotheca::Tense::present;
    voice=bibliotheca::Voice::active;
    number=bibliotheca::Number::singular;
    mood=bibliotheca::Mood::indicative;
}
VerbOption::VerbOption(int _person, bibliotheca::Number _number, bibliotheca::Tense _tense, bibliotheca::Voice _voice, bibliotheca::Mood _mood) {
    person=_person;
    number=_number;
    tense=_tense;
    voice=_voice;
    mood=_mood;
}
