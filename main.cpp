#include "Lexer.h"


int main(int argc, char** argv) {

    Lexer* lexer = new Lexer();

    // TODO

    //MY ADDED CODE//
    std::string fileName = argv[1];
    std::string inputString;
    std::ifstream inFile(fileName);

    char currentInput = inFile.peek();

    while (currentInput != EOF) {
        char addMeToString;
        inFile.get(addMeToString);
        inputString.push_back(addMeToString);
        currentInput = inFile.peek();
    }

    inFile.close();

    lexer->Run(inputString);
    //END MY ADDED CODE//


    delete lexer;

    return 0;
}