#include "Lexer.h"
#include "Parser.h"
#include "Interpreter.h"
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

    DatalogProgram myDatalog = DatalogProgram();
    Parser* parser = new Parser(tokens, myDatalog);
    parser->Run();


    Database database = Database();
    Interpreter* interpreter = new Interpreter(database, parser->myDatalog);
    interpreter->evaluateRules();
    interpreter->evaluateQueries();

    delete lexer;

    return 0;
}