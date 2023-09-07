#include "hash.h"
#define NUM_PRIMES 6


using namespace std; 

hashTable::hashTable(int size) {

}

int hashTable::hashTable(const string &key, void *pv) {

    return 0; 
}

bool hashTable::contains(const string &key) {

    return true; 
}

int hashTable::hash(const string &key) {

}

int hashTable::findPos(const string &key) {

}

bool hashTable::rehash() {

}

static unsigned int getPrime(int size) {
    
    //chose six primes, could add more if more entries are needed
    int primes[NUM_PRIMES] = {98317, 196613, 393241, 786433, 1572869, 3145739}

    if (size < primes[0]) { return primes[0]; }

    else {

        for(int i = 0; i < NUM_PRIMES-1; i++) {
            
            if (size > primes[i] && size < primes[i + 1]) {
               
                //return bigger prime
                return primes[i + 1] 
            }
        }
    }
    
    //return -1 on failure
    return -1; 
}





