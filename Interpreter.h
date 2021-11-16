//
// Created by jared on 10/25/2021.
//

#ifndef PROJECT1_INTERPRETER_H
#define PROJECT1_INTERPRETER_H
#include "DatalogProgram.h"
#include "Database.h"
#include "Relation.h"

class Interpreter {
public:
    Interpreter(Database database, DatalogProgram inputDatalog);
    ~Interpreter();
    DatalogProgram myDatalog;
    Database database;



    Relation* evaluatePredicate(Predicate* p);

    void evaluateQueries();

    void initializeFacts();

    void initializeSchemes();

    Relation* findRelation(std::string id);

    bool findInMap(std::string value);

    bool findInVector(std::string id);

    bool findInVector(std::vector<std::string> searchVector, std::string id);

    void evaluateRules();
};


#endif //PROJECT1_INTERPRETER_H
