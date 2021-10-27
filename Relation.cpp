//
// Created by jared on 10/25/2021.
//

#include "Relation.h"
#include <iostream>

Relation::Relation(std::string name, Header* header){
    this->name = name;
    this->header = header;
}

Relation::~Relation(){
    std::cout << "destroy_me";
}

void Relation::addTuple(Tuple tuple) {
    tuples.insert(tuple);
}

Relation Relation::select(int index, std::string value){

}
Relation Relation::select(int index, int indexTwo){

}
Relation Relation::project(std::vector<std::string> indices){

}
Relation Relation::rename(std::vector<std::string> attributes){

}
void Relation::toString(){
    int headerSize = header->returnSize();
    for (Tuple t : tuples) {
        for(int i = 0; i < headerSize-1; i++) {
            std::cout << header->attributes[i] << "='" << t.values[i] << "', ";
        }
        std::cout << header->attributes[headerSize-1] << "='" << t.values[headerSize-1] << "'"<< std::endl;
    }
}