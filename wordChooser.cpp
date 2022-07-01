//
// Created by miles on 13/06/22.
//

#include "wordChooser.h"
#include "util.h"
#include <QSettings>
#include <map>

NounChoice chooseNoun(std::vector<bibliotheca::Noun> *nouns) {
    if (nouns->empty()) {
        return {};
    }
    bibliotheca::Case aCase;
    int w_n = quickSetting(n_w_nom, int, 1);
    int w_ac = quickSetting(n_w_acc, int, 1);
    int w_g = quickSetting(n_w_gen, int, 1);
    int w_d = quickSetting(n_w_dat, int, 1);
    int w_ab = quickSetting(n_w_abl, int, 1);
    int w_v = quickSetting(n_w_voc, int, 1);
    if (w_n + w_ac + w_g + w_d + w_ab + w_v == 0) {
        aCase = bibliotheca::Case::nom;
    }
    else if (rand() % (w_n + w_ac + w_g + w_d + w_ab + w_v) < w_n) {
        aCase = bibliotheca::Case::nom;
    }
    else if (rand() % (w_ac + w_g + w_d + w_ab + w_v) < w_ac) {
        aCase = bibliotheca::Case::acc;
    }
    else if (rand() % (w_g + w_d + w_ab + w_v) < w_g) {
        aCase = bibliotheca::Case::gen;
    }
    else if (rand() % (w_d + w_ab + w_v) < w_d) {
        aCase = bibliotheca::Case::dat;
    }
    else if (rand() % (w_ab + w_v) < w_ab) {
        aCase = bibliotheca::Case::abl;
    }
    else {
        aCase = bibliotheca::Case::voc;
    }
    bibliotheca::Number aNumber = (rand() % (quickSetting(n_w_sing, int, 1) + quickSetting(n_w_plur, int, 1))) >= quickSetting(n_w_plur, int, 1) ? bibliotheca::Number::singular : bibliotheca::Number::plural;
    return {&(*nouns)[rand() % nouns->size()], aCase, aNumber};
}
VerbChoice chooseVerb(std::vector<bibliotheca::Verb> *verbs) {
    if (verbs->empty()) {
        return {};
    }
    VerbOption chosen;
    {
        int w_a = quickSetting(v_w_ac, int, 1);
        int w_p = quickSetting(v_w_pa, int, 1);
        chosen.voice = (w_a + w_p == 0) ? bibliotheca::Voice::active : ((rand() % (w_a + w_p)) < w_a ? bibliotheca::Voice::active : bibliotheca::Voice::passive);
    }
    {
        int w_ind = quickSetting(v_w_ind, int, 1);
        int w_sub = quickSetting(v_w_sub, int, 1);
        int w_inf = quickSetting(v_w_inf, int, 1);
        int w_imp = quickSetting(v_w_imperative, int, 1);
        if (w_imp + w_ind + w_inf + w_sub == 0) {
            chosen.mood = bibliotheca::Mood::indicative;
        }
        else {
            if ((rand() % (w_ind + w_inf + w_sub + w_imp)) < w_ind) {
                chosen.mood = bibliotheca::Mood::indicative;
            }
            else if ((rand() % (w_inf + w_sub + w_imp)) < w_inf) {
                chosen.mood = bibliotheca::Mood::infinitive;
            }
            else if ((rand() % (w_sub + w_imp)) < w_sub) {
                chosen.mood = bibliotheca::Mood::subjunctive;
            }
            else {
                chosen.mood = bibliotheca::Mood::imperative;
            }
        }
    }
    {
        if (chosen.mood != bibliotheca::Mood::infinitive) {//Technically not required, but speeds up slightly.
            int w_s = quickSetting(v_w_s, int, 1);
            int w_p = quickSetting(v_w_p, int, 1);
            chosen.number = (w_s + w_p == 0) ? bibliotheca::Number::singular : ((rand() % (w_s + w_p)) < w_s ? bibliotheca::Number::singular : bibliotheca::Number::plural);
        }
    }
    {
        if (chosen.mood != bibliotheca::Mood::infinitive && chosen.mood != bibliotheca::Mood::imperative) {
            int w_1 = quickSetting(v_w_1, int, 1);
            int w_2 = quickSetting(v_w_2, int, 1);
            int w_3 = quickSetting(v_w_3, int, 1);
            if (w_1 + w_2 + w_3 == 0) {
                chosen.person = 1;
            }
            else {
                if ((rand() % (w_1 + w_2 + w_3)) < w_1) {
                    chosen.person = 1;
                }
                else if ((rand() % (w_2 + w_3)) < w_2) {
                    chosen.person = 2;
                }
                else {
                    chosen.person = 3;
                }
            }
        }
    }
    {
        if (chosen.mood == bibliotheca::Mood::infinitive) {
            int w_pr = quickSetting(v_w_pre, int, 1);
            int w_pe = quickSetting(v_w_per, int, 1);
            int w_f = quickSetting(v_w_fut, int, 1);
            if (w_pr + w_pe + w_f == 0) {
                chosen.tense = bibliotheca::Tense::present;
            }
            else {
                if ((rand() % (w_pr + w_pe + w_f)) < w_pr) {
                    chosen.tense = bibliotheca::Tense::present;
                }
                else if ((rand() % (w_pe + w_f)) < w_pe) {
                    chosen.tense = bibliotheca::Tense::perfect;
                }
                else {
                    chosen.tense = bibliotheca::Tense::future;
                }
            }
        }
        if (chosen.mood == bibliotheca::Mood::subjunctive) {
            int w_pr = quickSetting(v_w_pre, int, 1);
            int w_pe = quickSetting(v_w_per, int, 1);
            int w_im = quickSetting(v_w_imperfect, int, 1);
            int w_pl = quickSetting(v_w_plu, int, 1);
            if (w_pr + w_pe + w_im + w_pl == 0) {
                chosen.tense = bibliotheca::Tense::present;
            }
            else {
                if ((rand() % (w_pr + w_pe + w_im + w_pl)) < w_pr) {
                    chosen.tense = bibliotheca::Tense::present;
                }
                else if ((rand() % (w_pe + w_im + w_pl)) < w_pe) {
                    chosen.tense = bibliotheca::Tense::perfect;
                }
                else if ((rand() % (w_im + w_pl)) < w_im) {
                    chosen.tense = bibliotheca::Tense::imperfect;
                }
                else {
                    chosen.tense = bibliotheca::Tense::pluperfect;
                }
            }
        }
        if (chosen.mood == bibliotheca::Mood::indicative) {
            int w_pr = quickSetting(v_w_pre, int, 1);
            int w_pe = quickSetting(v_w_per, int, 1);
            int w_im = quickSetting(v_w_imperfect, int, 1);
            int w_pl = quickSetting(v_w_plu, int, 1);
            int w_f = quickSetting(v_w_fut, int, 1);
            int w_fp = quickSetting(v_w_futper, int, 1);
            if (w_pr + w_pe + w_im + w_pl + w_f + w_fp == 0) {
                chosen.tense = bibliotheca::Tense::present;
            }
            else {
                if ((rand() % (w_pr + w_pe + w_im + w_pl + w_f + w_fp)) < w_pr) {
                    chosen.tense = bibliotheca::Tense::present;
                }
                else if ((rand() % (w_pe + w_im + w_pl + w_f + w_fp)) < w_pe) {
                    chosen.tense = bibliotheca::Tense::perfect;
                }
                else if ((rand() % (w_im + w_pl + w_f + w_fp)) < w_im) {
                    chosen.tense = bibliotheca::Tense::imperfect;
                }
                else if ((rand() % (w_pl + w_f + w_fp)) < w_pl) {
                    chosen.tense = bibliotheca::Tense::pluperfect;
                }
                else if ((rand() % (w_f + w_fp)) < w_f) {
                    chosen.tense = bibliotheca::Tense::future;
                }
                else {
                    chosen.tense = bibliotheca::Tense::futureperfect;
                }
            }
        }
    }
    return {&((*verbs)[rand() % verbs->size()]), chosen};
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
    person = 1;
    tense = bibliotheca::Tense::present;
    voice = bibliotheca::Voice::active;
    number = bibliotheca::Number::singular;
    mood = bibliotheca::Mood::indicative;
}
VerbOption::VerbOption(int _person, bibliotheca::Number _number, bibliotheca::Tense _tense, bibliotheca::Voice _voice, bibliotheca::Mood _mood) {
    person = _person;
    number = _number;
    tense = _tense;
    voice = _voice;
    mood = _mood;
}
