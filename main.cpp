#include "Lexer.h"
#include "string"
#include "fstream"
#include "iostream"

int main(int argc, char** argv) {

    Lexer* lexer = new Lexer();

    // TODO

    //MY ADDED CODE//
    std::string fileName = argv[1];
    std::string inputFile;
    std::ifstream inFile(fileName);

    char currentInput = inFile.peek();

    while (currentInput != EOF) {
        char addMeToString;
        inFile.get(addMeToString);
        inputFile.push_back(addMeToString);
        currentInput = inFile.peek();
    }

    inFile.close();
    std::cout << inputFile;

    lexer->Run(inputFile);
    //END MY ADDED CODE//


    delete lexer;

    return 0;
}