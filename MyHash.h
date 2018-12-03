#ifndef MYHASH_H_
#define MYHASH_H_

#include <iostream>
#include <math.h>
using namespace std;

/*
 * DESCRIPTION: Class for the hash functions
 * 
 * AUTHOR: Anthony Seo
 */
template <class T>
class MyHash {
    public:
    size_t operator()(const T& item);

};

/*
 * DESCRIPTION: Hash function for strings. 
 * 
 * AUTHOR: Anthony Seo
 */
template <>
class MyHash<string> {
    public:
    size_t operator()(const string& item) {
        size_t result = 0;
        for (char ch : item) {
            result = 37 * result + ch;
        }

        return result;
    }
};

template <>
class MyHash<int> {
    public:
    size_t operator()(const int& item) {
        return item;
    }
};

#endif