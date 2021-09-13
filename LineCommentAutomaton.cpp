#include "LineCommentAutomaton.h"

void LineCommentAutomaton::S0(const std::string& input) {
    if (input[index] == '#') {
        inputRead++;
        index++;
        S1(input);
    }
    else {
        Serr();
    }
}

void LineCommentAutomaton::S1(const std::string& input) {
    if (input[index] != '\n') {
        inputRead++;
        index++;
        S1(input);
    }
    else {
        Serr();
    }
}
