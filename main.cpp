#include <iostream>
#include "Cache.h"
#include "FIFO.h"
#include "LRU.h"
#include "LIFO.h"

using namespace std;

int main() {
    try {

        // Create a cache with FIFO eviction policy
        Cache<int, string, FIFO<int>> FIFOcache(3);
        cout << "Testing FIFO policy:" << endl;

        FIFOcache.put(1, "one");
        FIFOcache.put(2, "two");
        FIFOcache.put(3, "three");

        cout << "Value for key 2: " << FIFOcache.get(2) << endl; // Should be "two"

        FIFOcache.put(4, "four");  // This should evict key 1 (FIFO)

        cout << "Value for key 1 (should be evicted as it was the first inserted): ";
        string value_fifo = FIFOcache.get(1);
        cout << value_fifo << endl; // Should be "Key not found: 1"




        // Create a cache with LRU eviction policy
        Cache<int, string, LRU<int>> LRUcache(3);
        cout << "Testing LRU policy:" << endl;

        LRUcache.put(1, "one");
        LRUcache.put(2, "two");
        LRUcache.put(3, "three");

        cout << "Value for key 1: " << LRUcache.get(1) << endl; // Should be "one", Now 2 becomes least recently used

        LRUcache.put(4, "four");  // This should evict key 2 (LRU)

        cout << "Value for key 2 (should be evicted as it was the least recently used): ";
        string value_lru = LRUcache.get(2);
        cout << value_lru << endl; // Should be "Key not found: 2"




        // Create a cache with LIFO eviction policy
        Cache<int, string, LIFO<int>> LIFOcache(3);
        cout << "Testing LIFO policy:" << endl;

        LIFOcache.put(1, "one");
        LIFOcache.put(2, "two");
        LIFOcache.put(3, "three");

        cout << "Value for key 2: " << LIFOcache.get(2) << endl; // Should be "two"

        LIFOcache.put(4, "four");  // This should evict key 3 (LIFO)

        cout << "Value for key 3 (should be evicted as it was the last inserted): ";
        string value_lifo = LIFOcache.get(3);
        cout << value_lifo << endl; // Should be "Key not found: 3"

    } catch (const exception& e) {
        cerr << "Exception: " << e.what() << endl;
    }
    return 0;
}


/*

Output:-

Testing FIFO policy:
Value for key 2: two
Evicting key: 1
Value for key 1 (should be evicted as it was the first inserted): Key not found: 1

Testing LRU policy:
Value for key 1: one
Evicting key: 2
Value for key 2 (should be evicted as it was the least recently used): Key not found: 2

Testing LIFO policy:
Value for key 2: two
Evicting key: 3
Value for key 3 (should be evicted as it was the last inserted): Key not found: 3

*/
