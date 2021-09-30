//
// Created by jared on 9/28/2021.
//

#ifndef PROJECT1_DATALOGPROGRAM_H
#define PROJECT1_DATALOGPROGRAM_H
#include <string>
#include <vector>
#include "fstream"
#include "iostream"
#include "Rule.h"

class DatalogProgram {
private:

public:
    void toString();
    std::vector<Predicate*> schemes;
    std::vector<Predicate*> facts;
    std::vector<Predicate*> queries;
    std::vector<Rule*> rules;
};


#endif //PROJECT1_DATALOGPROGRAM_H
