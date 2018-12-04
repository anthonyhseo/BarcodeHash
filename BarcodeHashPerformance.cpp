#include <iostream>
#include <sstream>
#include <fstream>
#include <time.h>
#include <stdio.h>
#include "HashTable.h"

using namespace std;

void init(HashTable<string, string> &hash);

/*
 * DESCRIPTION: Automated testing for HashTable. It will output a csv file to
 * graph the data.
 *
 * to compile: g++ BarcodeHashPerformance.cpp -o BarcodeHashPerformance.out
 * to run: ./BarcodeHashPerformance.out
 *
 * AUTHOR: Anthony Seo
 */
int main() {
    remove("results.csv");
    ofstream outputData;
    ifstream inFile;
    inFile.open("nthUPC.csv");
    outputData.open("results.csv");
    HashTable<string, string> products;
    init(products);

    // The loop that generates the data for the graph for performance comparison.
    while (!inFile.eof()) {
        string line;
        getline(inFile, line);

        string token;
        bool numberParsed = false;
        int nth;
        string testUPC;
        istringstream ss(line);
        while (getline(ss, token, ',')) {
            if (!numberParsed) {
                nth = stoi(token);
                numberParsed = true;
            } else {
                testUPC = token;
            }
        }

        double hashTime = 0;

        // timing data for HashTable.
        clock_t t = clock();
        cout << products.get(testUPC) << endl;
        t = clock() - t;
        hashTime = t * 1.0 / CLOCKS_PER_SEC * 1000;
        cout << "HashTable search time: " << hashTime << " milliseconds" << endl;

        outputData << nth << "," << hashTime << endl;
        
    }

    inFile.close();
    outputData.close();

    return 0;
}

/*
 * DESCRIPTION: This method initializes the product HashTable.
 *
 * OUTPUT: none
 * INPUTS: HashTable of products.
 * AUTHOR: Anthony Seo
 */
void init(HashTable<string, string>& hash) {
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