//
// Created by jared on 10/25/2021.
//

#include "Interpreter.h"

Interpreter::Interpreter(Database database, DatalogProgram datalogProgram) {
    this->database = database;
    this->datalogProgram = datalogProgram;
    int schemeSize = datalogProgram.schemes.size();
    for (int i = 0; i < schemeSize; i++) {

        Relation newRelation = new Relation(datalogProgram.schemes[i]->id,)

    }
}