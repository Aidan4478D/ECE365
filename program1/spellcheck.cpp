#include <iostream>
#include "hash.h"



int main() {
    
    hashTable *hash = new hashTable(100000); 
    hash->insert("hello");    

    return 0; 
}
