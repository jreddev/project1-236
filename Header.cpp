//
// Created by jared on 10/25/2021.
//

#include "Header.h"

int Header::returnSize(){
    int size = attributes.size();
    return size;
}

int Header::find(std::string findMe) {
    int size = attributes.size();
    for (int i = 0; i < size; i++) {
        if (attributes.at(i) == findMe) {
            return i;
        }
    }
    return -1;
}