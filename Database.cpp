//
// Created by jared on 10/25/2021.
//

#include "Database.h"

void Database::addToMap(std::string name, Relation* relation) {
    mapOfRelations.insert({name, relation});
}