//
// Created by jared on 10/25/2021.
//

#ifndef PROJECT1_RELATION_H
#define PROJECT1_RELATION_H
#include "Tuple.h"
#include "Header.h"
#include <set>

class Relation {
public:
    Relation(std::string name, Header* header);
    ~Relation();
    std::string name;
    Header* header;
    std::set<Tuple> tuples;
    void addTuple(Tuple tuple);
    Relation* select(int index, std::string value);
    Relation* select(int index, int indexTwo);
    Relation* project(std::vector<int> indices);
    Relation* rename(std::vector<std::string> attributes);
    void toString();


    //Relation *Join(Relation *joinMe);

    Relation *Join(Relation *joinMe, std::string ruleName);

    void removeDuplicates(std::vector<std::string> &v);

    Relation *Join2(Relation *joinMe, std::string ruleName);

    Header *combineHeaders(Header *header1, Header *header2, std::vector<std::pair<int, int>> commonVals);

    Tuple *combineTuples(Tuple tuple, Tuple tuple1);

    Header *combineHeaders(Header *header1, Header *header2, std::vector<std::pair<int, int>> *commonVals);

    void ruleToString();

    Tuple *combineTuples(Tuple t1, Tuple t2, int headerSize);

    int unionize(Relation *newRelation);

    Tuple *combineTuples(Tuple t1, Tuple t2, int headerSize, std::vector<std::string> commonVals);

    void removeDuplicateTuples(std::vector<std::string> &v, std::vector<std::pair<int, int>> commonVals);

    void removeDuplicateTuples(std::vector<std::string> &v, std::vector<std::string> commonVals);

    void unite(Relation relation1);

    Relation join3(Relation relation1, Relation relation2);
};


#endif //PROJECT1_RELATION_H
