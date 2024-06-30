#ifndef LIFO_H
#define LIFO_H

#include "EvictionPolicy.h"

// LIFO (Last In, First Out) eviction policy
template<typename Key>
class LIFO : public EvictionPolicy<Key> {
public:
    void keyAccessed(const Key&) override {}

    void keyInserted(const Key& key) override {
        this->order.push_back(key);
    }

    Key evict() override {
        if (this->order.empty()) {
            throw std::runtime_error("No keys to evict");
        }
        Key key = this->order.back();
        this->order.pop_back();
        return key;
    }

    void keyRemoved(const Key& key) override {
        this->order.remove(key);
    }
};

#endif // LIFO_H
