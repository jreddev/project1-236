//
// Created by jared on 10/25/2021.
//

#ifndef PROJECT1_RELATION_H
#define PROJECT1_RELATION_H
#include "Tuple.h"
#include "Header.h"
#include <set>

class Relation {
    Relation(std::string name, Header header);
    ~Relation();
    std::string name;
    Header header;
    set<Tuple> tuples;
    void addTuple(Tuple tuple);
    Relation select(int index, std::string value);
    Relation select(int index, int indexTwo);
    Relation project(vector<std::string> indices);
    Relation rename(vector<std::string> attributes);
    void toString();


};


#endif //PROJECT1_RELATION_H
