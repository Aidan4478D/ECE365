#ifndef _GRAPH_H
#define _GRAPH_H

#include <list> 
#include <vector>
#include <tuple> 
#include <string>

#include "hash.h"


using namespace std; 

class graph {
    
    //node class nested within heap
    class node {

        public:
            string id; //id of the node
            int cost; //cost of the best path found so far from source->vertex
            bool known; //has the optimal path been found or not
            
            node* parent; 

            //edges connected to the vertex
            vector<tuple<node*, int>> edges; 
            
            node(string id_ = "", int cost_ = 0, bool known_ = false, node *parent_ = nullptr) {
                id = id_;
                cost = cost_; 
                known = known_; 
               parent = parent_; 
            }
    }; 
    
    void createNode(node* temp_node, string id); 

    list<node*> nodes; 
    hashTable mapping; 
        
    public:
        graph(int size); 

        void insert(string start, string dest, int cost); 
        void dijkstra(string source); 
        void generateOutput();
};


#endif //_GRAPH_H
