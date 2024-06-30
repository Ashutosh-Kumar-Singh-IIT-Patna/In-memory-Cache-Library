#ifndef CACHE_H
#define CACHE_H

#include "Storage.h"
#include <mutex>
#include "EvictionPolicy.h"
#include <iostream>

// Template class for Cache with Key, Value, and EvictionPolicy as template parameters
template<typename Key, typename Value, typename EvictionPolicy>
class Cache {
private:
    size_t capacity;  // Maximum capacity of the cache
    Storage<Key, Value> storage;  // Storage object to store key-value pairs
    EvictionPolicy evictionPolicy;  // Eviction policy object to handle cache eviction
    std::mutex mtx;  // Mutex for thread safety

public:
    // Constructor to initialize cache with a given capacity
    Cache(size_t capacity) : capacity(capacity) {}

    // Method to add a key-value pair to the cache
    void put(const Key& key, const Value& value) {
        mtx.lock();
        try {
            // If the cache is at full capacity, evict an item based on the eviction policy
            if (storage.size() == capacity) {
                Key evictedKey = evictionPolicy.evict();
                std::cout << "Evicting key: " << evictedKey << std::endl;
                storage.remove(evictedKey);
            }
            // Insert the new key-value pair into the cache
            storage.put(key, value);
            // Notify the eviction policy of the new key insertion
            evictionPolicy.keyInserted(key);
        } catch (...) {
            std::cerr << "Error: Unable to insert key-value pair." << std::endl;
        }
        mtx.unlock();
    }

    // Method to retrieve the value associated with a key
    Value get(const Key& key) {
        mtx.lock();
        Value result;
        try {
            // Check if the key exists in the cache
            if (!storage.exists(key)) {
                std::cerr << "Key not found: " << key << std::endl;
            } else {
                // Notify the eviction policy of the key access
                evictionPolicy.keyAccessed(key);
                // Retrieve the value from the cache
                result = storage.get(key);
            }
        } catch (...) {
            std::cerr << "Error: Unable to retrieve value for key." << std::endl;
        }
        mtx.unlock();
        return result;
    }

    // Method to remove a key-value pair from the cache
    void remove(const Key& key) {
        mtx.lock();
        try {
            // Check if the key exists in the cache
            if (storage.exists(key)) {
                // Notify the eviction policy of the key removal
                evictionPolicy.keyRemoved(key);
                // Remove the key-value pair from the cache
                storage.remove(key);
            } else {
                std::cerr << "Key not found: " << key << std::endl;
            }
        } catch (...) {
            std::cerr << "Error: Unable to remove key." << std::endl;
        }
        mtx.unlock();
    }

    // Method to check if a key exists in the cache
    bool exists(const Key& key) {
        mtx.lock();
        bool result = storage.exists(key);
        mtx.unlock();
        return result;
    }
};

#endif // CACHE_H
