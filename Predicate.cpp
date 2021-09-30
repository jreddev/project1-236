//
// Created by jared on 9/28/2021.
//

#include "Predicate.h"

void Predicate::toString() {
    std::cout << id << "(";
    int size = parameterList.size();
    for(int i = 0; i < size; i++) {
         parameterList[i]->toString();
        if(i<(size-1)){
            std::cout << ",";
        }
    }
    std::cout << ")";
}
