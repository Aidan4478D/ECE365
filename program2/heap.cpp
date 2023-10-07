#include "heap.h"
#include "hash.h"
#include <vector>

//heap logic
//note: left child of node is stored in position 2*i + 1 or bitshift left by 1


heap::heap(int capacity_):mapping(capacity_*2) {
    
    capacity = capacity_; 
    filled = 0; 

    // Allocate space for the nodes (0 slot is not used)
    data.resize(capacity_+1);
}

int heap::insert(const string &id, int key, void *pv) {
    
    //if heap is filled to capacity
    if(filled == capacity) return 1; 

    //if node with id already exists (i.e. in hash table) 
    if(mapping.contains(id)) return 2; 

    //creates new node object
    node *new_node = new node(id, key, pv);  
    
    //insert the data at ending position then percolate it up
    data[++filled] = *new_node;
    percolateUp(filled); 
    
    return 0; 
}

int heap::setKey(const string &id, int key) {

    //id is not in the hash table
    if(!mapping.contains(id)) return 1; 
    
    //get position of first node
    node *new_node = nullptr;
    int pos = getPos(new_node); 

    //perform increasekey and decreasekey logic

    //set new key
    data[pos].key = key;    

    return 0; 
}

int heap::deleteMin(string *pId, int *pKey, void *ppData) {
    
    //heap is empty
    if(filled == 0) return 1; 
    
    //get deleted node and percolate the other values down
    node deleted_node = data[1];

    //remove node from hash table
    mapping.setPointer(deleted_node.id, &deleted_node); 
    mapping.remove(deleted_node.id); 
    
    //make checks and set pointer variables to deleted node values
    if (pId) *pId = deleted_node.id;
    if (pKey) *pKey = deleted_node.key; 
    if (ppData) *(static_cast<void **> (ppData)) = deleted_node.pData;

    
    //percolate down last element
    data[1] = data[filled--]; 
    percolateDown(1);

    return 0; 
}

int heap::remove(const string &id, int *pKey, void *ppData) {
    
    filled--; 

    return 0; 
}


int heap::getPos(node *pn) {
    int pos = pn - &data[0];
    return pos;
}


void heap::percolateUp(int posCur) {

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



void heap::percolateDown(int posCur) {

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
        if(posCur != filled && data[posCur + 1].key < data[posCur].key)
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













