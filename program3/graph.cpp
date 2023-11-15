#include "graph.h"
#include "heap.h"

#include <limits.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <stack>

#define INF INT_MAX

graph::graph(int size) {
    
    mapping = hashTable(size); 
}

void graph::createNode(node* temp_node, string id) {
    
    temp_node->id = id;
    temp_node->cost = INF; 
    temp_node->known = false; 
    temp_node->parent = nullptr; 
    
    nodes.push_back(temp_node); 
    mapping.insert(id, temp_node); 
}


void graph::insert(string source, string sink, int cost) {

    node *temp_source = new node(); 
    node *temp_sink = new node(); 

    //if the starting vertex is already in the graph
    if(mapping.contains(source)) {
        temp_source = (node*) mapping.getPointer(source); 
    }
    //otherwise create new vertex in graph
    else createNode(temp_source, source); 
    
    //if the ending vertex is already in the graph
    if(mapping.contains(sink)) 
        temp_sink = (node*) mapping.getPointer(sink); 
    //otherwise create new vertex in graph
    else createNode(temp_sink, sink); 
    
    //add edge in tuple to graph
    tuple<node*, int> edge(temp_sink, cost); 
    temp_source->edges.push_back(edge); 
}



void graph::dijkstra(string source) {
    
    //get start node from hash table
    node* start_node = (node*) mapping.getPointer(source); 

    //create heap
    heap min_edge(nodes.size());

    //add nodes to heap
    for(auto node : nodes) 
        min_edge.insert(node->id, node->cost, node); 
    
    //initialize starting node and where to start heap
    start_node->cost = 0; 
    min_edge.setKey(start_node->id, start_node->cost); 
    
    //node to store current vertex in graph
    node *temp_node;

    //finding edge with smallest cost; or a deleteMin
    while(!min_edge.deleteMin(nullptr, nullptr, &temp_node)) {

        //if the cost after insertion is still infinity, there's no paths found
        if(temp_node->cost == INT_MAX) continue; 
        
        //loop through edges that a node/vertex has
        for(auto edge : temp_node->edges) {
            
            //access elements from edge tuple
            node *edge_node = get<0>(edge); 
            int edge_cost = get<1>(edge); 
            
            //calculate relative cost
            int temp_cost = edge_cost + temp_node->cost;
            
            //if path is non-optimal and temp_cost < current cost
            if(!edge_node->known && temp_cost < edge_node->cost) {
                
                //update edge costs and parent
                edge_node->cost = temp_cost; 
                edge_node->parent = temp_node; 
                
                //update which node to expand off of
                min_edge.setKey(edge_node->id, edge_node->cost); 
            }
        }
        temp_node->known = true; 
    }
}



void graph::generateOutput() {
    
    //get name of output file
    string file_name; 
    cout << "Please enter the name of an output file: ";
    cin >> file_name; 

    ofstream of(file_name); 
    
    //loop through all the nodes
    for(auto n : nodes) {
        
        //print the name and the colon
        of << n->id << ": ";
        
        //if path is non-optimal and the cost is infinity, there's no path to the node
		if (!n->known && n->cost == INT_MAX) {
			of << "NO PATH\n";
			continue;
		}
        
        //print out cost, initial bracket, and variable to store path
        of << n->cost << " [";
		string out_path;
    
        //variable to store the parents of node paths
        node *p = n->parent;

        //loop through parents and add to path
		while(p != nullptr){
			out_path += (p->id + ", ");
			p = p->parent;
		}

        //write path to output file 
		of << out_path << n->id << "]\n";
    }
    
    of.close(); 
}

