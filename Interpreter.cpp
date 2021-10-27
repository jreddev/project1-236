//
// Created by jared on 10/25/2021.
//

#include "Interpreter.h"

Interpreter::Interpreter(Database database, DatalogProgram datalogProgram) {
    this->database = database;
    this->datalogProgram = datalogProgram;
    int schemeSize = datalogProgram.schemes.size();
    for (int i = 0; i < schemeSize; i++) {
        Header* newHeader = new Header();
        int parameters = datalogProgram.schemes[i]->parameterList.size();
        for (int k = 0; k < parameters; k++){
            std::string newAttribute = datalogProgram.schemes[i]->parameterList[k]->p;
            newHeader->attributes.push_back(newAttribute);
        }
        std::string relationName = datalogProgram.schemes[i]->id;
        Relation* newRelation = new Relation(relationName, newHeader);
        database.addToMap(relationName,newRelation);
    }

    int factsSize = datalogProgram.facts.size();
    for (int i = 0; i < factsSize; i++) {
        Tuple* newTuple = new Tuple();
        int valuesSize = datalogProgram.facts[i]->parameterList.size();
        for (int k = 0; k < valuesSize; k++){
            std::string newValue = datalogProgram.facts[i]->parameterList[k]->p;
            newTuple->values.push_back(newValue);
        }
        std::string relationName = datalogProgram.facts[i]->id;
        Relation* tempRelation = database.mapOfRelations.at(relationName);
        tempRelation->tuples.insert(newTuple);

    }
}

Relation Interpreter::evaluatePredicate(Predicate p){

}