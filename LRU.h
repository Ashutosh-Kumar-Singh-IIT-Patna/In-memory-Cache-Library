#ifndef LRU_H
#define LRU_H

#include "EvictionPolicy.h"
#include <unordered_map>

// LRU (Least Recently Used) eviction policy
template<typename Key>
class LRU : public EvictionPolicy<Key> {
private:
    std::unordered_map<Key, typename DoublyLinkedList<Key>::iterator> map;

public:
    void keyAccessed(const Key& key) override {
        auto it = map.find(key);
        if (it != map.end()) {
            this->order.erase(it->second);
        }
        this->order.push_back(key);
        map[key] = this->order.last();
    }

    void keyInserted(const Key& key) override {
        this->order.push_back(key);
        map[key] = this->order.last();
    }

    Key evict() override {
        if (this->order.empty()) {
            throw std::runtime_error("No keys to evict");
        }
        Key key = this->order.front();
        this->order.pop_front();
        map.erase(key);
        return key;
    }

    void keyRemoved(const Key& key) override {
        auto it = map.find(key);
        if (it != map.end()) {
            this->order.erase(it->second);
            map.erase(it);
        }
    }
};

#endif // LRU_H
