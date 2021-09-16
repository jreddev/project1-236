//
// Created by jared on 9/15/2021.
//

#include "IdAutomaton.h"
void IdAutomaton::S0(const std::string& input) {
    if (isalpha(input[index])) {
        inputRead++;
        index++;
        S1(input);
    }
    else {
        Serr();
    }
}
void IdAutomaton::S1(const std::string& input) {
    if (isalpha(input[index]) || isdigit(input[index])) {
        inputRead++;
        index++;
        S1(input);
    }
    else {

    }
}