#ifndef HASHTABLE_H_
#define HASHTABLE_H_

#include <string>
#include <math.h>
#include "MyHash.h"
using namespace std;

/*
 * DESCRIPTION: Node to keep key-value pairs for the hash table. Collisions are resolved through chaining. This implementation of hash table will use linked lists to resolve collisions. User will have to set the key, value, and next manually.
 * 
 * AUTHOR: Anthony Seo
 */
template <class K, class V>
struct HashNode {
    K key;
    V value;
    HashNode<K, V> *next;
};

/*
 * DESCRIPTION: Prototype for the HashTable class. Descriptions of each method will be above the implementation.
 * 
 * AUTHOR: Anthony Seo
 */
template <class K, class V>
class HashTable {
  private:
    HashNode<K, V> **table;
    int capacity = 1000;
    MyHash<K> hashFunction;
    hash<K> stlHash;

  public:
    HashTable();
    ~HashTable();
    HashTable(const HashTable& other);
    void insert(K key, V value);
    V get(K key);
    void remove(K key);

    const HashTable& operator=(const HashTable& other);

    // testing methods below
    void viewDistribution();

  private:
    HashTable deepCopy(const HashTable &other);
    void initializeHashTable();
};

/*
 * DESCRIPTION: Constructor for the HashTable. Initializes private variables
 * 
 * OUTPUT: none
 * INPUTS: none
 */
template <class K, class V>
HashTable<K, V>::HashTable() {
    table = new HashNode<K, V>*[capacity];
    for (int i = 0; i < capacity; i++) {
        table[i] = nullptr;
    }
}

/*
 * DESCRIPTION: Copy constructor for the HashTable data structure. 
 * 
 * OUTPUTS: none
 * INPUTS: reference to HashTable to be copied
 */
template <class K, class V>
HashTable<K, V>::HashTable(const HashTable<K, V>& other) {
    table = new HashNode<K, V>*[capacity];
    for (int i = 0; i < capacity; i++) {
        table[i] = nullptr;
    }
    *this = other;
}

template <class K, class V>
HashTable<K, V>::~HashTable() {
    initializeHashTable();
    delete [] table;
}


template <class K, class V>
void HashTable<K, V>::insert(K key, V value) {
    int index = hashFunction(key) % capacity;
    HashNode<K, V> *newElement = new HashNode<K, V>;
    newElement->key = key;
    newElement->value = value;
    newElement->next = table[index];
    table[index] = newElement;
}

template <class K, class V>
V HashTable<K, V>::get(K key) {
    int index = hashFunction(key) % capacity;
    HashNode<K, V> *current = table[index];
    while (current != nullptr && current->key != key) {
        current = current->next;
    }
    if (current == nullptr) {
        throw "There are no items with key: " + key;
    }
    return current->value;
}

template <class K, class V>
void HashTable<K, V>::remove(K key) {
    int index = hashFunction(key) % capacity;
    HashNode<K, V> *current = table[index];
    HashNode<K, V> *temp;
    if (current != nullptr && current->key != key) {
        current = current->next;
    }
    if (current == nullptr) {
        cout << "Key: " << key << " not found." << endl;
    }

    // first item in the index
    if (current == table[index]) {
        temp = current;
        table[index] = table[index]->next;
    }
}

template <class K, class V>
const HashTable<K, V>& HashTable<K, V>::operator=(const HashTable<K, V>& other) {
    if (this != &other) {
        initializeHashTable();
        for (int i = 0; i < capacity; i++) {
            HashNode<K, V>* current = other.table[i];
            HashNode<K, V>* copiedLL = new HashNode<K, V>;
            copiedLL->next = nullptr;
            HashNode<K, V>* p = copiedLL;

            while (current != nullptr) {
                HashNode<K, V>* newNode = new HashNode<K, V>;
                newNode->key = current->key;
                newNode->value = current->value;
                newNode->next = nullptr;
                p->next =  newNode;
                p = p->next;
                current = current->next;
            }

            HashNode<K, V>* temp = copiedLL;
            copiedLL = copiedLL->next;
            table[i] = copiedLL;
            delete temp;

            HashNode<K, V>* thisCurrent = table[i];
            while (thisCurrent != nullptr) {
                cout << "this current: " << thisCurrent->key << " " << thisCurrent->value << endl;
                thisCurrent = thisCurrent->next;
            }
        }
    }
    
    return *this;
}

/*
 * DESCRIPTION: 
 * 
 * 
 */
template <class K, class V>
void HashTable<K, V>::initializeHashTable() {
    for (int i = 0; i < capacity; i++) {
        HashNode<K, V>* current = table[i];
        HashNode<K, V>* temp = nullptr;
        while (current != nullptr) {
            temp = current;
            current = current->next;
            delete temp;
        }
        table[i] = nullptr;
    }
}

template <class K, class V>
void HashTable<K, V>::viewDistribution() {
    HashNode<K, V> *current;
    for (int i = 0; i < capacity; i++) {
        current = table[i];
        int count = 0;
        while (current != nullptr) {
            current = current->next;
            count++;
        }
        cout << "table[" << i << "]: " << count << endl;
    }
}



#endif // HASHTABLE_H_