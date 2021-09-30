//
// Created by jared on 9/28/2021.
//

#include "Rule.h"

void Rule::toString() {
    headPredicate->toString();
    std::cout << " :- ";
    int size = bodyPredicates.size();
    for (int i = 0; i < size; i++){
        bodyPredicates[0]->toString();
        if(i<(size-1)){
            std::cout << ",";
        }
        else {
            std::cout << ".";
        }
    }

}
