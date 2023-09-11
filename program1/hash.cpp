#include "hash.h"
#include <iostream>
#define NUM_PRIMES 6


using namespace std; 

hashTable::hashTable(int size) {

    capacity = getPrime(size);
    printf("prime number is %d\n", capacity);
    
    //would reserve be a better operation?
    data.resize(capacity);
}

int hashTable::insert(const string &key, void *pv) {
    
    //if the hash table is >= 50% filled, add more spots to the table
    //if you cant add more spots to the table return an error
    if (((double)filled / capacity) >= 0.5) {
        if(!rehash())
            return 2; 
    }

    //returns 1 if the key is already in the table
    if (contains(key)) { return 1; }
    
    //gets hash number index thing based off key
    int hash_val = hash(key); 
    cout << "key is " << key << " hash val is " << hash_val << "\n"; 

    //create new hash item with key
    hashItem *item = new hashItem(); 
    item->key = key; 
    
    //insert item into hash table data
    data.insert(data.begin() + hash_val, *item); 
    filled++; 

    return 0; 
}

bool hashTable::contains(const string &key) {

    return false; 
}

int hashTable::hash(const string &key) {
    
    /* hash function from 
     * Chapter 5.2, Figure 5.4
     * "Data Structures and Algorithm Analysis in C++", 4th Edition
by Mark Allen Weiss
    */

    unsigned int hashVal = 0;

    for( char ch : key )
        hashVal = 37 * hashVal + ch;

    return hashVal % capacity;
}

int hashTable::findPos(const string &key) {

    return 0;
}

bool hashTable::rehash() {
    
    return 0; 
}

unsigned int hashTable::getPrime(int size) {
    
    //chose six primes, could add more if more entries are needed
    int primes[NUM_PRIMES] = {98317, 196613, 393241, 786433, 1572869, 3145739};

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





