#include <iostream>
#include <sstream>
#include <fstream>
#include <time.h>

#include "HashTable.h"
using namespace std;


void init(HashTable<string, string> &hash);


int main() {
    HashTable<string, string> products;

    clock_t t = clock();
    init(products);
    t = clock() - t;
    cout << t * 1.0 / CLOCKS_PER_SEC << endl;

    string upc;
    while (upc != "quit") {
        cout << "Enter the UPC of the product you want to retrieve: ";
        getline(cin, upc);
        if (upc == "quit") {
            cout << "Quitting..." << endl;
            break;
        }
        t = clock();
        try {
            cout << products.get(upc) << endl;
        } catch (const char* e) {
            cout << "could not find product with UPC: " << upc << endl;
        }
        
        // cout << productsSTL[upc] << endl;
        t = clock() - t;
        cout << t * 1.0 / CLOCKS_PER_SEC * 1000 << endl;
    }


    return 0;
}

void init(HashTable<string, string> &hash) {
    string output;
    ifstream file;
    file.open("upc_corpus.txt");
    while (getline(file, output)) {
        bool upcParsed = false;
        string upc = "";
        string desc = "";
        string token = "";
        istringstream ss(output);
        while (getline(ss, token, ',')) {
            if (!upcParsed) {
                upc = token;
                upcParsed = true;
            } else {
                // += because there might be commas in the description.
                desc += token;
            }
        }

        hash.insert(upc, desc);
    }

}
