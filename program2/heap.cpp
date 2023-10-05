#include "heap.h"

//heap logic
//note: left child of node is stored in position 2*i + 1


heap::heap(int capacity):mapping(capacity*2) {

    // Allocate space for the nodes (0 slot is not used)
    data.resize(capacity+1);
}

int heap::insert(const string &id, int key, void *pv) {
    
    //if heap is filled to capacity
    if(data.size() == capacity) return 1; 

    //if node with id already exists (i.e. in hash table) 
    if(mapping.contains(id)) return 2; 

    //creates new node object
    node *new_node; 
    new_node->id = id; 
    new_node->key = key; 
    new_node->pv = pv; 

    
    //do some percolating up


    capacity++; 

    return 0; 
}
int heap::setKey(const string &id, int key) {

    return 0; 
}

int heap::deleteMin(string *pId, int *pKey, void *ppData) {

    return 0; 
}

int heap::remove(const string &id, int *pKey, void *ppData) {
    
    return 0; 
}


int heap::getPos(node *pn) {

    int pos = pn - &data[0];

    return pos;
}


void percolateUp(int posCur) {

    //bring newly inserted element to the front of the array (unused entry)
    data[0] = data[posCur]; 

    //initially set previous node to be where you initially insert
    int prev_node = posCur; 

    //bitshift right is equivalent to /2, go till at front of tree
    while ((posCur >> 1) > 0) {
        
        //bitshift right by 1
        posCur = posCur >> 1;  

        //compare node to insert key with current position key
        if(data[0].key < data[posCur].key) {
            
            //move element down
            data[prev_node] = data[posCur]; 
        }

        //if it's not less than parent key, it's in the correct place
        else break; 
        
        prev_node = posCur; 
    }
    
    //insert original data into correct position w/o violating heap order property
    data[prev_node] = data[0]; 
}



void percolateDown(int posCur) {

    //bring element at position to front of array
    data[0] = data[posCur];
    
    //initially set previous node to be where you initially insert
    int prev_node = posCur; 

    //bitshift left is equivalent to /2, till up to end of tree
    //similar implementation to the book in figure 6.12, page 253
    while ((posCur << 1) <= filled) {
        
        //bitshift left by 1
        posCur = posCur << 1;  

        //switching to left and right children
        if(posCur != filled && data[posCur + 1].key < data[posCur])
            posCur++;

        //swapping nodes down if original node key > current node key
        if(data[0].key > data[posCur].key) 
            data[prev_node] = data[posCur];

        //otherwise node is in correct place so break loop
        else break; 
        
        //updating previous node position
        prev_node = posCur; 
    }
    
    //updating tree to insert node in correct position
    data[prev_node] = data[0]; 
}













