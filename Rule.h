//
// Created by jared on 9/28/2021.
//

#ifndef PROJECT1_RULE_H
#define PROJECT1_RULE_H
#include "Predicate.h"

class Rule {
private:
public:
    Predicate* headPredicate;
    std::vector<Predicate*> bodyPredicates;
    void toString();
};


#endif //PROJECT1_RULE_H
