#include "graph.h"

#include <climits>
#include <stdlib.h>

#include <vector>
#include <tuple> 
#include <ctime> 
#include <iostream>
#include <sstream> 
#include <fstream> 
#include <iostream>

using namespace std; 

void parseFile(graph *g) {

    string file_name; 
    cout << "Enter name of graph file: "; 
    cin >> file_name; 

    ifstream links(file_name); 
    string line; 

    //graph insertion
    while(!links.eof()) {
        
        //get content of line from file, if line is empty quit the loop
        getline(links, line);
        if(line.empty()) continue;
        
        //make line into stringstream object
        stringstream ss_line(line); 
        
        //vector to hold words in a line
        vector<string> tokens; 
        string word = ""; 
        
        //add words to the vector seperated by space
        while(getline(ss_line, word, ' ')) 
            tokens.push_back(word);
        
        //insert each line in dictionary into hash table
        g->insert(tokens[0], tokens[1], stoi(tokens[2]));
    }
    
    string source; 
    cout << "Enter name of starting vertex: "; 
    cin >> source; 

    clock_t t1 = clock();
    
    //run dijkstra's algorithm on verticess
    g->dijkstra(source); 

    clock_t t2 = clock(); 
    double timeDiff = ((double)(t2-t1)) / CLOCKS_PER_SEC;

    cout << "Total time (in seconds) to apply Dijkstra's algorithm: " << timeDiff << "\n";
}


int main() {
    
    graph *g = new graph(100);  

    parseFile(g); 
    g->generateOutput(); 

    return 0; 
}
