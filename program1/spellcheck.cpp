#include <iostream>
#include <ctime>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>

#include "hash.h"

#define MAX_LENGTH 20

using namespace std; 

int main() {
  
    string filename;
    cout << "Enter name of input file: "; 
    cin >> filename; 

    ifstream f (filename); 
    string line = ""; 
    //do something with file name

    cout << "Data loaded.\n";
    cout << "Executing sort...\n";

    clock_t t1 = clock(); 
    
    //create hash table object with initial size 50000
    hashTable *hash = new hashTable(50000); 

    while(!f.eof()) {
        
        //get content of line from file, if line is empty quit the loop
        getline(f, line);
        if(line.empty()) break;
        
        //insert each line in dictionary into hash table
        hash->insert(line); 
    }
    




    //do hash table insert and all those checks
    clock_t t2 = clock(); 
    double timeDiff = ((double)(t2-t1)) / CLOCKS_PER_SEC;

    cout << "Procedure finished. CPU time was " << timeDiff << " seconds\n"; 
    cout << "Enter name of output file: ";
    cin >> filename;



    return 0; 
}
