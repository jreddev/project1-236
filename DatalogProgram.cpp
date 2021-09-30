//
// Created by jared on 9/28/2021.
//

#include "DatalogProgram.h"
#include <set>

void DatalogProgram::toString() {
    std::set<std::string> domain;
    int schemesSize = schemes.size();
    int factsSize = facts.size();
    int rulesSize = rules.size();
    int queriesSize = queries.size();

    std::cout << "Schemes(" << schemesSize << "):\n";
    for (int i = 0; i < schemesSize; i++) {
        std::cout << "  ";
        schemes[i]->toString();
        std::cout << "\n";
    }
    std::cout << "Facts(" << factsSize << "):\n";
    for (int i = 0; i < factsSize; i++) {
        std::cout << "  ";
        facts[i]->toString();
        std::cout << ".\n";
    }
    std::cout << "Rules(" << rulesSize << "):\n";
    for (int i = 0; i < rulesSize; i++) {
        std::cout << "  ";
        rules[i]->toString();
        std::cout << "\n";
    }
    std::cout << "Queries(" << queriesSize << "):\n";
    for (int i = 0; i < queriesSize; i++) {
        std::cout << "  ";
        queries[i]->toString();
        std::cout << "?\n";
    }
    for(int i = 0; i < factsSize; i++) {
        int numFacts = facts[i]->parameterList.size();
        for (int j = 0; j < numFacts; j++) {
            domain.insert(facts[i]->parameterList[j]->p);
        }
    }
    int domainSize = domain.size();
    std::cout << "Domain(" << domainSize << "):\n";
    for (auto it=domain.begin(); it != domain.end(); ++it) {
        std::cout << "  " << *it << "\n";
    }


}
