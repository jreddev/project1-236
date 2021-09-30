//
// Created by jared on 9/27/2021.
//

#include "Parser.h"
#include <set>
Parser::Parser(std::vector<Token*> inputTokens) {
    myTokens = inputTokens;
    std::vector<Token*> matchTokens;

}

Parser::~Parser() {
}



void Parser::Run() {
    try {
        datalogProgram();

    } catch (Token* error) {
        std::cout << "Failure!\n\t";
        error->toString();
    }
    if (myTokens.empty()) {
        std::cout << "Success!\n";
        toString();
        /*std::set<std::string> domain;
        int domainSize = domain.size();
        std::cout << "Domain(" << domainSize << "):\n";
        for (int i = 0; i < domainSize; i++) {
            std::cout << "  ";
            domain[i]->toString();
            std::cout << "\n";
        }*/
    }
    else {
        //std::cout << "Houston, we have a problem...";
    }

}

void Parser::datalogProgram() {
    commentCheck();
    terminalCheck(TokenType::SCHEMES);
    terminalCheck(TokenType::COLON);
    scheme();
    schemeList();
    terminalCheck(TokenType::FACTS);
    terminalCheck(TokenType::COLON);
    factList();
    terminalCheck(TokenType::RULES);
    terminalCheck(TokenType::COLON);
    ruleList();
    terminalCheck(TokenType::QUERIES);
    terminalCheck(TokenType::COLON);
    query();
    queryList();
    terminalCheck(TokenType::END);
}

void Parser::toString() {
    myDatalog->toString();
}

void Parser::scheme() {
        Predicate* tempPred = new Predicate();
    commentCheck();
        tempPred->id = myTokens[0]->value;
    terminalCheck(TokenType::ID);
    terminalCheck(TokenType::LEFT_PAREN);
        Parameter* tempParam = new Parameter();
        tempParam->p = myTokens[0]->value;
        tempPred->parameterList.push_back(tempParam);
    terminalCheck(TokenType::ID);
    idList(tempPred);
        myDatalog->schemes.push_back(tempPred);

    terminalCheck(TokenType::RIGHT_PAREN);

}
void Parser::schemeList() {
    commentCheck();
    TokenType matchType = myTokens[0]->returnType();
    if (matchType == TokenType::ID) {
        scheme();
        schemeList();
    }
    //else do nothing (move on) lambda
}

void Parser::fact(){
    Predicate* tempPred = new Predicate();
    commentCheck();
    tempPred->id = myTokens[0]->value;
    terminalCheck(TokenType::ID);
    terminalCheck(TokenType::LEFT_PAREN);
        Parameter* tempParam = new Parameter();
        tempParam->p = myTokens[0]->value;
        tempPred->parameterList.push_back(tempParam);
    terminalCheck(TokenType::STRING);
    stringList(tempPred);
    terminalCheck(TokenType::RIGHT_PAREN);
    terminalCheck(TokenType::PERIOD);
    myDatalog->facts.push_back(tempPred);
}

void Parser::factList(){
    commentCheck();
    //if in follow set
    TokenType matchType = myTokens[0]->returnType();
    if (matchType == TokenType::ID) {
        fact();
        factList();
    }
    //else do nothing
}

void Parser::rule(){
    Rule* tempRule = new Rule;
    commentCheck();
    headPredicate(tempRule);
    terminalCheck(TokenType::COLON_DASH);
    rulePredicate(tempRule);
    rulePredicateList(tempRule);
    terminalCheck(TokenType::PERIOD);
    myDatalog->rules.push_back(tempRule);
}

void Parser::ruleList(){
    commentCheck();
    //if in follow set
    TokenType matchType = myTokens[0]->returnType();
    if(matchType == TokenType::ID) {
        rule();
        ruleList();
    }
    //else
}

void Parser::query(){
    commentCheck();
    predicate();
    terminalCheck(TokenType::Q_MARK);

}

void Parser::queryList() {
    commentCheck();
    //if in follow set
    TokenType matchType = myTokens[0]->returnType();
    if (matchType == TokenType::ID) {
        query();
        queryList();
    }

    //else do nothing
}

void Parser::idList(Predicate* tempPred){
    commentCheck();
    //if in follow set
    TokenType matchType = myTokens[0]->returnType();
    if (matchType == TokenType::COMMA){
        terminalCheck(TokenType::COMMA);
            Parameter* tempParam = new Parameter();
            tempParam->p = myTokens[0]->value;
            tempPred->parameterList.push_back(tempParam);
        terminalCheck(TokenType::ID);
        idList(tempPred);
    } //FIXME maybe one more time (not sure)

    //else do nothing
}

void Parser::stringList(Predicate *tempPred) {
    commentCheck();
    //if in follow set
    TokenType matchType = myTokens[0]->returnType();
    if(matchType == TokenType::COMMA){
        terminalCheck(TokenType::COMMA);
            Parameter* tempParam = new Parameter();
            tempParam->p = myTokens[0]->value;
            tempPred->parameterList.push_back(tempParam);
        terminalCheck(TokenType::STRING);
        stringList(tempPred);
    }//FIXME maybe one more time (not sure)

    //else do nothing
}

void Parser::headPredicate(Rule *tempRule) {
    commentCheck();
        //Predicate* tempPred = new Predicate;
        tempRule->headPredicate = new Predicate;
        tempRule->headPredicate->id = myTokens[0]->value;
    terminalCheck(TokenType::ID);
    terminalCheck(TokenType::LEFT_PAREN);
        Parameter* tempParam = new Parameter();
        tempParam->p = myTokens[0]->value;
        tempRule->headPredicate->parameterList.push_back(tempParam);
    terminalCheck(TokenType::ID);
    ruleIdList(tempRule);
    terminalCheck(TokenType::RIGHT_PAREN);
}

void Parser::predicate(){
        Predicate* tempPred = new Predicate();
    commentCheck();
        tempPred->id = myTokens[0]->value;
    terminalCheck(TokenType::ID);
    terminalCheck(TokenType::LEFT_PAREN);
    parameter(tempPred);
    parameterList(tempPred);
    terminalCheck(TokenType::RIGHT_PAREN);
    myDatalog->queries.push_back(tempPred);
}

void Parser::predicateList(){
    commentCheck();
    //if in follow set
    TokenType matchType = myTokens[0]->returnType();
    if (matchType == TokenType::COMMA) {
        terminalCheck(TokenType::COMMA);
        predicate();
        predicateList();
    }
    //else do nothing
}

void Parser::rulePredicate(Rule* tempRule){
    Predicate* tempPred = new Predicate();
    commentCheck();
    tempPred->id = myTokens[0]->value;
    terminalCheck(TokenType::ID);
    terminalCheck(TokenType::LEFT_PAREN);
    parameter(tempPred);
    parameterList(tempPred);
    terminalCheck(TokenType::RIGHT_PAREN);
    tempRule->bodyPredicates.push_back(tempPred);
}

void Parser::rulePredicateList(Rule* tempRule){
    commentCheck();
    //if in follow set
    TokenType matchType = myTokens[0]->returnType();
    if (matchType == TokenType::COMMA) {
        terminalCheck(TokenType::COMMA);
        rulePredicate(tempRule);
        rulePredicateList(tempRule);
    }
    //else do nothing
}

void Parser::parameter(Predicate* tempPred){
    commentCheck();
    //if something...?
    TokenType matchType = myTokens[0]->returnType();
    if (matchType == TokenType::STRING) {
            Parameter* tempParam = new Parameter();
            tempParam->p = myTokens[0]->value;
            tempPred->parameterList.push_back(tempParam);
        terminalCheck(TokenType::STRING);
    }
    else if (matchType == TokenType::ID){
            Parameter* tempParam = new Parameter();
            tempParam->p = myTokens[0]->value;
            tempPred->parameterList.push_back(tempParam);
        terminalCheck(TokenType::ID);
    }
    else {
        throw myTokens.begin();
    }
}

void Parser::parameterList(Predicate* tempPred){
    commentCheck();
    //if in follow set
    TokenType matchType = myTokens[0]->returnType();
    if (matchType == TokenType::COMMA){
        terminalCheck(TokenType::COMMA);
        parameter(tempPred);
        parameterList(tempPred);
    }
    //else do nothing
}

void Parser::terminalCheck(TokenType type) {
    commentCheck();
    TokenType matchType = myTokens[0]->returnType();
    if (matchType != type) {
        Token* throwToken = myTokens[0];
        throw throwToken;
        //throw std::invalid_argument("Wrong TokenType found");
    }
    else {
        myTokens.erase(myTokens.begin());
    }
}

void Parser::commentCheck(){
    TokenType matchType = myTokens[0]->returnType();
    if (matchType == TokenType::BLOCKCOMMENT || matchType == TokenType::LINECOMMENT) {
        while (matchType == TokenType::BLOCKCOMMENT || matchType == TokenType::LINECOMMENT) {
            myTokens.erase(myTokens.begin());
            matchType = myTokens[0]->returnType();
        }
    }
}

void Parser::ruleIdList(Rule *tempRule) {
    commentCheck();
    //if in follow set
    TokenType matchType = myTokens[0]->returnType();
    if (matchType == TokenType::COMMA){
        terminalCheck(TokenType::COMMA);
            Parameter* tempParam = new Parameter();
            tempParam->p = myTokens[0]->value;
            tempRule->headPredicate->parameterList.push_back(tempParam);
        terminalCheck(TokenType::ID);
        ruleIdList(tempRule);
    } //FIXME maybe one more time (not sure)
}


