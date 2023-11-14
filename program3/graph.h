#ifndef _GRAPH_H
#define _GRAPH_H

#include <list> 
#include <vector>
#include <tuple> 
#include <string>

#include "hash.h"


using namespace std; 

class graph {

    class node { // An inner class within heap

        public:
            std::string id; // The id of this node
            int cost; //cost of the best path found so far from source->vertex
            bool known; //has the optimal path been found or not
            
            node* parent; 

            //edges connected to the vertex
            vector<tuple<node*, int>> edges; 
            
            node() = default; 
    }; 
    
    void createNode(node* temp_node, string id); 

    list<node*> nodes; 
    hashTable mapping; 

    int capacity, filled; 
        
    public:
        graph(int size); 

        void insert(string start, string dest, int cost); 
        void dijkstra(string source); 
};


#endif //_GRAPH_H
