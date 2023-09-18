#include <iostream>
#include <ctime>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <vector> 

#include "hash.h"

#define MAX_LENGTH 20

using namespace std; 

int main() {
  
    string filename;
    cout << "Enter name of dictionary file: "; 
    cin >> filename; 

    ifstream dict (filename); 
    string line = ""; 
    //do something with file name

    cout << "Data loaded.\n";
    clock_t t1 = clock(); 
    
    //create hash table object with initial size 50000
    hashTable *hash = new hashTable(50000); 
    
    //dictionary insertion
    while(!dict.eof()) {
        
        //get content of line from file, if line is empty quit the loop
        getline(dict, line);
        if(line.empty()) break;
        
        string lower_word; 
        for(auto x : line) {
            lower_word += tolower(x); 
        }

        //insert each line in dictionary into hash table
        hash->insert(lower_word); 
    }
    
    //do hash table insert and all those checks
    clock_t t2 = clock(); 
    double timeDiff = ((double)(t2-t1)) / CLOCKS_PER_SEC;

    cout << "Dictionary load finished. CPU time was " << timeDiff << " seconds\n"; 
    cout << "Enter name of spell check file: "; 
    
    //loads new file into inf variable
    cin >> filename;
    ifstream check (filename); 
    
    //getting output file data
    string outfile; 
    cout << "Enter name of output file: ";
    cin >> outfile;
    ofstream ouf (outfile); 

    t1 = clock(); 
    int line_number = 1; 

    //spellcheck logic
    while(!check.eof()) {

        //buffer to store words
        vector<string> buffer; 
        
        //get content of line from file, if line is empty quit the loop
        getline(check, line);
        
        //convert word to lowercase
        string lower_line = "";  
        for(auto x : line) {
            lower_line += tolower(x); 
        }

        string word = "";
        
        for (int i = 0; i < lower_line.length(); i++) {

            //get letter at position i
            char x = lower_line[i]; 

            //if the letter is lowercase, an apostrophe, or hyphen, add it onto the word
            if ((x >= 97 && x <= 122) || (x == 39) || (x == '-')) {
                word = word + x;
            }

            //if the word is > 20 characters write an error to the output file
            else if (word.length() >= 20) {
                ouf << "Long word at line " << line_number << ", starts: " << word << "\n"; 
                
                //go to the next word seperator, then set the word to be empty
                while((x >= 97 && x <= 122) || (x == 39) || (x == '-')) {
                    x = lower_line[i++]; 
                }
                word = ""; 
            }
            //otherwise it's a word seperator and end the word, add it to the buffer
            else {
                buffer.push_back(word); 
                word = "";
            }
        }
        buffer.push_back(word); 
        
        //loop through words that made it onto the buffer and see if they're in the dictionary
        for(int i = 0; i < buffer.size(); i++) {
            if(!hash->contains(buffer[i])) {
                ouf << "Unknown word at line " << line_number << ": " << buffer[i] << "\n"; 
            }
        }
        line_number++;    
    }
    
    
    t2 = clock(); 
    timeDiff = ((double)(t2-t1)) / CLOCKS_PER_SEC;
    cout << "Spell check finished. CPU time was " << timeDiff << " seconds\n"; 

    return 0; 
}
