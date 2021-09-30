//
// Created by jared on 9/28/2021.
//

#ifndef PROJECT1_PREDICATE_H
#define PROJECT1_PREDICATE_H
#include "Parameter.h"
#include <string>
#include <vector>
#include "fstream"
#include "iostream"

class Predicate {
private:

public:
    std::string id;
    std::vector <Parameter*> parameterList;
    void toString();
};


#endif //PROJECT1_PREDICATE_H
