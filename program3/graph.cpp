#include "graph.h"
#include <limits.h>

#define INF INT_MAX

graph::graph(int size) {
    
    filled = 0;
    mapping = hashTable(size); 
}

void graph::createNode(node* temp_node, string id) {
    
    mapping.insert(id, temp_node); 

    temp_node->id = id;
    temp_node->dist = INF; 
    temp_node->prev = nullptr; 
    
    nodes.push_back(*temp_node); 

    filled++; 
}


void graph::insert(string source, string sink, int cost) {

    node *temp_source; 
    node *temp_sink;

    //if the starting vertex is already in the graph
    if(mapping.contains(source)) 
        temp_source = (node*) mapping.getPointer(source); 

    //otherwise create new vertex in graph
    else 
        createNode(temp_source, source); 

    //if the ending vertex is already in the graph
    if(mapping.contains(sink))
        temp_source = (node*) mapping.getPointer(sink); 

    //otherwise create new vertex in graph
    else 
        createNode(temp_sink, sink); 
    
    //jankily adding edge to vector of edges
    int pos = temp_source->path.size();
    temp_source->path.resize(++pos); 
    temp_source->path[pos].cost = cost; 
    temp_source->path[pos].sink = temp_sink; 
}
