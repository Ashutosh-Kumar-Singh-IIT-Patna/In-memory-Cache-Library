#ifndef DOUBLYLINKEDLIST_H
#define DOUBLYLINKEDLIST_H

// A templated doubly linked list class to support eviction policies
template <typename T>
class DoublyLinkedList {
private:
    // Node structure for doubly linked list
    struct Node {
        T data;
        Node* prev;
        Node* next;
        Node(const T& data) : data(data), prev(nullptr), next(nullptr) {}
    };

    Node* head; // Head of the list
    Node* tail; // Tail of the list
    size_t count; // Number of elements in the list

public:
    using iterator = Node*; // Iterator type definition

    // Constructor to initialize an empty list
    DoublyLinkedList() : head(nullptr), tail(nullptr), count(0) {}

    // Destructor to clean up the list
    ~DoublyLinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    // Add a value to the end of the list
    void push_back(const T& value) {
        Node* newNode = new Node(value);
        if (!tail) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        ++count;
    }

    // Remove the value from the end of the list
    void pop_back() {
        if (!tail) return;
        Node* temp = tail;
        tail = tail->prev;
        if (tail) tail->next = nullptr;
        else head = nullptr;
        delete temp;
        --count;
    }

    // Add a value to the front of the list
    void push_front(const T& value) {
        Node* newNode = new Node(value);
        if (!head) {
            head = tail = newNode;
        } else {
            head->prev = newNode;
            newNode->next = head;
            head = newNode;
        }
        ++count;
    }

    // Remove the value from the front of the list
    void pop_front() {
        if (!head) return;
        Node* temp = head;
        head = head->next;
        if (head) head->prev = nullptr;
        else tail = nullptr;
        delete temp;
        --count;
    }

    // Get the number of elements in the list
    size_t size() const {
        return count;
    }

    // Check if the list is empty
    bool empty() const {
        return count == 0;
    }

    // Get the value at the front of the list
    T& front() {
        if (!head) throw std::out_of_range("List is empty");
        return head->data;
    }

    // Get the value at the back of the list
    T& back() {
        if (!tail) throw std::out_of_range("List is empty");
        return tail->data;
    }

    // Remove a specific value from the list
    void remove(const T& value) {
        Node* current = head;
        while (current) {
            if (current->data == value) {
                Node* temp = current;
                if (current->prev) current->prev->next = current->next;
                if (current->next) current->next->prev = current->prev;
                if (current == head) head = current->next;
                if (current == tail) tail = current->prev;
                current = current->next;
                delete temp;
                --count;
            } else {
                current = current->next;
            }
        }
    }

    // Erase a node from the list using an iterator
    void erase(iterator it) {
        if (!it) return;
        if (it->prev) it->prev->next = it->next;
        if (it->next) it->next->prev = it->prev;
        if (it == head) head = it->next;
        if (it == tail) tail = it->prev;
        delete it;
        --count;
    }

    // Get an iterator to the end of the list (nullptr)
    iterator end() const {
        return nullptr;
    }

    // Get an iterator to the beginning of the list
    iterator begin() const {
        return head;
    }

    // Get an iterator to the last element of the list
    iterator last() const {
        return tail;
    }
};

#endif // DOUBLYLINKEDLIST_H
