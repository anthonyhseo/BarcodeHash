#ifndef MYHASH_H_
#define MYHASH_H_

#include <iostream>
using namespace std;

/*
 * DESCRIPTION: Class for the custom hash functions. Additional hash functions
 * can be added to this file based on other data types. Currently, only two hash
 * functions are implemented (strings and int).
 *
 * AUTHOR: Anthony Seo
 */
template <class T>
class MyHash {
  public:
    size_t operator()(const T &item);
};

/*
 * DESCRIPTION: Hash function for strings. Algorithm is based on the book
 * implementation of the string hash.
 *
 * OUTPUT: hash value (size_t)
 * INPUTS: reference to string to be hashed
 * AUTHOR: Anthony Seo
 */
template <>
class MyHash<string> {
  public:
    size_t operator()(const string &item) {
        size_t result = 0;
        for (char ch : item) {
            result = 37 * result + ch;
        }

        return result;
    }
};

/*
 * DESCRIPTION: Hash function for ints. The hash function just returns the int.
 *
 * OUTPUT: hash value (size_t)
 * INPUTS: reference to integer
 * AUTHOR: Anthony Seo
 */
template <>
class MyHash<int> {
  public:
    size_t operator()(const int &item) { return item; }
};

#endif