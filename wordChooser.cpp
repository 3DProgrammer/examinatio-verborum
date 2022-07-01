//
// Created by miles on 13/06/22.
//

#include "wordChooser.h"
#include <map>
#include <QSettings>
#include "util.h"

NounChoice chooseNoun(std::vector<bibliotheca::Noun> *nouns) {
    if (nouns->empty()) {
        return {};
    }
    bibliotheca::Case aCase;
    int w_n= quickSetting(n_w_nom, int, 1);
    int w_ac= quickSetting(n_w_acc, int, 1);
    int w_g= quickSetting(n_w_gen, int, 1);
    int w_d= quickSetting(n_w_dat, int, 1);
    int w_ab= quickSetting(n_w_abl, int, 1);
    int w_v= quickSetting(n_w_voc, int, 1);
    if (w_n+w_ac+w_g+w_d+w_ab+w_v==0) {
        aCase=bibliotheca::Case::nom;
    }
    else if (rand()%(w_n+w_ac+w_g+w_d+w_ab+w_v)<w_n) {
        aCase = bibliotheca::Case::nom;
    }
    else if (rand()%(w_ac+w_g+w_d+w_ab+w_v)<w_ac) {
        aCase = bibliotheca::Case::acc;
    }
    else if (rand()%(w_g+w_d+w_ab+w_v)<w_g) {
        aCase = bibliotheca::Case::gen;
    }
    else if (rand()%(w_d+w_ab+w_v)<w_d) {
        aCase = bibliotheca::Case::dat;
    }
    else if (rand()%(w_ab+w_v)<w_ab) {
        aCase = bibliotheca::Case::abl;
    }
    else {
        aCase = bibliotheca::Case::voc;
    }
    bibliotheca::Number aNumber = (rand()%(quickSetting(n_w_sing, int, 1)+ quickSetting(n_w_plur, int, 1)))>= quickSetting(n_w_plur, int, 1)?bibliotheca::Number::singular:bibliotheca::Number::plural;
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
