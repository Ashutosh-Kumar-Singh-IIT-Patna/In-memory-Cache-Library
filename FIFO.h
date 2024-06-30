#ifndef FIFO_H
#define FIFO_H

#include "EvictionPolicy.h"

// FIFO (First In, First Out) eviction policy
template<typename Key>
class FIFO : public EvictionPolicy<Key> {
public:
    void keyAccessed(const Key&) override {}

    void keyInserted(const Key& key) override {
        this->order.push_back(key);
    }

    Key evict() override {
        if (this->order.empty()) {
            throw std::runtime_error("No keys to evict");
        }
        Key key = this->order.front();
        this->order.pop_front();
        return key;
    }

    void keyRemoved(const Key& key) override {
        this->order.remove(key);
    }
};

#endif // FIFO_H
