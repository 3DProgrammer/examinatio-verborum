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

NounChoice::NounChoice() {
    noun=nullptr;
}

NounChoice::NounChoice(bibliotheca::Noun *_noun, bibliotheca::Case _nounCase, bibliotheca::Number _nounNumber) {
    noun=_noun;
    nounCase=_nounCase;
    nounNumber=_nounNumber;
}
