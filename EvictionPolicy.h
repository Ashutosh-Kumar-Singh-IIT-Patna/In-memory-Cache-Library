#ifndef EVICTIONPOLICY_H
#define EVICTIONPOLICY_H

#include "DoublyLinkedList.h"

// Abstract base class for eviction policies
template<typename Key>
class EvictionPolicy {
protected:
    DoublyLinkedList<Key> order; // Keeps track of the order of keys
public:
    virtual void keyAccessed(const Key& key) = 0; // Called when a key is accessed
    virtual void keyInserted(const Key& key) = 0; // Called when a key is inserted
    virtual Key evict() = 0; // Called to evict a key
    virtual void keyRemoved(const Key& key) = 0; // Called when a key is removed
};

#endif // EVICTIONPOLICY_H
