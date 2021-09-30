#include "Lexer.h"
#include "Parser.h"
#include <vector>


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
    std::vector<Token*> tokens = lexer->tokens;
    //END MY ADDED CODE//

    Parser* parser = new Parser(tokens);
    parser->Run();

    delete lexer;

    return 0;
}