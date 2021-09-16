#include "BlockCommentAutomaton.h"
void BlockCommentAutomaton::S0(const std::string& input) {

    if (input[index] == '#') {
        inputRead++;
        index++;
        S1(input);
    }
    else if (input[index] == EOF){
        SFail(input);
    }
    else {
        Serr();
    }
}

void BlockCommentAutomaton::S1(const std::string& input) {
    int inputLength = input.size();
    if (input[index] == '|') {
        inputRead++;
        index++;
        S2(input);
    }
    else if (input[index] == EOF){
        SFail(input);
    }
    else if (index == inputLength){
        SFail(input);
    }
    else {
        Serr();
    }
}
void BlockCommentAutomaton::S2(const std::string& input) {
    int inputLength = input.size();
    if (input[index] == '|') {
        inputRead++;
        index++;
        S3(input);
    }
    else if (input[index] == EOF){
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
        S2(input);
    }
}
void BlockCommentAutomaton::S3(const std::string& input) {
    int inputLength = input.size();
    if (input[index] == '#') {
        inputRead++;
    }
    else if (input[index] == '|') {
        inputRead++;
        index++;
        S3(input);
    }
    else if (input[index] == EOF){
        SFail(input);
    }
    else if (index == inputLength){
        SFail(input);
    }
    else {
        inputRead++;
        index++;
        S2(input);
    }
}
void BlockCommentAutomaton::SFail(const std::string& input){
    type = TokenType::UNDEFINED;
}

