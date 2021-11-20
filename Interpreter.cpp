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
    std::cout << "Query Evaluation" << std::endl;
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
        else {
            std::cout << " No";
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

void Interpreter::evaluateRules() {
    std::cout << "Rule Evaluation" << std::endl;
    int tuplesAdded = 0;
    int loop = 0;
    do {
        std::vector<Relation *> rulesToEval;
        int rulesSize = myDatalog.rules.size();
        for (int i = 0; i < rulesSize; i++) {
            int predicateSize = myDatalog.rules[i]->bodyPredicates.size();
            for (int j = 0; j < predicateSize; ++j) {
                Predicate *p = myDatalog.rules[i]->bodyPredicates[j];
                Relation *newRelation = evaluatePredicate(p);
                rulesToEval.push_back(newRelation);
                //newRelation->toString(); //not sure about this.
            }
            Relation *ruleRelation = nullptr;
            int rulesRelations = rulesToEval.size();
            if (rulesRelations > 1) {
                for (int j = 0; j < rulesRelations - 1; ++j) {
                    ruleRelation = rulesToEval[j]->Join2(rulesToEval[j + 1], rulesToEval[j]->name);


                }
            }
            if (rulesRelations == 1) {
                ruleRelation = rulesToEval[0];
            }

            myDatalog.rules[i]->toString();
            std::cout << std::endl;

            //TODO :: project tuples that appear in the head predicate
            std::vector<int> headIndeces = convertToIndeces(myDatalog.rules[i]->headPredicate->parameterList,
                                                            ruleRelation);
            ruleRelation = ruleRelation->project(headIndeces);

            //ruleRelation->name = rulesToEval[i]->name;
            ruleRelation->name = myDatalog.rules[i]->headPredicate->id;
            //TODO :: rename the relation to make it union compatible
            tuplesAdded = unionize(ruleRelation);
            //TODO :: union with the relation in the database
            //myDatalog.rules[i]->toString();
            //std::cout << std::endl;
            //ruleRelation->ruleToString();
        }
        loop ++;
    } while (tuplesAdded > 0);
    std::cout << std::endl;
    std::cout << "Schemes populated after ";
    std::cout << loop;
    std::cout << " passes through the Rules." << std::endl;
    std::cout << std::endl;
}

int Interpreter::unionize(Relation* newRelation) {
    int tuplesAdded = 0;
    Relation* ogRelation = database.mapOfRelations[newRelation->name];
    for (Tuple t : newRelation->tuples) {
        if (ogRelation->tuples.insert(t).second) {
            tuplesAdded++;
            //newRelation->ruleToString();
            int whileNum = 0;
            int headerSize = newRelation->header->attributes.size();
            while (whileNum < headerSize) {
                std::cout << "  " << newRelation->header->attributes[whileNum] << "=" << t.values[whileNum];
                if (whileNum < (headerSize - 1)) {
                    std::cout << ", ";
                }
                if (whileNum == headerSize - 1) {
                    std::cout << std::endl;
                }


                whileNum++;
            }
        }
    }
    return tuplesAdded;
}


std::vector<int> Interpreter::convertToIndeces(std::vector<Parameter *> vector, Relation* ruleRelation) {
    std::vector<int> headIndeces;
    int vecSize = vector.size();
    int relSize = ruleRelation->header->returnSize();
    /*for (int j = 0; j < relSize; ++j) {
        for (int i = 0; i < vecSize; ++i) {
            if (ruleRelation->header->attributes[j] == vector[i]->p) {
                headIndeces.push_back(j);
            }
        }
    }*/
    for (int i = 0; i < vecSize; ++i) {
        for (int j = 0; j < relSize; ++j) {
            if (ruleRelation->header->attributes[j] == vector[i]->p) {
                headIndeces.push_back(j);
            }
        }
    }
    return headIndeces;
}
