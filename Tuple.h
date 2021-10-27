//
// Created by jared on 10/25/2021.
//

#ifndef PROJECT1_TUPLE_H
#define PROJECT1_TUPLE_H
#include "vector"
#include <string>

class Tuple {
    std::vector<std::string> values;

    bool operator< (const Tuple &rhs) const {
        return values < rhs.values;
    }

    int returnSize();
};


#endif //PROJECT1_TUPLE_H
