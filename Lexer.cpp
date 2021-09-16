#include "Lexer.h"
#include "ColonAutomaton.h"
#include "ColonDashAutomaton.h"
#include "AddAutomaton.h"
#include "BlockCommentAutomaton.h"
#include "CommaAutomaton.h"
#include "FactsAutomaton.h"
#include "Left_ParenAutomaton.h"
#include "LineCommentAutomaton.h"
#include "MultiplyAutomaton.h"
#include "PeriodAutomaton.h"
#include "Q_MarkAutomaton.h"
#include "QueriesAutomaton.h"
#include "Right_ParenAutomaton.h"
#include "RulesAutomaton.h"
#include "SchemesAutomaton.h"
#include "StringAutomaton.h"
#include "UndefinedAutomaton.h"
#include "EOFAutomaton.h"
#include "IdAutomaton.h"

Lexer::Lexer() {
    CreateAutomata();
}

Lexer::~Lexer() {
    // TODO: need to clean up the memory in `automata` and `tokens`
}

void Lexer::CreateAutomata() {
    automata.push_back(new UndefinedAutomaton());
    automata.push_back(new EOFAutomaton());
    automata.push_back(new ColonAutomaton());
    automata.push_back(new ColonDashAutomaton());
    // TODO: Add the other needed automata here
    automata.push_back(new AddAutomaton());
    automata.push_back(new BlockCommentAutomaton());
    automata.push_back(new CommaAutomaton());
    automata.push_back(new FactsAutomaton());
    automata.push_back(new Left_ParenAutomaton());
    automata.push_back(new LineCommentAutomaton());
    automata.push_back(new MultiplyAutomaton());
    automata.push_back(new PeriodAutomaton());
    automata.push_back(new Q_MarkAutomaton());
    automata.push_back(new QueriesAutomaton());
    automata.push_back(new Right_ParenAutomaton());
    automata.push_back(new RulesAutomaton());
    automata.push_back(new SchemesAutomaton());
    automata.push_back(new StringAutomaton());
    automata.push_back(new IdAutomaton());


    // TODO: still need to add ID and maybe some other(s).
}

void Lexer::Run(std::string& input) {

    // TODO: convert this pseudo-code with the algorithm into actual C++ code
    /*
    set lineNumber to 1
    // While there are more characters to tokenize
    loop while input.size() > 0 {
        set maxRead to 0
        set maxAutomaton to the first automaton in automata*/
//My ADDED CODE//
    int lineNumber = 1;
    Automaton* eofAutomata = automata[1];
    while (input.size() > 0){
        int maxRead = 0;
        Automaton* maxAutomaton = automata[0];
        Automaton* undefinedAutomaton = automata[0];

        int inputRead;
        if (isspace(input.at(0))){
            //std::cout << "This here is a whitespace dude...";
            if (input.at(0) == '\n'){
                lineNumber++;
            }
            int eraseValue = 1;
            input.erase(0,eraseValue);
        }
        else {
            int vectorSize = automata.size();
            for (int i = 0; i < vectorSize; i++){
                inputRead = automata[i]->Start(input);
                if (inputRead > maxRead) {
                    maxRead = inputRead;
                    maxAutomaton = automata[i];
                }
            }
            if (maxRead > 0) {
                if (maxAutomaton == automata[5]){
                    int addLines = automata[5]->NewLinesRead();
                    lineNumber = lineNumber + addLines;
                }
                if (maxAutomaton == automata[17]){
                    int addLines = automata[17]->NewLinesRead();
                    lineNumber = lineNumber + addLines;
                }
                std::string tokenString = input.substr(0,maxRead);
                Token* newToken = maxAutomaton->CreateToken(tokenString, lineNumber);
                tokens.push_back(newToken);
            }
            else {
                std::string tokenString = input.substr(0,1);//FIXME : for undefined I need to make it so it works for strings and comments that never end.
                Token* newToken = undefinedAutomaton->CreateToken(tokenString, lineNumber);
                tokens.push_back(newToken);
                maxRead = 1;
            }
            int eraseValue = maxRead;
            input.erase(0,eraseValue);
        }

    }
    //lineNumber++;//fixme
    Token* newToken = eofAutomata->CreateToken("", lineNumber);//FIXME : maybe need to change "EOF".. no se.
    tokens.push_back(newToken);

    int tokenVectorSize = tokens.size();
    for (int i = 0; i < tokenVectorSize; i++){
        tokens[i]->toString();
    }
    std::cout << "Total Tokens = ";
    std::cout << tokenVectorSize;
    std::cout << "\n";
//END MY ADDED CODE//
        // TODO: you need to handle whitespace inbetween tokens

        // Here is the "Parallel" part of the algorithm
        //   Each automaton runs with the same input
       /* foreach automaton in automata {
            inputRead = automaton.Start(input)
            if (inputRead > maxRead) {
                set maxRead to inputRead
                set maxAutomaton to automaton
            }
        }
        // Here is the "Max" part of the algorithm
        if maxRead > 0 {
            set newToken to maxAutomaton.CreateToken(...)
                increment lineNumber by maxAutomaton.NewLinesRead()
                add newToken to collection of all tokens
        }
        // No automaton accepted input
        // Create single character undefined token
        else {
            set maxRead to 1
                set newToken to a  new undefined Token
                (with first character of input)
                add newToken to collection of all tokens
        }
        // Update `input` by removing characters read to create Token
        remove maxRead characters from input
    }
    add end of file token to all tokens
    */
}
