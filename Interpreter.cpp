//
// Created by jared on 10/25/2021.
//

#include "Interpreter.h"

Interpreter::Interpreter(Database database, DatalogProgram inputDatalog) {
    this->database = database;
    this->myDatalog = inputDatalog;
    initializeSchemes();
    initializeFacts();

}

void Interpreter::initializeSchemes() {
    int schemeSize = myDatalog.schemes.size();
    for (int i = 0; i < schemeSize; i++) {
        Header* newHeader = new Header();
        int parameters = myDatalog.schemes[i]->parameterList.size();
        for (int k = 0; k < parameters; k++){
            std::string newAttribute = myDatalog.schemes[i]->parameterList[k]->p;
            newHeader->attributes.push_back(newAttribute);
        }
        std::string relationName = myDatalog.schemes[i]->id;
        Relation* newRelation = new Relation(relationName, newHeader);
        database.addToMap(relationName,newRelation);
    }
}

void Interpreter::initializeFacts() {
    int factsSize = myDatalog.facts.size();
    for (int i = 0; i < factsSize; i++) {
        Tuple newTuple = Tuple();
        int valuesSize = myDatalog.facts[i]->parameterList.size();
        for (int k = 0; k < valuesSize; k++){
            std::string newValue = myDatalog.facts[i]->parameterList[k]->p;
            newTuple.values.push_back(newValue);
        }
        std::string relationName = myDatalog.facts[i]->id;
        Relation* tempRelation = database.mapOfRelations.at(relationName);
        tempRelation->addTuple(newTuple);

    }
}

void Interpreter::evaluateQueries() {
    int queriesSize = myDatalog.queries.size();
    for(int i = 0; i < queriesSize; i++) {
        Predicate* p = myDatalog.queries[i];
        Relation* newRelation = evaluatePredicate(p);
        bool sayYes = false;
        int tupleSize = 0;
        if (!newRelation->tuples.empty()) {
            sayYes = true;
            tupleSize = newRelation->tuples.size();

        }
        myDatalog.queries[i]->toString();
        std::cout << "?";
        if (sayYes) {
            std::cout << " Yes(" << tupleSize << ")";
        }
        std::cout << std::endl;
        newRelation->toString();
    }

}

Relation* Interpreter::evaluatePredicate(Predicate* p) {
    std::vector<int> indexSeen;
    std::vector<std::string> variableSeen;
    std::map<std::string, int> mapSeen;
    int parameterListSize = p->parameterList.size();
    Relation* queryRelation = findRelation(p->id);
    //int j = 0;
    for (int i = 0; i < parameterListSize; ++i) {

        if(p->parameterList[i]->isConstant) {
            //type 1 select.
            std::string passVal = p->parameterList[i]->p;
            queryRelation = queryRelation->select(i,passVal);
            //return queryRelation;
        }
        else {
            if (indexSeen.empty()){
                //mark for later if it's first.
                std::string pushValue = p->parameterList[i]->p;
                indexSeen.push_back(i);
                variableSeen.push_back(pushValue);
                mapSeen.insert({pushValue,i});
            }
            else {
                std::string findValue = p->parameterList[i]->p;

                if (findInVector(variableSeen, findValue)) {
                    int indexFind = mapSeen.find(findValue)->second;
                    //type 2 select
                    queryRelation = queryRelation->select(indexFind,i);
                    //return queryRelation;
                }
                else {
                    //mark for later
                    std::string pushValue = p->parameterList[i]->p;
                    indexSeen.push_back(i);
                    variableSeen.push_back(pushValue);
                    mapSeen.insert({pushValue,i});
                }

            }
            //j++;
        }
    }
    queryRelation = queryRelation->project(indexSeen);
    queryRelation = queryRelation->rename(variableSeen);
    return queryRelation;
}

bool Interpreter::findInVector(std::vector<std::string> searchVector, std::string id) {
    int vectorSize = searchVector.size();
    for (int i = 0; i < vectorSize; ++i) {
        if (searchVector[i] == id) {
            return true;
        }
    }
    return false;
}

Relation* Interpreter::findRelation(std::string id){
    Relation* returnRelation = database.mapOfRelations[id];
    return returnRelation;
}