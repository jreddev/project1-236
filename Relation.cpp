//
// Created by jared on 10/25/2021.
//

#include "Relation.h"
#include <iostream>
#include <set>
#include <map>

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

Relation* Relation::Join(Relation* joinMe, std::string ruleName){
    std::vector<std::pair<int,int>> commonVals;
    Header* newHeader = this->header;
    int header2Size = joinMe->header->returnSize();
    for (int i = 0; i < header2Size; i++) {
        std::string attribute = joinMe->header->attributes[i];//Just so I remember, I changed this from header-attributes[i] to just attributes[i].
        int indexVal = this->header->find(attribute);
        if(indexVal != -1) {
            std::cout << attribute << "is a common element." << std::endl;
            std::pair<int,int> tempPair = std::make_pair(indexVal,i);
            commonVals.push_back(tempPair);
        }
        else {
            newHeader->attributes.push_back(attribute);
        }
    }
    Relation* newRelation = new Relation(ruleName,newHeader);
    std::string Header1Val = this->header->attributes[0];
    //int set1Size = this->tuples.size();
    //int set2Size = joinMe->tuples.size();
    bool joinAble = false;
    int numCommonVals = commonVals.size();
    /*for (int i = 0; i < set1Size; ++i) {
        for (int k = 0; k < numCommonVals; ++k) {
            if (i == commonVals[i].first){
                joinAble = true;
            }
        }
        for (int j = 0; j < set2Size; ++j) {
            if (j == commonVals[i].second && joinAble){

            }
        }
        joinAble = false;
    }*/
    int i = 0;
    for (Tuple t1 : tuples) {
        int j = 0;
        for (int k = 0; k < numCommonVals; ++k) {
            if (i == commonVals[i].first){
                joinAble = true;
            }
        }
        for (Tuple t2 : joinMe->tuples) {
            if (j == commonVals[i].second && joinAble){
                Tuple* newTuple = new Tuple;
                newTuple->values.reserve(t1.values.size() + t2.values.size());
                newTuple->values.insert(newTuple->values.end(),t1.values.begin(),t1.values.end());
                newTuple->values.insert(newTuple->values.end(),t2.values.begin(),t2.values.end());
                removeDuplicates(newTuple->values);
                newRelation->addTuple(*newTuple);
            }
            j++;
        }
        i++;
    }
    return newRelation;
}



void Relation::removeDuplicates(std::vector<std::string> &v)
{
    auto end = v.end();
    for (auto it = v.begin(); it != end; ++it) {
        end = std::remove(it + 1, end, *it);
    }

    v.erase(end, v.end());
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


Relation* Relation::Join2(Relation* joinMe, std::string ruleName){
    std::vector<std::pair<int,int>> commonVals;
    Header* newHeader = combineHeaders(this->header,joinMe->header,commonVals);
    Relation* newRelation = new Relation(ruleName,newHeader);
    bool joinAble = false;
    int numCommonVals = commonVals.size();
    int i = 0;
    for (Tuple t1 : tuples) {
        int j = 0;
        for (int k = 0; k < numCommonVals; ++k) {
            if (i == commonVals[i].first){
                joinAble = true;
            }
        }
        for (Tuple t2 : joinMe->tuples) {
            if (j == commonVals[i].second && joinAble){
                Tuple* newTuple = combineTuples(t1,t2);
                newRelation->addTuple(*newTuple);
            }
            j++;
        }
        i++;
    }
    return newRelation;
}

Header* Relation::combineHeaders(Header* header1, Header* header2, std::vector<std::pair<int,int>> commonVals) {
    Header* newHeader = new Header;
    int header2Size = header2->returnSize();
    for (int i = 0; i < header2Size; i++) {
        std::string attribute = header2->attributes[i];//Just so I remember, I changed this from header-attributes[i] to just attributes[i].
        int indexVal = header1->find(attribute);
        if(indexVal != -1) {
            std::cout << attribute << "is a common element." << std::endl;
            std::pair<int,int> tempPair = std::make_pair(indexVal,i);
            commonVals.push_back(tempPair);
        }
        else {
            newHeader->attributes.push_back(attribute);
        }
    }
    return newHeader;
}

Tuple *Relation::combineTuples(Tuple t1, Tuple t2) {
    Tuple* newTuple = new Tuple;
    newTuple->values.reserve(t1.values.size() + t2.values.size());
    newTuple->values.insert(newTuple->values.end(),t1.values.begin(),t1.values.end());
    newTuple->values.insert(newTuple->values.end(),t2.values.begin(),t2.values.end());
    removeDuplicates(newTuple->values);
    return newTuple;
}
