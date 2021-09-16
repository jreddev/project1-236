#include "StringAutomaton.h"

void StringAutomaton::S0(const std::string& input) {
    if (input[index] == '\'') {
        inputRead++;
        index++;
        S1(input);
    }
    else {
        Serr();
    }
}

void StringAutomaton::S1(const std::string& input) {
    int inputLength = input.size();
    if (input[index] == '\'') {
        index++;
        inputRead++;
        S2(input);
    }
    else if (input[index]==EOF){
        SFail(input);
    }
    else if (index == inputLength){
        SFail(input);
    }
    else {
        if(input[index] == '\n'){
            newLines++;

        }
        inputRead++;
        index++;
        S1(input);
    }
}
void StringAutomaton::S2(const std::string& input) {
    int inputLength = input.size();
    if (input[index] == '\'') {
        index++;
        inputRead++;
        S1(input);
    }
    else if (index == inputLength){
        SFail(input);
    }
    else {
       /* if(input[index] == '\n'){
            newLines++;

        }*/
    }
}
void StringAutomaton::SFail(const std::string& input){
    type = TokenType::UNDEFINED;
}