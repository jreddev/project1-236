//
// Created by jared on 10/25/2021.
//

#include "Relation.h"

Relation::Relation(std::string name, Header header){
    this->name = name;
    this->header = header;
}

Relation::~Relation(){
    std::cout << "destroy_me";
}

Relation::addTuple(Tuple tuple) {
    tuples.insert(tuple);
}

Relation Relation::select(int index, std::string value){

}
Relation Relation::select(int index, int indexTwo){

}
Relation Relation::project(vector<std::string> indices){

}
Relation Relation::rename(vector<std::string> attributes){

}
void Relation::toString(){

}