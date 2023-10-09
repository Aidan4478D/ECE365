#include "hash.h"
#include <iostream>
#define NUM_PRIMES 6


using namespace std; 

hashTable::hashTable(int size) {
    
    filled = 0; 

    //get prime number
    capacity = getPrime(size);
    
    //would reserve be a better operation?
    data.resize(capacity);
}

int hashTable::insert(const string &key, void *pv) {
    
    //returns 1 if the key is already in the table
    if (contains(key))  return 1;
    
    //if the hash table is >= 50% filled, add more spots to the table
    //if you cant add more spots to the table return an error
    if (filled >= capacity/2.0) {
        
        //rehash fail check
        if(!rehash())
            return 2; 
    }
    
    //gets hash number index thing based off key
    int hash_val = hash(key); 
    int iterations = 0; 

    //create new hash item with key
    hashItem *item = new hashItem(); 
    item->key = key; 
    item->isOccupied = true; 
    item->isDeleted = false; 
    item->pv = pv; 
  
    while(data[hash_val].isOccupied && !data[hash_val].isDeleted) {
        
        //increment index - linear probing
        hash_val++;
        
        //break out of loop if you've iterated through the entire table somehow
        iterations++; 
        if(iterations > capacity) return -1; 

        //reset back to zero if hash_val > capacity
        hash_val %= capacity; 
    }

    //insert item into hash table data
    data[hash_val] = *item; 
    filled++; 

    return 0; 
}

bool hashTable::contains(const string &key) {
    
    bool val; 
    //return true if key is found, false otherwise
    (findPos(key) == -1) ? val = false : val = true;
    return val; 
}

void* hashTable::getPointer(const string &key, bool *b) {
    
    //if the key isn't found, set b to false and return nullptr
    if(!contains(key)) {
        if(b) *b = false; 
        return nullptr;
    }

    //otherwise set b to true and return the associated ptr
    if(b) *b = true; 
    return data[findPos(key)].pv; 
}


int hashTable::setPointer(const string &key, void *pv) {
    
    //set data pointer value to pv if key is found
    if(contains(key)) {
        data[findPos(key)].pv = pv; 
        return 0; 
    }
    return 1; 
}


bool hashTable::remove(const string &key) {
    
    //lazy deletion if key is found
    if(contains(key)) {
        data[findPos(key)].isDeleted = true;
        return true;
    }

    return false; 
}


int hashTable::hash(const string &key) {
    
    /* hash function from 
     * Chapter 5.2, Figure 5.4
     * "Data Structures and Algorithm Analysis in C++", 4th Edition by Mark Allen Weis */

    unsigned int hashVal = 0;

    for (char ch : key)
        hashVal = 37 * hashVal + ch;

    return hashVal % capacity;
}

int hashTable::findPos(const string &key) {
    
    int hash_val = hash(key); 
    int iterations = 0; 

    while(data[hash_val].isOccupied ) {
        if (data[hash_val].key == key && !data[hash_val].isDeleted) return hash_val; 
        
        //increment index - linear probing
        hash_val++; 

        //break out of loop if you've iterated through the entire table somehow
        iterations++; 
        if(iterations > capacity) break; 

        //reset index back to zero if hash_val > capacity
        hash_val %= capacity; 
    }
    
    //return -1 on failure
    return -1;
}

bool hashTable::rehash() {
    
    //double hash capacity
    capacity = getPrime(capacity * 2); 

    //copy old data into a new vector and clear the current vector
    vector<hashItem> old_data = data; 
    data.clear(); 

    //try increasing the capacity size
    try {
        data.resize(capacity); 
    }   
    //return false if new memory allocation fails
    catch(bad_alloc&) {
        return false; 
    }

    for(int i = 0; i < old_data.size(); i++) {

        //if a hashItem exists in a certain position
        if(old_data[i].isOccupied && !old_data[i].isDeleted) {

            //will insert item at correct key position in new table
            insert(old_data[i].key, old_data[i].pv); 
        }
    }
    
    return true; 
}

unsigned int hashTable::getPrime(int size) {
    
    //chose six primes, could add more if more entries are needed
    int primes[NUM_PRIMES] = {98317, 196613, 393241, 786433, 1572869, 3145739};

    //if size is less than 98317, just make table size 98317 anyways
    if (size < primes[0]) { return primes[0]; }
    
    else {
        for(int i = 0; i < NUM_PRIMES-1; i++) {  
            if (size > primes[i] && size < primes[i + 1]) {
                //return bigger prime
                return primes[i + 1];
            }
        }
    }
    
    //return biggest prime in array if requested number is too big
    return primes[NUM_PRIMES - 1]; 
}
