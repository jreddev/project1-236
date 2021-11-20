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

    int newHeaderSize = newHeader->attributes.size();

    for (const Tuple &t : tuples) {
        Tuple newTuple = Tuple();
        for (int i = 0; i < headerSize; i++) {
            std::string attribute = header->attributes[i];
            for (int j = 0; j < vectorSize; j++) {
                int index = indices[j];
                if (index == i && i < t.values.size()) {
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

void Relation::ruleToString(){
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

/*Relation* Relation::Join(Relation* joinMe, std::string ruleName){
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
    }
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
*/
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
    Header* newHeader = new Header;
    Header* header2 = joinMe->header;
    int header1Size = this->header->returnSize();
    for (int i = 0; i < header1Size; i++) {
        std::string attribute1 = header->attributes[i];
        int indexVal = header2->find(attribute1);
        if(indexVal != -1) {
            //std::cout << attribute1 << " is a common element." << std::endl;
        }
        else {
            newHeader->attributes.push_back(attribute1);
        }
    }
    int header2Size = header2->returnSize();
    for (int i = 0; i < header2Size; i++) {
        std::string attribute2 = header2->attributes[i];//Just so I remember, I changed this from header-attributes[i] to just attributes[i].
        int indexVal = header->find(attribute2);
        if(indexVal != -1) {
            //std::cout << attribute2 << " is a common element." << std::endl;
            std::pair<int,int> tempPair = std::make_pair(indexVal,i);
            commonVals.push_back(tempPair);
            newHeader->attributes.push_back(attribute2); //not sure about this line
        }
        else {
            newHeader->attributes.push_back(attribute2);
        }
    }

    Relation* newRelation = new Relation(ruleName,newHeader);
    bool joinAble = false;
    int numCommonVals = commonVals.size();
    //--
    if (numCommonVals > 0) {
       for (Tuple t1 : tuples) {
           for (Tuple t2 : joinMe->tuples) {
               for (int i = 0; i < numCommonVals; ++i) {
                   if (t1.values[commonVals[i].first] == t2.values[commonVals[i].second]) {
                       Tuple* newTuple = combineTuples(t1,t2,newHeader->returnSize());
                       newRelation->addTuple(*newTuple);
                   }
               }
           }
       }
    }
    //--
    else {
        //std::cout << "no common vals, do cross multiply" << std::endl;
        for (Tuple t1 : tuples) {
            for (Tuple t2 : joinMe->tuples) {
                Tuple* newTuple = combineTuples(t1,t2,newHeader->returnSize());
                newRelation->addTuple(*newTuple);
            }
        }
    }

    return newRelation;
}

Header* Relation::combineHeaders(Header* header1, Header* header2, std::vector<std::pair<int,int>> *commonVals) {
    Header* newHeader = new Header;
    int header2Size = header2->returnSize();
    for (int i = 0; i < header2Size; i++) {
        std::string attribute2 = header2->attributes[i];//Just so I remember, I changed this from header-attributes[i] to just attributes[i].
        int indexVal = header1->find(attribute2);
        if(indexVal != -1) {
            std::cout << attribute2 << " is a common element." << std::endl;
            std::pair<int,int> tempPair = std::make_pair(indexVal,i);
            commonVals->push_back(tempPair);
            newHeader->attributes.push_back(attribute2); //not sure about this line
        }
        else {
            newHeader->attributes.push_back(attribute2);
        }
    }
    int header1Size = this->header->returnSize();
    for (int i = 0; i < header1Size; i++) {
        std::string attribute1 = header1->attributes[i];
        int indexVal = header2->find(attribute1);
        if(indexVal != -1) {
            std::cout << attribute1 << " is a common element." << std::endl;
            std::pair<int,int> tempPair = std::make_pair(indexVal,i);
            commonVals->push_back(tempPair);
        }
        else {
            newHeader->attributes.push_back(attribute1);
        }
    }
    return newHeader;
}

Tuple *Relation::combineTuples(Tuple t1, Tuple t2, int headerSize) {
    Tuple* newTuple = new Tuple;
    int newTuplesSize = t1.values.size() + t2.values.size();
    newTuple->values.reserve(t1.values.size() + t2.values.size());
    newTuple->values.insert(newTuple->values.end(),t1.values.begin(),t1.values.end());
    newTuple->values.insert(newTuple->values.end(),t2.values.begin(),t2.values.end());
    if (headerSize < newTuplesSize) {
        //removeDuplicates(newTuple->values);
    }
    return newTuple;
}




/* if (numCommonVals > 0) {
        int i = 0;
        for (Tuple t1 : tuples) {
            int j = 0;
            for (int k = 0; k < numCommonVals; ++k) {
                if (numCommonVals > i && i == commonVals[i].first){
                    joinAble = true;
                }
            }
            for (Tuple t2 : joinMe->tuples) {
                if (j == commonVals[j].second && joinAble){ //FIXME :: don't access commonvals[i] if it is empty.
                    Tuple* newTuple = combineTuples(t1,t2);
                    newRelation->addTuple(*newTuple);
                }

if (joinAble && t1.values[commonVals[i].first] == t2.values[commonVals[i].second]) {
Tuple* newTuple = combineTuples(t1,t2);
newRelation->addTuple(*newTuple);
}
if (joinAble && t1.values[commonVals[i].second] == t2.values[commonVals[i].first]) {
Tuple* newTuple = combineTuples(t1,t2);
newRelation->addTuple(*newTuple);
}
j++;
}
i++;
joinAble = false;
}
}*/