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
    if (input[index]=='|') {
        S2(input);
    }
    if (input[index] != '\n') {
        inputRead++;
        index++;
        S1(input);
    }
    else {

    }
}
void LineCommentAutomaton::S2(const std::string& input) {
    if (input[index]=='|') {
        S3(input);
    }
    if (input[index] != '\n') {
        inputRead++;
        index++;
        S1(input);
    }
    else {

    }
}
void LineCommentAutomaton::S3(const std::string& input) {
    if (input[index]=='#') {
        Serr();
    }
}

void LineCommentAutomaton::SFail(const std::string& input) {
    type = TokenType::UNDEFINED;
}
