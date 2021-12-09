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
        /*for (int i = 0; i < headerSize; i++) {
            std::string attribute = header->attributes[i];
            for (int j = 0; j < vectorSize; j++) {
                int index = indices[j];
                if (index == i && i < t.values.size()) {
                    std::string tupleVal = t.values.at(i); //might be j instead of i.. just watch out.
                    newTuple.values.push_back(tupleVal);
                }
            }
        }*/
        for (int j = 0; j < vectorSize; j++) {
            for (int i = 0; i < headerSize; i++) {
                std::string attribute = header->attributes[i];
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

Relation* Relation::Join2(Relation* joinMe, std::string ruleName){
    std::vector<std::pair<int,int>> commonVals;
    std::vector<std::string> commonValsStrings;
    std::vector<int> commonValsInt;
    Header* newHeader = new Header();
    Header* header2 = joinMe->header;
    int header1Size = this->header->returnSize();
    for (int i = 0; i < header1Size; i++) {
        std::string attribute1 = header->attributes[i];
        int indexVal = header2->find(attribute1);
        if(indexVal != -1) {
            //std::cout << attribute1 << " is a common element." << std::endl;
            std::pair<int,int> tempPair = std::make_pair(i,indexVal);
            commonVals.push_back(tempPair);
            commonValsInt.push_back(i);
            newHeader->attributes.push_back(attribute1);
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
            /*std::pair<int,int> tempPair = std::make_pair(indexVal,i);
            commonVals.push_back(tempPair);
             commanValsStrings.push_back(attribute1);
            newHeader->attributes.push_back(attribute2); //not sure about this line*/
        }
        else {
            newHeader->attributes.push_back(attribute2);
        }
    }
    int m = 0;
    for (int n = 0; n < commonValsInt.size(); ++n) {
        for (Tuple t1 : tuples) {
            if (commonValsInt[n] == m) {
                commonValsStrings.push_back(t1.values.at(m));
            }
            m++;
        }
    }

    Relation* newRelation = new Relation(ruleName,newHeader);
    bool joinAble = false;
    int numCommonVals = commonVals.size();
    int headerSize = newHeader->returnSize();
    //--
    if (numCommonVals > 0) {
       for (Tuple t1 : tuples) {
           \
           for (Tuple t2 : joinMe->tuples) {
               for (int i = 0; i < numCommonVals; ++i) {
                   if (t1.values[commonVals[i].first] == t2.values[commonVals[i].second]) {
                     //  Tuple* newTuple = combineTuples(t1,t2,headerSize,commonValsStrings);
                       Tuple* newTuple = new Tuple;
                       int newTuplesSize = t1.values.size() + t2.values.size();
                       newTuple->values.reserve(t1.values.size() + t2.values.size());
                       newTuple->values.insert(newTuple->values.end(),t1.values.begin(),t1.values.end());
                       if(commonVals[i].second != 0) {
                           newTuple->values.insert(newTuple->values.end(),t2.values.begin(),t2.values.begin() + commonVals[i].second - 1);
                       }
                       newTuple->values.insert(newTuple->values.end(),t2.values.begin() + commonVals[i].second + 1,t2.values.end());
                       /*if (headerSize < newTuplesSize) {
                           removeDuplicateTuples(newTuple->values, commonVals);
                       }*/
                       newRelation->addTuple(*newTuple);
                   }
               }
           }
       }
    }
    /**if (numCommonVals > 0) {
        int i = 0;
        int j = 0;
        for (Tuple t1 : tuples) {
            for (Tuple t2 : joinMe->tuples) {
                if (t1.values[commonVals[i].first] == t2.values[commonVals[i].second]) {
                    Tuple* newTuple = combineTuples(t1,t2,headerSize,commonValsStrings);
                    newRelation->addTuple(*newTuple);
                }
                j++;
            }
            i++;
        }
    }*/
    //--
    else {
        //std::cout << "no common vals, do cross multiply" << std::endl;
        for (Tuple t1 : tuples) {
            for (Tuple t2 : joinMe->tuples) {
                Tuple* newTuple = combineTuples(t1,t2,headerSize);
                newRelation->addTuple(*newTuple);
            }
        }
    }

    return newRelation;
}

Tuple *Relation::combineTuples(Tuple t1, Tuple t2, int headerSize, std::vector<std::string> commonVals) {
    Tuple* newTuple = new Tuple;
    int newTuplesSize = t1.values.size() + t2.values.size();
    newTuple->values.reserve(t1.values.size() + t2.values.size());
    newTuple->values.insert(newTuple->values.end(),t1.values.begin(),t1.values.end());
    newTuple->values.insert(newTuple->values.end(),t2.values.begin(),t2.values.end());
    if (headerSize < newTuplesSize) {
        removeDuplicateTuples(newTuple->values, commonVals);
    }
    return newTuple;
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

Tuple *Relation::combineTuples(Tuple t1, Tuple t2, int headerSize) {
    Tuple* newTuple = new Tuple;
    int newTuplesSize = t1.values.size() + t2.values.size();
    newTuple->values.reserve(t1.values.size() + t2.values.size());
    newTuple->values.insert(newTuple->values.end(),t1.values.begin(),t1.values.end());
    newTuple->values.insert(newTuple->values.end(),t2.values.begin(),t2.values.end());
    return newTuple;
}

void Relation::removeDuplicateTuples(std::vector<std::string> &v, std::vector<std::string> commonVals){
    std::set<std::string> seen;
    for (int i = 0; i < v.size(); ++i) {
        for (int j = 0; j < commonVals.size(); ++j) {
            if (v[i] == commonVals[j]) {
                if (seen.insert(v[i]).second) {
                    //std::cout << "test first seen" << std::endl;
                }
                else {
                    v.erase(v.begin() + i -1);
                }
            }
        }
    }
}

Relation* Relation::Join(Relation* joinMe, std::string ruleName){
    std::vector<int> rel1pairVals;
    std::vector<int> rel2pairVals;
    std::vector<int> rel2nonMatchVals;
    int rel1loopVal = this->header->returnSize();
    int rel2loopVal = joinMe->header->returnSize();

    Header* newHeader = new Header;
    /*for (int i = 0; i < rel1loopVal; ++i) {
        std::string rel1attribute = header->attributes[i];
        int indexVal = joinMe->header->find(rel1attribute);
        if (indexVal != -1) {
            rel1pairVals.push_back(i);
            rel2pairVals.push_back(indexVal);
            newHeader->attributes.push_back(rel1attribute);
        }
        else {
            newHeader->attributes.push_back(rel1attribute);
        }
    }
    for (int i = 0; i < rel2loopVal; ++i) {
        std::string rel2attribute = joinMe->header->attributes[i];
        int indexVal = header->find(rel2attribute);
        if (indexVal == -1) {
            //rel1pairVals.push_back(i);
            //rel2pairVals.push_back(indexVal);

            newHeader->attributes.push_back(rel2attribute);
        }
        else {
            rel2nonMatchVals.push_back(indexVal);
            //newHeader->attributes.push_back(rel2attribute);
        }
    }*/

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
                        for (int i = 0; i < t1.values.size(); ++i) {
                            newTuple->values.push_back(t1.values[i]);
                        }
                        for (int i = 0; i < rel2nonMatchVals.size(); ++i) {
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
                for (int i = 0; i < t1.values.size(); ++i) {
                    newTuple->values.push_back(t1.values[i]);
                }
                for (int i = 0; i < t2.values.size(); ++i) {
                    newTuple->values.push_back(t2.values[i]);
                }
                newRelation->addTuple(*newTuple);
            }
        }
    }

    return newRelation;
}



/*for (int i = 0; i < header->returnSize(); ++i) {
    newHeader->attributes.push_back(header->attributes[i]);
}
rel1loopVal = newHeader->returnSize();
for (int i = 0; i < rel1loopVal; ++i) {
    for (int j = 0; j < rel2loopVal; ++j) {
        if (newHeader->attributes[i] == joinMe->header->attributes[j]) {
            //add matching indices to vectors
            rel1pairVals.push_back(i);
            rel2pairVals.push_back(j);
        }
        else {
            newHeader->attributes.push_back(joinMe->header->attributes[j]);
            rel2nonMatchVals.push_back(j);
        }
    }
}*/

