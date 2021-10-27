//
// Created by jared on 10/25/2021.
//

#ifndef PROJECT1_DATABASE_H
#define PROJECT1_DATABASE_H
#include <map>
#include <Relation.h>

class Database {
public:
    std::map<std::string, Relation> mapOfRelations;
    void addToMap(std::string name, Relation relation);
};


#endif //PROJECT1_DATABASE_H
