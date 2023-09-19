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


//function that takes in a string and converts the entire string to lowercase
string lowerString(const string &line) {
    
    string lower_line = "";  
    for(auto x : line) {
        lower_line += tolower(x); 
    }
    return lower_line; 
}

int main() {
  
    string filename;
    cout << "Enter name of dictionary file: "; 
    cin >> filename; 

    ifstream dict (filename); 
    string line = ""; 

    cout << "Data loaded.\n";
    clock_t t1 = clock(); 
    
    //create hash table object with initial size 50000
    hashTable *hash = new hashTable(50000); 
    
    //dictionary insertion
    while(!dict.eof()) {
        
        //get content of line from file, if line is empty quit the loop
        getline(dict, line);
        if(line.empty()) break;
        
        //convert line to lowercase
        line = lowerString(line); 

        //insert each line in dictionary into hash table
        hash->insert(line); 
    }
    
    clock_t t2 = clock(); 
    double timeDiff = ((double)(t2-t1)) / CLOCKS_PER_SEC;

    cout << "Dictionary load finished. CPU time was " << timeDiff << " seconds\n"; 
    
    //get spell check file
    cout << "Enter name of spell check file: "; 
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
        
        //get content of line from file, if line is empty, skip it
        getline(check, line);
        if(line.empty()) {
            line_number++; 
            continue;
        }
        
        //convert line to lowercase
        line = lowerString(line); 
        
        //variable to store current word
        string word = "";
        
        for (int i = 0; i < line.length(); i++) {

            //get letter at position i
            char x = line[i]; 

            //if the word is > 20 characters write an error to the output file
            if (word.length() >= 20) {
                ouf << "Long word at line " << line_number << ", starts: " << word << "\n"; 
                
                //go to the next word seperator, then set the word to be empty
                while((x >= 97 && x <= 122) || (x == 39) || (x == '-')) {
                    x = line[++i]; 
                }
                word = ""; 
            }

            //if the letter is lowercase, an apostrophe, or hyphen, add it onto the word
            else if ((x >= 97 && x <= 122) || (x == 39) || (x == '-')) {
                word = word + x;
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
            
            //final purge to get out any empty lines that somehow made it in
            if (!buffer[i].length()) continue; 
            
            //write to output file if the word isn't in the hash table
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
