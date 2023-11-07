#ifndef _GRAPH_H
#define _GRAPH_H

#include <list> 
#include <tuple> 
#include <string>

#include "hash.h"

using namespace std; 

class graph {

    class node { // An inner class within heap
        public:
            std::string id; // The id of this node
            
            //adjacency list with edge costs
            list<tuple<node, int>> adjacent;
            
            //log of verticies along a path
            list<string> path; 

            node() = default; 
    }; 

    list<node> nodes; 
    hashTable mapping; 
        
    public:
        graph(int size); 

        void insert(string start, string dest, int cost); 
        void djikstra(); 
};


#endif //_GRAPH_H
