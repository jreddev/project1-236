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

Relation* Relation::select(int index, std::string value){
    Relation* selectedRelation = new Relation(name, header);
    for (const Tuple &t : tuples) {
        std::string tVal = t.values[index];
        if(tVal == value){
            selectedRelation->addTuple(t);
        }
    }
    return selectedRelation;
}
Relation* Relation::select(int index, int indexTwo){
    Relation* selectedRelation = new Relation(name, header);
    for (const Tuple &t : tuples) {
        std::string tVal = t.values[index];
        std::string tValTwo = t.values[indexTwo];
        if(tVal == tValTwo){
            selectedRelation->addTuple(t);
        }
    }
    return selectedRelation;
}
Relation* Relation::project(std::vector<int> indices){
    Header* newHeader = new Header();
    int headerSize = header->returnSize();
    int vectorSize = indices.size();
    for (int i = 0; i < headerSize; i++) {
        std::string attribute = header->attributes[i];
        for (int j = 0; j < vectorSize; j++) {
            int index = indices[j];
            if (index == i) {
                newHeader->attributes.push_back(attribute);
            }
        }
    }

    Relation* projectRelation = new Relation(name,newHeader);

    for (const Tuple &t : tuples) {
        Tuple newTuple = Tuple();
        for (int i = 0; i < headerSize; i++) {
            std::string attribute = header->attributes[i];
            for (int j = 0; j < vectorSize; j++) {
                int index = indices[j];
                if (index == i) {
                    std::string tupleVal = t.values.at(i); //might be j instead of i.. just watch out.
                    newTuple.values.push_back(tupleVal);
                }
            }
        }
        projectRelation->addTuple(newTuple);
    }
    return projectRelation;
}
Relation* Relation::rename(std::vector<std::string> attributes){

    Header* newHeader = new Header();
    int headerSize = header->returnSize();
    for (int i = 0; i < headerSize; i++) {
        std::string attribute = attributes[i];  //Just so I remember, I changed this from header-attributes[i] to just attributes[i].
        newHeader->attributes.push_back(attribute);
    }
    Relation* renameRelation = new Relation(name,newHeader);

    for (const Tuple &t : tuples) {
        renameRelation->addTuple(t);
    }
    return renameRelation;

    /*Header* newHeader = new Header();
    int rowSize = header->returnSize();
    int vectorSize = attributes.size();
    for (Tuple t : tuples) {

        for (int j = 0; j < vectorSize; j++) {
            std::string attribute = t.values.at(j);
            std::string index = attributes[j];
            if (index == attribute) {

            }
        }
    }

    Relation* renameRelation = new Relation(name,newHeader);

    return renameRelation;*/
}
/*void Relation::toString(){
    if (!tuples.empty()){
        int tupleSize = tuples.size();
        int headerSize = header->attributes.size();
        //std::cout << name << std::endl;
        for (auto t : tuples) {
            for(int i = 0; i < tupleSize-1; i++) {
                std::cout << header->attributes[i] << "=" << t.values[i] << ", ";
            }
            std::cout << header->attributes[headerSize-1] << "='" << t.values[tupleSize-1] << "'"<< std::endl;
        }

    }
}*/

void Relation::toString(){
    //int tupleSize = tuples.size();
    int headerSize = header->attributes.size();
    if (!tuples.empty()){
        for (Tuple t : tuples) {
            int whileNum = 0;
            while (whileNum < headerSize) {
                std::cout << "  " << header->attributes[whileNum] << "=" << t.values[whileNum];
                if (whileNum < (headerSize - 1)) {
                    std::cout << ", ";
                }
                if (whileNum == headerSize - 1) {
                    std::cout << std::endl;
                }


                whileNum++;
            }
        }
    }
}





/*for (int i = 0; i < headerSize; i++) {
        std::string attribute = header->attributes[i];
        for (int j = 0; j < vectorSize; j++) {
            std::string index = indices[j];
            if (index == attribute) {
                newHeader->attributes.push_back(attribute);
            }
        }
    }*/