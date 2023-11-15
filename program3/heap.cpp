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
    mapping.insert(id, &data[0]); 

    //insert the data at ending position then percolate it up, no more memory leak hopefully
    data[++filled] = node(id, key, pv);
    percolateUp(filled); 
    
    return 0; 
}


int heap::setKey(const string &id, int key_) {

    //id is not in the hash table
    if(!mapping.contains(id)) return 1; 
    
    //gets node and position in array
    node *pn = static_cast<node *> (mapping.getPointer(id));
    int pos = getPos(pn); 
    
    //store old key into variable and set node to new key value
    int old_key = data[pos].key; 
    data[pos].key = key_;

    //place new key into correct position
    if(old_key < key_) percolateDown(pos); 
    else percolateUp(pos);

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
    
    //bring last element to front, update hash table, and percolate down
    data[1] = data[filled--]; 
    mapping.setPointer(data[1].id, &data[1]); 
    percolateDown(1);

    return 0; 
}


int heap::remove(const string &id, int *pKey, void *ppData) {
    
    //id is not in the hash table
    if(!mapping.contains(id)) return 1; 
    
    //gets node and position in array
    node *pn = static_cast<node *> (mapping.getPointer(id));
    mapping.remove(id); 
    
    int pos = getPos(pn);
    
    //fill in the pointers if provided
    if (pKey) *pKey = pn->key; 
    if (ppData) *(static_cast<void **> (ppData)) = pn->pData;
    
    //bring last node into deleted nodes position and update hash table
    data[pos] = data[filled--]; 
    mapping.setPointer(data[pos].id, &data[pos]);  

    //place new key into correct position
    if(data[pos].key < data[pos >> 1].key && pos > 1) percolateUp(pos); 
    else percolateDown(pos);

    return 0; 
}


int heap::getPos(node *pn) {
    int pos = pn - &data[0];
    return pos;
}


void heap::percolateUp(int posCur) {

    //bring newly inserted element to the front of the array (unused entry)
    data[0] = data[posCur]; 
    mapping.setPointer(data[0].id, &data[0]); 
    
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
            mapping.setPointer(data[prev_node].id, &data[prev_node]); 
        }

        //if it's not less than parent key, it's in the correct place
        else break; 
        
        prev_node = posCur; 
    }
    
    //insert original data into correct position w/o violating heap order property
    data[prev_node] = data[0]; 
    mapping.setPointer(data[prev_node].id, &data[prev_node]); 
}



void heap::percolateDown(int posCur) {

    //bring element at position to front of array
    data[0] = data[posCur];
    mapping.setPointer(data[0].id, &data[0]); 
    
    //initially set previous node to be where you initially insert
    int prev_node = posCur; 

    //bitshift left is equivalent to *2, till up to end of tree
    //similar implementation to the book in figure 6.12, page 253
    while ((posCur << 1) <= filled) {
        
        //bitshift left by 1
        posCur = posCur << 1;  

        //switching to left and right children
        if(posCur < filled && data[posCur + 1].key < data[posCur].key)
            posCur++;

        //swapping nodes down if original node key > current node key
        if(data[0].key > data[posCur].key) {
            data[prev_node] = data[posCur];
            mapping.setPointer(data[prev_node].id, &data[prev_node]); 
        }

        //otherwise node is in correct place so break loop
        else break; 
        
        //updating previous node position
        prev_node = posCur; 
    }
    
    //updating tree to insert node in correct position
    data[prev_node] = data[0]; 
    mapping.setPointer(data[prev_node].id, &data[prev_node]); 

}













