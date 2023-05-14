//
// Created by lu'ren'jia'd's on 2021/11/17.
//

#ifndef UNTITLED6_1287MAP_H
#define UNTITLED6_1287MAP_H

#include <unordered_map>

class BigIndexArray {
public:
    std::unordered_map<long long, long long> big_array;

    ~BigIndexArray();

    long long &operator[](long long index);
};

BigIndexArray::~BigIndexArray() {
    big_array.clear();
}

long long &BigIndexArray::operator[](long long index) {
        return big_array[index];
}

#endif //UNTITLED6_1287MAP_H
