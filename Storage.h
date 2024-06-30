#ifndef STORAGE_H
#define STORAGE_H

#include <unordered_map>
#include <stdexcept>
#include <iostream>

// Storage class to hold key-value pairs
template<typename Key, typename Value>
class Storage {
private:
    std::unordered_map<Key, Value> data; // Hash map to store data
public:
    void put(const Key& key, const Value& value) {
        data[key] = value;
    }

    Value get(const Key& key) const {
        if (!exists(key)) {
            throw std::runtime_error("Key not found: " + std::to_string(key));
        }
        return data.at(key);
    }

    void remove(const Key& key) {
        data.erase(key);
    }

    bool exists(const Key& key) const {
        return data.find(key) != data.end();
    }

    size_t size() const {
        return data.size();
    }
};

#endif // STORAGE_H
