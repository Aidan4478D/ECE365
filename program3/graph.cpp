#include "graph.h"
#include "heap.h"

#include <limits.h>

#define INF INT_MAX

graph::graph(int size) {
    
    mapping = hashTable(size); 
}

void graph::createNode(node* temp_node, string id) {
    
    mapping.insert(id, temp_node); 

    temp_node->id = id;
    temp_node->cost = INF; 
    temp_node->known = false; 

    nodes.push_back(temp_node); 

    filled++; 
}


void graph::insert(string source, string sink, int cost) {

    node *temp_source; 
    node *temp_sink;

    //if the starting vertex is already in the graph
    if(mapping.contains(source)) 
        temp_source = (node*) mapping.getPointer(source); 

    //otherwise create new vertex in graph
    else createNode(temp_source, source); 

    //if the ending vertex is already in the graph
    if(mapping.contains(sink))
        temp_source = (node*) mapping.getPointer(sink); 

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
    min_edge.setKey(start_node->id, start_node->cost); 
    start_node->cost = 0; 

    node *temp_node;

    //finding edge with smallest cost; or a deleteMin
    while(!min_edge.deleteMin(nullptr, nullptr, (void**) &temp_node)) {
        
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
                min_edge.setKey(start_node->id, start_node->cost); 
            }
        }
        temp_node->known = true; 
    }
}
