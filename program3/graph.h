#ifndef _GRAPH_H
#define _GRAPH_H

#include <list> 
#include <tuple> 
#include <string>

#include "hash.h"

using namespace std; 

class graph {

    class node { // An inner class within heap

        class edge {
            
            public:
                node *sink; 
                int cost; 
        }; 

        public:
            std::string id; // The id of this node
            int dist; //cost of the best path found so far from source->vertex
            node *prev; //previous node on the path from source->vertex

            //edges connected to the vertex
            vector<edge> path; 

            node() = default; 
    }; 
    
    void createNode(node* temp_node, string id); 

    list<node> nodes; 
    hashTable mapping; 

    int capacity, filled; 
        
    public:
        graph(int size); 

        void insert(string start, string dest, int cost); 
        void djikstra(); 
};


#endif //_GRAPH_H
