//
// Created by jared on 10/25/2021.
//

#ifndef PROJECT1_INTERPRETER_H
#define PROJECT1_INTERPRETER_H
#include "DatalogProgram.h"
#include "Database.h"

class Interpreter {
    Interpreter(Database database, DatalogProgram datalogProgram);
    ~Interpreter();
    DatalogProgram datalogProgram;
    Database database;

};


#endif //PROJECT1_INTERPRETER_H
