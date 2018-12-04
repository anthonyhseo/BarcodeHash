#ifndef HASHTABLE_H_
#define HASHTABLE_H_

#include <string>
#include <math.h>
#include "MyHash.h"
using namespace std;

/*
 * DESCRIPTION: Node to keep key-value pairs for the hash table. Collisions are
 * resolved through chaining. This implementation of hash table will use linked
 * lists to resolve collisions. User will have to set the key, value, and next
 * manually.
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
 * DESCRIPTION: Prototype for the HashTable class. Descriptions of each method
 * will be above the implementation.
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
    void initializeHashTable();
};

/*
 * DESCRIPTION: Constructor for the HashTable. Initializes private variables for
 * the HashTable class.
 *
 * OUTPUT: none
 * INPUTS: none
 * AUTHOR: Anthony Seo
 */
template <class K, class V>
HashTable<K, V>::HashTable() {
    table = new HashNode<K, V>*[capacity];
    for (int i = 0; i < capacity; i++) {
        table[i] = nullptr;
    }
}

/*
 * DESCRIPTION: Copy constructor for the HashTable data structure. Implemented
 * for part of the rule of Big Three.
 *
 * OUTPUT: none
 * INPUTS: reference to HashTable to be copied
 * AUTHOR: Anthony Seo
 */
template <class K, class V>
HashTable<K, V>::HashTable(const HashTable<K, V>& other) {
    table = new HashNode<K, V>*[capacity];
    for (int i = 0; i < capacity; i++) {
        table[i] = nullptr;
    }
    *this = other;
}

/*
 * DESCRIPTION: Destructor for the HashTable class. Free's up dynamic memory
 * elements to prevent memory leaks.
 *
 * OUTPUT: none
 * INPUTS: none
 * AUTHOR: Anthony Seo
 */
template <class K, class V>
HashTable<K, V>::~HashTable() {
    initializeHashTable();
    delete [] table;
}

/*
 * DESCRIPTION: This method insert a key-value pair into the HashTable. If a
 * node with key is found, the node's value will be overwritten.
 *
 * OUTPUT: none
 * INPUTS: K key, V value
 * AUTHOR: Anthony Seo
 */
template <class K, class V>
void HashTable<K, V>::insert(K key, V value) {
    int index = hashFunction(key) % capacity;
    HashNode<K, V> *current = table[index];
    // traverse through the linked list and find the node with key
    while (current != nullptr && current->key != key) {
        current = current->next;
    }

    // node with key not found, create a new one.
    if (current == nullptr) {
        HashNode<K, V> *newElement = new HashNode<K, V>;
        newElement->key = key;
        newElement->value = value;
        newElement->next = table[index];
        table[index] = newElement;
    } else {
        // node with key found, overwriting the value.
        current->value = value;
    }
    
}

/*
 * DESCRIPTION: This method gets a value when providing a key to the HashTable.
 *
 * OUTPUT: V value
 * INPUTS: K key
 * THROWS: exception if key-value pair is not found
 * AUTHOR: Anthony Seo
 */
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

/*
 * DESCRIPTION: This method removes a key-value pair after providing a key to
 * the HashTable.
 *
 * OUTPUT: V value
 * INPUTS: K key
 * THROWS: exception if key-value pair is not found
 * AUTHOR: Anthony Seo
 */
template <class K, class V>
void HashTable<K, V>::remove(K key) {
    int index = hashFunction(key) % capacity;
    HashNode<K, V> *current = table[index];
    HashNode<K, V> *prev;
    HashNode<K, V> *temp;
    if (current == nullptr) {
        throw "There are no elements with that key.";
    }
    // first item in the index
    if (current->key == key) {
        temp = current;
        table[index] = current->next;
        delete temp;
    } else {
        while (current != nullptr && current->key != key) {
            prev = current;
            current = current->next;
        }

        if (current == nullptr) {
            throw "There are no elements with that key.";
        }
        
        temp = current;
        prev->next = current->next;
        delete temp;
    }
}

/*
 * DESCRIPTION: Assignment operator for the HashTable class. Implemented for
 * part of the rule of big three.
 *
 * OUTPUT: reference to the hash copied hash table
 * INPUTS: reference to HashTable to be copied.
 * AUTHOR: Anthony Seo
 */
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
                p->next = newNode;
                p = p->next;
                current = current->next;
            }

            HashNode<K, V>* temp = copiedLL;
            copiedLL = copiedLL->next;
            table[i] = copiedLL;
            delete temp;
        }
    }
    
    return *this;
}

/*
 * DESCRIPTION: Private method to empty the HashTable to the initial state.
 * This is essentially a helper for the destructor, copy constructor and 
 * assignment operator.
 * 
 * OUTPUT: none
 * INPUTS: none
 * AUTHOR: Anthony Seo
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

#endif // HASHTABLE_H_