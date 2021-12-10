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
    /*for (int i = 0; i < headerSize; i++) {
        std::string attribute = header->attributes[i];
        for (int j = 0; j < vectorSize; j++) {
            int index = indices[j];
            if (index == i) {
                newHeader->attributes.push_back(attribute);
            }
        }
    }*/
    for (int j = 0; j < vectorSize; j++) {
        for (int i = 0; i < headerSize; i++) {
            std::string attribute = header->attributes[i];
            int index = indices[j];
            if (index == i) {
                newHeader->attributes.push_back(attribute);
            }
        }
    }


    Relation* projectRelation = new Relation(name,newHeader);

   // int newHeaderSize = newHeader->attributes.size();

    for (const Tuple &t : tuples) {
        Tuple newTuple = Tuple();
        for (int j = 0; j < vectorSize; j++) {
            for (int i = 0; i < headerSize; i++) {
                std::string attribute = header->attributes[i];
                int index = indices[j];
                int tValSize = t.values.size();
                if (index == i && i < tValSize) {
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

int Relation::unionize(Relation* newRelation) {
    int tuplesAdded = 0;
    Relation* ogRelation = this;
    for (Tuple t : newRelation->tuples) {
        if (ogRelation->tuples.insert(t).second) {
            tuplesAdded++;
            //newRelation->ruleToString();
            int whileNum = 0;
            int headerSize = this->header->attributes.size();
            while (whileNum < headerSize) {
                std::cout << "  " << this->header->attributes[whileNum] << "=" << t.values[whileNum];
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
    return tuplesAdded;
}

Relation* Relation::Join(Relation* joinMe, std::string ruleName){
    std::vector<int> rel1pairVals;
    std::vector<int> rel2pairVals;
    std::vector<int> rel2nonMatchVals;
    int rel1loopVal = this->header->returnSize();
    int rel2loopVal = joinMe->header->returnSize();

    Header* newHeader = new Header;

    for (int i = 0; i < rel1loopVal; ++i) {
        bool pairFound = false;
        for (int j = 0; j < rel2loopVal; ++j) {
            if  (header->attributes[i] == joinMe->header->attributes[j]) {
                rel1pairVals.push_back(i);
                rel2pairVals.push_back(j);
                newHeader->attributes.push_back(header->attributes[i]);
                pairFound = true;
            }
        }
        if (!pairFound) {
            newHeader->attributes.push_back(header->attributes[i]);
        }
    }
    for (int i = 0; i < rel2loopVal; ++i) {
        bool pairFound = false;
        for (int j = 0; j < rel1loopVal; ++j) {
            if  (header->attributes[j] == joinMe->header->attributes[i]) {
                //rel1pairVals.push_back(i);
                //rel2pairVals.push_back(j);
                //newHeader->attributes.push_back(header->attributes[i]);
                pairFound = true;
            }

        }
        if (!pairFound) {
            newHeader->attributes.push_back(joinMe->header->attributes[i]);
            rel2nonMatchVals.push_back(i);
        }
    }




    Relation* newRelation = new Relation(ruleName, newHeader);
    int tVal1 = 0;
    if (!rel1pairVals.empty()) {
        for (Tuple t1 : tuples) {
            int tVal2 = 0;
            for (Tuple t2 : joinMe->tuples) {
                if (!rel1pairVals.empty() && !rel2pairVals.empty()) {
                    //if (rel1pairVals[0] == tVal1 && rel2pairVals[0] == tVal2) {
                    if (t1.values[rel1pairVals[0]] == t2.values[rel2pairVals[0]]) {
                        Tuple *newTuple = new Tuple();
                        int t1size = t1.values.size();
                        for (int i = 0; i < t1size; ++i) {
                            newTuple->values.push_back(t1.values[i]);
                        }
                        int t2size = rel2nonMatchVals.size();
                        for (int i = 0; i < t2size; ++i) {
                            newTuple->values.push_back(t2.values[rel2nonMatchVals[i]]);
                        }
                        newRelation->addTuple(*newTuple);
                        //rel2pairVals.pop_back();
                        //rel1pairVals.pop_back();
                    }
                    //}
                }


                tVal2++;
            }
            tVal1++;
        }
    }
    else {
        for (Tuple t1 : tuples) {
            for (Tuple t2 : joinMe->tuples) {
                Tuple *newTuple = new Tuple();
                int t1size = t1.values.size();
                for (int i = 0; i < t1size; ++i) {
                    newTuple->values.push_back(t1.values[i]);
                }
                int t2size = t2.values.size();
                for (int i = 0; i < t2size; ++i) {
                    newTuple->values.push_back(t2.values[i]);
                }
                newRelation->addTuple(*newTuple);
            }
        }
    }

    return newRelation;
}