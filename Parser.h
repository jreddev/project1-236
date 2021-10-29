#ifndef PARSER_H
#define PARSER_H
#include "Token.h"
#include "DatalogProgram.h"
#include <vector>

class Parser
{
private:
    std::vector<Token*> myTokens;

public:
    //DatalogProgram* myDatalog = new DatalogProgram;
    Parser(std::vector<Token*> inputTokens, DatalogProgram inputDatalog);
    ~Parser();
    DatalogProgram myDatalog;
    void datalogProgram();
    void toString();
    void scheme();
    void schemeList();
    void fact();
    void factList();
    void rule();
    void ruleList();
    void query();
    void queryList();
    void idList(Predicate* tempPred);
    void stringList(Predicate *tempPred);
    void headPredicate(Rule *tempRule);
    void predicate();
    void predicateList();
    void parameter(Predicate* tempPred);
    void parameterList(Predicate* tempPred);
    void terminalCheck(TokenType type);


    void Run();

    void commentCheck();

    void createParameter();

    void ruleIdList(Rule *tempRule);

    void rulePredicate(Rule *tempRule);

    void rulePredicateList(Rule *tempRule);
};

#endif // PARSER_H
